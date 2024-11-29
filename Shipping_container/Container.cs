namespace Shipping_container
{
    /// <summary>
    /// Represents a container for shipping, which serves as the base class for different container types.
    /// </summary>
    public abstract class Container
    {
        private static int _serialNumberCounter = 1000;

        /// <summary>
        /// Gets the unique serial number of the container.
        /// </summary>
        public int SerialNumber { get; }

        /// <summary>
        /// Gets or sets the description of the container.
        /// </summary>
        public string Description { get; set; }

        /// <summary>
        /// Gets or sets the origin country of the container.
        /// </summary>
        public string OriginCountry { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="Container"/> class,
        /// assigning a unique serial number to the container.
        /// </summary>
        protected Container()
        {
            SerialNumber = _serialNumberCounter++;
        }

        /// <summary>
        /// Calculates the fee associated with the container, to be implemented by subclasses.
        /// </summary>
        /// <returns>
        /// The calculated fee for the container.
        /// </returns>
        public abstract decimal CalculateFee();

        /// <summary>
        /// Gets the type of the container (e.g., "FullSize", "HalfSize", etc.), to be implemented by subclasses.
        /// </summary>
        /// <returns>
        /// A string representing the type of the container.
        /// </returns>
        public abstract string GetType();

        /// <summary>
        /// Returns a string representation of the container, including its serial number, description, and origin country.
        /// </summary>
        /// <returns>
        /// A string representing the container's details.
        /// </returns>
        public abstract string ToString();
    }
}