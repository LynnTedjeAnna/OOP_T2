namespace Shipping_container;

public static class Program
{
    public static void Main(string[] args)
    {
        var server = new ShippingServer(); // Start the server on port 23
        server.Start(); // Start the server asynchronously
    }
}