using System;
using System.Threading.Tasks;

namespace ContainerShipping
{
    class Program
    {
        static async Task Main(string[] args)
        {
            ShippingServer server = new ShippingServer(23);
            await server.StartAsync();
        }
    }
}
