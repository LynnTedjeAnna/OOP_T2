using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace ContainerShipping
{
    // Class to hold the state of the client session
    public class ClientSession
    {
        public string ExpectedCommand { get; set; } = "START"; // Initialize to START
        public Container CurrentContainer { get; set; } // To store the current container during the session
        public List<ContainerData> ContainerRecords { get; set; } = new List<ContainerData>(); // List to hold container records
        private int _containerIdCounter = 1000; // Start ID for containers

        // Method to add container data
        public void AddContainerData()
        {
            if (CurrentContainer != null)
            {
                ContainerRecords.Add(new ContainerData
                {
                    Id = _containerIdCounter++,
                    Weight = CurrentContainer.Weight,
                    Volume = CurrentContainer.Volume,
                    Refrid = CurrentContainer.IsRefrigerated() ? "YES" : "NO",
                    Fee = CurrentContainer.CalculateFee(),
                    ContainerType = CurrentContainer.GetType().Name
                });
            }
        }
    }

    public class ShippingServer
    {
        private readonly TcpListener _listener;

        public ShippingServer(int port)
        {
            _listener = new TcpListener(IPAddress.Any, port);
        }

        public async Task StartAsync()
        {
            _listener.Start();
            Console.WriteLine("Server started... Listening for connections.");

            while (true)
            {
                TcpClient client = await _listener.AcceptTcpClientAsync();
                _ = Task.Run(() => HandleClientAsync(client)); // Handle each client in a new task
            }
        }

        private async Task HandleClientAsync(TcpClient client)
        {
            using NetworkStream stream = client.GetStream();
            using var reader = new StreamReader(stream, Encoding.ASCII);
            using var writer = new StreamWriter(stream, Encoding.ASCII) { AutoFlush = true };

            await writer.WriteLineAsync("WELCOME");

            ClientSession session = new ClientSession(); // Create a new session for the client

            try
            {
                string line;
                while ((line = await reader.ReadLineAsync()) != null)
                {
                    await ProcessCommand(line.Trim().ToUpper(), writer, session, client); // Pass client to the method
                }
            }
            catch (Exception ex)
            {
                await writer.WriteLineAsync($"ERR;{ex.Message}");
            }
            finally
            {
                await GenerateReport(writer, session); // Generate report before closing
                client.Close();
                Console.WriteLine("Connection closed.");
            }
        }

        private async Task ProcessCommand(string command, StreamWriter writer, ClientSession session, TcpClient client)
        {
            // Check for STOP command
            if (command == "STOP")
            {
                await writer.WriteLineAsync("ACK; Connection will be closed."); // Acknowledge STOP command
                Console.WriteLine("STOP command received. Closing connection.");
                client.Close(); // Close the connection immediately
                return; // Exit the method early
            }

            switch (session.ExpectedCommand)
            {
                case "START":
                    if (command == "START")
                    {
                        await writer.WriteLineAsync("ACK"); // Acknowledge START
                        session.ExpectedCommand = "TYPE"; // Move to expecting TYPE
                        await writer.WriteLineAsync("TYPE"); // Indicate next expected command
                    }
                    else
                    {
                        await writer.WriteLineAsync("ERR;Expected START");
                    }
                    break;

                case "TYPE":
                    if (command == "FULL" || command == "HALF" || command == "QUART")
                    {
                        session.CurrentContainer = CreateContainer(command); // Create the appropriate container based on type
                        session.ExpectedCommand = command == "FULL" ? "FRIDGE" : command == "HALF" ? "VOLUME" : "STOP";
                        await writer.WriteLineAsync("ACK"); // Acknowledge TYPE

                        // Prepare for next command based on type
                        if (session.CurrentContainer is FullSizeContainer)
                            await writer.WriteLineAsync("FRIDGE"); // Prompt for fridge info for FULL
                        else if (session.CurrentContainer is HalfSizeContainer)
                            await writer.WriteLineAsync("VOLUME"); // Prompt for volume for HALF
                        else
                            await writer.WriteLineAsync("ACK"); // Acknowledge QUART input and end session
                    }
                    else
                    {
                        await writer.WriteLineAsync("ERR;Invalid Type");
                    }
                    break;

                case "FRIDGE":
                    if (command == "YES")
                    {
                        // Set refrigeration status in ContainerData
                        session.CurrentContainer.IsRefrigerated = command == "YES";
                        // Save to ContainerData
                        session.AddContainerData(); // Assuming this method captures the current state in ContainerData
                        await writer.WriteLineAsync("ACK");
                        session.ExpectedCommand = "WEIGHT"; // Expecting weight input
                        await writer.WriteLineAsync("WEIGHT"); // Prompt for weight
                    }
                    else if (command == "NO")
                    {
                        // Set refrigeration status in ContainerData
                        session.CurrentContainer.IsRefrigerated = command == "NO";
                        // Save to ContainerData
                        session.AddContainerData(); // Assuming this method captures the current state in ContainerData
                        await writer.WriteLineAsync("ACK");
                        session.ExpectedCommand = "WEIGHT"; // Expecting weight input
                        await writer.WriteLineAsync("WEIGHT"); // Prompt for weight
                    }
                    else
                    {
                        await writer.WriteLineAsync("ERR;Expected YES or NO");
                    }
                    break;

                case "WEIGHT":
                    if (int.TryParse(command, out int weight) && weight <= 20000)
                    {
                        session.CurrentContainer.Weight = weight; // Set the weight for FULL container
                        session.AddContainerData(); // Add container data to the list
                        await writer.WriteLineAsync("ACK");
                        session.ExpectedCommand = "STOP"; // Session ends after receiving weight
                        await writer.WriteLineAsync("ACK");
                    }
                    else
                    {
                        await writer.WriteLineAsync("ERR;Weight Exceeded");
                    }
                    break;

                case "VOLUME":
                    if (int.TryParse(command, out int volume) && volume <= 40)
                    {
                        session.CurrentContainer.Volume = volume; // Set the volume for HALF container
                        session.AddContainerData(); // Add container data to the list
                        await writer.WriteLineAsync("ACK");
                        session.ExpectedCommand = "STOP"; // Session ends after receiving volume
                        await writer.WriteLineAsync("ACK");
                    }
                    else
                    {
                        await writer.WriteLineAsync("ERR;Volume Exceeded");
                    }
                    break;

                case "STOP":
                    // After the last ACK, just stop and close the connection
                    Console.WriteLine("Session ended. Closing connection.");
                    await GenerateReport(writer, session); // Generate report before closing
                    client.Close(); // Close the connection after reporting
                    break;

                default:
                    await writer.WriteLineAsync("ERR;Unknown Command");
                    break;
            }
        }

        private async Task GenerateReport(StreamWriter writer, ClientSession session)
        {
            decimal grandTotal = 0m;

            // Calculate totals per container type
            var fullTotal = CalculateContainerTotal(session.ContainerRecords, "FullSizeContainer");
            var halfTotal = CalculateContainerTotal(session.ContainerRecords, "HalfSizeContainer");
            var quartTotal = CalculateContainerTotal(session.ContainerRecords, "QuarterSizeContainer");

            await writer.WriteLineAsync("\n--- Report ---");

            // Full Size report
            await writer.WriteLineAsync(String.Format("|{0, -10}|{1, -10}|{2, -10}|{3, -10}|{4, -10}|", "ID", "Weight", "Volume", "Refrid", "Fee"));

            foreach (var record in session.ContainerRecords)
            {
                string weight = record.Weight.HasValue ? $"{record.Weight}kg" : "N/A";
                string volume = record.Volume.HasValue ? $"{record.Volume}m3" : "N/A";
                await writer.WriteLineAsync(String.Format("|{0, -10}|{1, -10}|{2, -10}|{3, -10}|{4, -10}|", record.Id, weight, volume, record.Refrid, $"€{record.Fee:F2}"));
            }

            // Final report
            await writer.WriteLineAsync($"Full Total €{fullTotal:F2}");
            await writer.WriteLineAsync($"Half Total €{halfTotal:F2}");
            await writer.WriteLineAsync($"Quart Total €{quartTotal:F2}");

            grandTotal = fullTotal + halfTotal + quartTotal;

            await writer.WriteLineAsync($"Grand Total €{grandTotal:F2}");
        }

        private decimal CalculateContainerTotal(List<ContainerData> containers, string containerType)
        {
            decimal total = 0m;
            foreach (var container in containers)
            {
                if (container.ContainerType == containerType)
                {
                    total += container.Fee;
                }
            }
            return total;
        }

        private Container CreateContainer(string containerType)
        {
            switch (containerType)
            {
                case "FULL":
                    return new FullSizeContainer();
                case "HALF":
                    return new HalfSizeContainer();
                case "QUART":
                    return new QuarterSizeContainer();
                default:
                    return null;
            }
        }
    }
}