using System;
using System.Collections.Generic; // For List<T>
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
        public string ContainerType { get; set; }
        public List<ContainerData> ContainerRecords { get; set; } = new List<ContainerData>(); // List to hold container records
        private int _containerIdCounter = 1000; // Start ID for containers

        // Method to add container data
        public void AddContainerData(string weight, string volume, string refrid, decimal fee)
        {
            ContainerRecords.Add(new ContainerData
            {
                Id = _containerIdCounter++,
                Weight = weight,
                Volume = volume,
                Refrid = refrid,
                Fee = fee
            });
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

        private async Task ProcessCommand(string command, StreamWriter writer, ClientSession session, TcpClient client) // Accept client here
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
                        session.ContainerType = command;
                        await writer.WriteLineAsync("ACK"); // Acknowledge TYPE

                        // Prepare for next command based on type
                        if (session.ContainerType == "FULL")
                        {
                            session.ExpectedCommand = "FRIDGE";
                            await writer.WriteLineAsync("FRIDGE"); // Prompt for fridge info
                        }
                        else if (session.ContainerType == "HALF")
                        {
                            session.ExpectedCommand = "VOLUME";
                            await writer.WriteLineAsync("VOLUME"); // Prompt for volume
                        }
                        else // QUART
                        {
                            await writer.WriteLineAsync("ACK"); // Acknowledge QUART input
                            session.ExpectedCommand = "END"; // No more input needed for QUART
                        }
                    }
                    else
                    {
                        await writer.WriteLineAsync("ERR;Invalid Type");
                    }
                    break;

                case "FRIDGE":
                    if (command == "YES" || command == "NO")
                    {
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
                        decimal fee = CalculateFee("FULL", weight); // Calculate fee based on weight
                        session.AddContainerData($"{weight}kg", "N/A", "YES", fee); // Add container data
                        await writer.WriteLineAsync("ACK"); // Acknowledge the weight input
                        session.ExpectedCommand = "END"; // All data received for FULL
                        await writer.WriteLineAsync("ACK"); // Acknowledge ending the session
                    }
                    else
                    {
                        await writer.WriteLineAsync("ERR;Weight Exceeded");
                    }
                    break;

                case "VOLUME":
                    if (int.TryParse(command, out int volume) && volume <= 40)
                    {
                        decimal fee = CalculateFee("HALF", volume); // Calculate fee based on volume
                        session.AddContainerData("N/A", $"{volume}m3", "N/A", fee); // Add container data
                        await writer.WriteLineAsync("ACK"); // Acknowledge the volume input
                        session.ExpectedCommand = "END"; // All data received for HALF
                        await writer.WriteLineAsync("ACK"); // Acknowledge ending the session
                    }
                    else
                    {
                        await writer.WriteLineAsync("ERR;Volume Exceeded");
                    }
                    break;

                case "END":
                    await writer.WriteLineAsync("ACK"); // Acknowledge ending the session
                    break;

                default:
                    await writer.WriteLineAsync("ERR;Unknown Command");
                    break;
            }

            // If the command has reached END, close the connection
            if (session.ExpectedCommand == "END")
            {
                Console.WriteLine("Ending session and closing connection.");
                await Task.Delay(100); // Small delay before closing to ensure client gets the last response
                client.Close();
            }
        }

        private async Task GenerateReport(StreamWriter writer, ClientSession session)
        {
            decimal grandTotal = 0m; // Initialize grand total

            // Calculate totals per container type
            var fullTotal = CalculateContainerTotal(session.ContainerRecords, "FULL");
            var halfTotal = CalculateContainerTotal(session.ContainerRecords, "HALF");
            var quartTotal = CalculateContainerTotal(session.ContainerRecords, "QUART");

            // Generate the report
            await writer.WriteLineAsync("\n--- Report ---");

            // Full Size report
            await writer.WriteLineAsync("Id   Weight    Volume   Refrid   Fee");
            foreach (var record in session.ContainerRecords)
            {
                if (record.Refrid != null && record.Refrid != "N/A" && record.Refrid != "")
                {
                    await writer.WriteLineAsync($"{record.Id} {record.Weight} {record.Volume ?? "N/A"} {record.Refrid} €{record.Fee:F2}");
                }
            }
            await writer.WriteLineAsync($"Total €{fullTotal:F2}\n");

            // Half Size report
            await writer.WriteLineAsync("Id   Weight    Volume   Refrid   Fee");
            foreach (var record in session.ContainerRecords)
            {
                if (record.Volume != null && record.Volume != "N/A")
                {
                    await writer.WriteLineAsync($"{record.Id} {record.Weight ?? "N/A"} {record.Volume} {record.Refrid ?? "N/A"} €{record.Fee:F2}");
                }
            }
            await writer.WriteLineAsync($"Total €{halfTotal:F2}\n");

            // Quart Size report (you can implement additional logic if needed)
            await writer.WriteLineAsync("Total €{quartTotal:F2}");
        }

        // Method to calculate the fee for the container
        private decimal CalculateFee(string containerType, int value)
        {
            decimal fee = 0;

            // Set fee rates based on container type
            switch (containerType)
            {
                case "FULL":
                    fee = value * 1.02m; // Example fee rate for FULL container
                    break;
                case "HALF":
                    fee = value * 19.34m; // Example fee rate for HALF container (example rate)
                    break;
                case "QUART":
                    fee = 1692.72m; // Example flat rate for QUART container
                    break;
            }

            // Round fee to 2 decimal places
            return Math.Round(fee, 2);
        }

        // Method to calculate the total fee for a specific container type
        private decimal CalculateContainerTotal(List<ContainerData> containerRecords, string containerType)
        {
            decimal total = 0m;

            // Calculate total fee for the specified container type
            foreach (var record in containerRecords)
            {
                if (containerType == "FULL" && record.Weight != null)
                {
                    total += record.Fee;
                }
                else if (containerType == "HALF" && record.Volume != null && record.Volume != "N/A")
                {
                    total += record.Fee;
                }
                else if (containerType == "QUART" && record.Volume == null)
                {
                    total += record.Fee;
                }
            }

            return total;
        }
    }
}