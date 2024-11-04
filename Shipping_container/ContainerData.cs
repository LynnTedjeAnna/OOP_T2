using System;

namespace ContainerShipping
{
    // Class to represent container data
    public class ContainerData
    {
        public int Id { get; set; }            // Container ID
        public string Weight { get; set; }      // Weight of the container
        public string Volume { get; set; }      // Volume of the container
        public string Refrid { get; set; }      // Refrigeration status (YES/NO)
        public decimal Fee { get; set; }        // Fee for the container
    }
}