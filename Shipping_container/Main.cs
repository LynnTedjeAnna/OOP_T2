using ContainerShipping;

public static class Program
{
    public static async Task Main(string[] args)
    {
        var server = new ShippingServer(23); // Start the server on port 23
        await server.StartAsync(); // Start the server asynchronously
    }
}