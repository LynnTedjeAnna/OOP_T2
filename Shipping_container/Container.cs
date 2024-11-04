using System;

namespace ContainerShipping
{
    /// <summary>
    /// Base class for all containers.
    /// </summary>
    public abstract class Container
    {
        private static int _serialNumberCounter = 1000;

        public int SerialNumber { get; }
        public string Description { get; set; }
        public string OriginCountry { get; set; }

        protected Container()
        {
            SerialNumber = _serialNumberCounter++;
        }

        /// <summary>
        /// Abstract method to calculate the container fee.
        /// </summary>
        /// <returns>Fee as a decimal</returns>
        public abstract decimal CalculateFee();
    }
}