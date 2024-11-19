using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.IO;


//todo: ask, define maken voor tabel report grootte?

namespace ContainerShipping
{
    // Class to hold the state of the client session
    public class ClientSession
    {
        public string ExpectedCommand { get; set; } = "START"; // Initialize to START
        public Container CurrentContainer { get; set; } // To store the current container during the session
        public List<Container> ContainerRecords { get; set; } = new List<Container>(); // List to hold container records

        // Method to add container data
        public void AddContainer() {
            if (CurrentContainer != null) {
                ContainerRecords.Add(CurrentContainer);
                CurrentContainer = null;
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
            using StreamReader reader = new StreamReader(stream, Encoding.ASCII);
            using StreamWriter writer = new StreamWriter(stream, Encoding.ASCII) { AutoFlush = true };
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
        await GenerateReport(writer, session); // Generate report before closing
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
                if (session.CurrentContainer == null)
                {
                    await writer.WriteLineAsync("ERR;Failed to create container");
                    return; // Exit if container creation fails
                }

                session.ExpectedCommand = command == "FULL" ? "FRIDGE" : command == "HALF" ? "VOLUME" : "STOP";
                await writer.WriteLineAsync("ACK"); // Acknowledge TYPE

                // Prepare for next command based on type
                if (session.CurrentContainer is FullSizeContainer)
                    await writer.WriteLineAsync("FRIDGE"); // Prompt for fridge info for FULL
                else if (session.CurrentContainer is HalfSizeContainer)
                    await writer.WriteLineAsync("VOLUME"); // Prompt for volume for HALF
                else if (session.CurrentContainer is QuarterSizeContainer){
                    await writer.WriteLineAsync("ACK"); // Acknowledge QUART input and end session
                    session.ExpectedCommand = "START"; // Move to expecting TYPE
                    session.AddContainer();
                    await writer.WriteLineAsync("CONTAINER ADDED");
                }
            }
            else
            {
                await writer.WriteLineAsync("ERR;Invalid Type");
            }
            break;

        case "FRIDGE":
            if (session.CurrentContainer == null)
            {
                await writer.WriteLineAsync("ERR;No container available for fridge setup");
                return; // Exit if no container is available
            }

            if (command == "YES" || command == "NO")
            {
                session.CurrentContainer.IsRefrigerated = (command == "YES");
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
            if (session.CurrentContainer == null)
            {
                await writer.WriteLineAsync("ERR;No container available for weight input");
                return; // Exit if no container is available
            }

            if (int.TryParse(command, out int weight) && weight <= 20000)
            {
                session.CurrentContainer.Weight = weight; // Set the weight for FULL container
                await writer.WriteLineAsync("ACK");
                session.ExpectedCommand = "START"; // Move to expecting TYPE
                session.AddContainer();
                await writer.WriteLineAsync("CONTAINER ADDED");

            }
            else
            {
                await writer.WriteLineAsync("ERR;Weight Exceeded");
            }
            break;

        case "VOLUME":
            if (session.CurrentContainer == null)
            {
                await writer.WriteLineAsync("ERR;No container available for volume input");
                return; // Exit if no container is available
            }

            if (int.TryParse(command, out int volume) && volume <= 40)
            {
                session.CurrentContainer.Volume = volume; // Set the volume for HALF container
                await writer.WriteLineAsync("ACK");
                session.ExpectedCommand = "START"; // Move to expecting TYPE
                session.AddContainer();
                await writer.WriteLineAsync("CONTAINER ADDED");
            }
            else
            {
                await writer.WriteLineAsync("ERR;Volume Exceeded");
            }
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
            var fullTotal = CalculateContainerTotal(session.ContainerRecords, "FullSize");
            var halfTotal = CalculateContainerTotal(session.ContainerRecords, "HalfSize");
            var quartTotal = CalculateContainerTotal(session.ContainerRecords, "QuarterSize");

            await writer.WriteLineAsync("\n---------------------------------------------Report----------------------------------------------");

            // Full Size report
            await writer.WriteLineAsync(String.Format("|{0, -15}|{1, -15}|{2, -15}|{3, -15}|{4, -15}|{5, -15}|","Type", "ID", "Weight", "Volume", "Refrid", "Fee"));

            foreach (var record in session.ContainerRecords)
            {
                string weight = record.Weight.HasValue ? $"{record.Weight}kg" : "N/A";
                string volume = record.Volume.HasValue ? $"{record.Volume}m3" : "N/A";
                await writer.WriteLineAsync(String.Format("|{0, -15}|{1, -15}|{2, -15}|{3, -15}|{4, -15}|{5, -15}|", record.GetType(), record.SerialNumber, weight, volume, record.IsRefrigerated, $"€{record.CalculateFee():F2}"));
            }

            // Final report
            await writer.WriteLineAsync("-------------------------------------------------------------------------------------------------");
            await writer.WriteLineAsync(String.Format("|{0, -15}|{1, -15}|{2, -15}|{3, -15}|{4, -15}|{5, -15}|", "Full Total", "", "", "", "", $"€{fullTotal:F2}"));
            await writer.WriteLineAsync(String.Format("|{0, -15}|{1, -15}|{2, -15}|{3, -15}|{4, -15}|{5, -15}|", "Half Total", "", "", "", "", $"€{halfTotal:F2}"));
            await writer.WriteLineAsync(String.Format("|{0, -15}|{1, -15}|{2, -15}|{3, -15}|{4, -15}|{5, -15}|", "Quarter Total", "", "", "", "", $"€{quartTotal:F2}"));

            grandTotal = fullTotal + halfTotal + quartTotal;
            await writer.WriteLineAsync(String.Format("|{0, -15}|{1, -15}|{2, -15}|{3, -15}|{4, -15}|{5, -15}|", "Grand Total", "", "", "", "", $"€{grandTotal:F2}"));
            await writer.WriteLineAsync("-------------------------------------------------------------------------------------------------\n");
        }

        private decimal CalculateContainerTotal(List<Container> containers, string containerType)
        {
            decimal total = 0m;
            foreach (var container in containers)
            {
                if (container.GetType() == containerType)
                {
                    total += container.CalculateFee();
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