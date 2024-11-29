using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Shipping_container
{

    public class ShippingServer
    {
        private List<Container> ContainerRecords { get; set; } = new List<Container>(); // List to hold container records
        private readonly TcpListener _listener;

        /// <summary>
        /// Initializes a new instance of the ShippingServer class and sets up the listener on port 23.
        /// </summary>
        public ShippingServer()
        {
            _listener = new TcpListener(IPAddress.Any, 23);
        }

        /// <summary>
        /// Starts the server and listens for incoming client connections.
        /// </summary>
        public Task Start()
        {
            _listener.Start();
            Console.WriteLine("Server started on port 23...");

            while (true)
            {
                TcpClient client = _listener.AcceptTcpClient();
                Task.Run(() => HandleClient(client));
            }
        }

        /// <summary>
        /// Handles communication with a connected client.
        /// </summary>
        /// <param name="client">The connected TcpClient instance.</param>
        private void HandleClient(TcpClient client)
        {
            using NetworkStream stream = client.GetStream();
            using StreamReader reader = new StreamReader(stream, Encoding.ASCII);
            using StreamWriter writer = new StreamWriter(stream, Encoding.ASCII) { AutoFlush = true };
            writer.WriteLine("WELCOME");

            try
            {
                string line = reader.ReadLine();
                while (line != null)
                {
                    ProcessCommand(line.Trim().ToUpper(), writer, client, reader); // Pass client to the method
                }
            }
            catch (Exception ex)
            {
                writer.WriteLine($"ERR;{ex.Message}");
            }
        }

        /// <summary>
        /// Handles logic for creating a full-size container.
        /// </summary>
        /// <param name="writer">StreamWriter to send responses to the client.</param>
        /// <param name="reader">StreamReader to receive input from the client.</param>
        private void FullLogic(StreamWriter writer, StreamReader reader)
        {
            // Step 1: Prompt for weight
            writer.WriteLine("WEIGHT"); // Prompt client for weight
            string weightInput = reader.ReadLine(); // Read weight from client

            if (!int.TryParse(weightInput, out int weight))
            {
                throw new InvalidOperationException("Invalid weight input from client.");
            }
            if (weight > FullSizeContainer.MaxWeight)
            {
                throw new ExceededWeightException("Weight exceeds maximum allowed for FullSizeContainer.");
            }
            if (weight < 0)
            {
                throw new ExceededVolumeException("Weight exceeds minimum allowed for FullSizeContainer.");
            }

            // Step 2: Prompt for refrigeration status
            writer.WriteLine("FRIDGE"); // Prompt client for refrigeration status
            string fridgeInput = reader.ReadLine();
            if (fridgeInput == null)
            {
                throw new InvalidOperationException("Invalid refrigeration input.");
            }
            fridgeInput = fridgeInput.Trim().ToUpper();

            bool isRefrigerated = false;
            if (fridgeInput == "NO")
            {
                isRefrigerated = false;
            }
            else if (fridgeInput == "YES")
            {
                isRefrigerated = true;
            }
            else
            {
                throw new InvalidOperationException("Invalid refrigeration input.");
            }

            // Step 3: Create and add the container
            FullSizeContainer fullSizeContainer = new FullSizeContainer
            {
                Weight = weight,
                IsRefrigerated = isRefrigerated,
                OriginCountry = "Unknown"           // Origin
            };

            ContainerRecords.Add(fullSizeContainer); // Add to the container records

            // Step 4: Acknowledge success
            writer.WriteLine("ACK");
        }

        /// <summary>
        /// Handles logic for creating a half-size container.
        /// </summary>
        /// <param name="writer">StreamWriter to send responses to the client.</param>
        /// <param name="reader">StreamReader to receive input from the client.</param>
        private void HalfLogic(StreamWriter writer, StreamReader reader)
        {
            // Step 1: Prompt for weight
            writer.WriteLine("VOLUME"); // Prompt client for weight
            string volumeInput = reader.ReadLine(); // Read weight from client

            if (!int.TryParse(volumeInput, out int volume))
            {
                throw new InvalidOperationException("Invalid volume input from client.");
            }
            if (volume > HalfSizeContainer.MaxVolume)
            {
                throw new ExceededVolumeException("Volume exceeds maximum allowed for HalfSizeContainer.");
            }
            if (volume < 0)
            {
                throw new ExceededVolumeException("Volume exceeds minimum allowed for HalfSizeContainer.");
            }

            // Step 3: Create and add the container
            HalfSizeContainer halfSizeContainer = new HalfSizeContainer()
            {
                Volume = volume,
                OriginCountry = "Unknown"           // Origin
            };

            ContainerRecords.Add(halfSizeContainer); // Add to the container records

            // Step 4: Acknowledge success
            writer.WriteLine("ACK");
        }

        /// <summary>
        /// Processes a client command and performs the appropriate actions.
        /// </summary>
        /// <param name="command">The command received from the client.</param>
        /// <param name="writer">StreamWriter to send responses to the client.</param>
        /// <param name="client">The TcpClient connection instance.</param>
        /// <param name="reader">StreamReader to receive input from the client.</param>
        private void ProcessCommand(string command, StreamWriter writer, TcpClient client, StreamReader reader)
        {
            if (command == "START")
            {
                writer.WriteLine("TYPE"); // Prompt for type
                string typeInput = reader.ReadLine(); // Read type from client
                if (typeInput == null)
                {
                    throw new InvalidOperationException("Invalid type input.");
                }

                switch (typeInput.Trim().ToUpper())
                {
                    case "FULL":
                        FullLogic(writer, reader);
                        client.Close();
                        break;
                    case "HALF":
                        HalfLogic(writer, reader);
                        client.Close();
                        break;
                    case "QUART":
                        writer.WriteLine("ACK");
                        ContainerRecords.Add(new QuarterSizeContainer()
                        {
                            OriginCountry = "Unknown"
                        });
                        client.Close();
                        break;
                    default:
                        throw new ContainerException("ERROR");
                }
            }
            else if (command == "STOP")
            {
                writer.WriteLine("ACK");
                GenerateReport(writer);
                client.Close();
            }
            else
            {
                throw new ContainerException("ERROR INVALID COMMAND");
            }
        }

        /// <summary>
        /// Generates a report summarizing all container records.
        /// </summary>
        /// <param name="writer">StreamWriter to send the report to the client.</param>
        private void GenerateReport(StreamWriter writer)
        {
            decimal fullSizeTotal = 0, halfSizeTotal = 0, quarterSizeTotal = 0, grandTotal = 0;

            writer.WriteLine("\n--------------------------------------------Report---------------------------------------------");
            writer.WriteLine(String.Format("|{0, -10}|{1, -10}|{2, -10}|{3, -10}|{4, -10}|{5, -10}|{6, -10}", "ID", "Type", "Origin","Refrig", "Weight", "Volume", "Fee"));

            foreach (Container container in ContainerRecords)
            {
                writer.WriteLine(container.ToString()); // Call the ToString method

                decimal fee = container.CalculateFee();

                switch (container.GetType())
                {
                    case "FullSize":
                        fullSizeTotal += fee;
                        break;
                    case "HalfSize":
                        halfSizeTotal += fee;
                        break;
                    case "QuarterSize":
                        quarterSizeTotal += fee;
                        break;
                }
            }

            grandTotal = fullSizeTotal + halfSizeTotal + quarterSizeTotal;

            writer.WriteLine("-----------------------------------------------------------------------------------------------");
            writer.WriteLine($"Full Size Total: €{fullSizeTotal:F2}");
            writer.WriteLine($"Half Size Total: €{halfSizeTotal:F2}");
            writer.WriteLine($"Quarter Size Total: €{quarterSizeTotal:F2}");
            writer.WriteLine($"Grand Total: €{grandTotal:F2}");
            writer.WriteLine("-----------------------------------------------------------------------------------------------");
        }
    }
}