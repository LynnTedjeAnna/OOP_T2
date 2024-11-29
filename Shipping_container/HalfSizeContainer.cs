namespace Shipping_container
{
    /// <summary>
    /// Represents a half-size container.
    /// </summary>
    public class HalfSizeContainer : Container
    {
        /// <summary>
        /// The fee per cubic meter for a half-size container.
        /// </summary>
        public const decimal FeePerM3 = 19.37m;

        /// <summary>
        /// The maximum volume allowed for a half-size container.
        /// </summary>
        public const int MaxVolume = 40;

        private int _volume;

        /// <summary>
        /// Gets or sets the volume of the container.
        /// </summary>
        /// <value>
        /// The volume of the container.
        /// </value>
        /// <exception cref="ExceededVolumeException">Thrown when the volume exceeds the maximum allowed.</exception>
        public int Volume
        {
            get => _volume;
            set
            {
                if (value > MaxVolume)
                {
                    throw new ExceededVolumeException("Volume Exceeded");
                }
                _volume = value;
            }
        }

        /// <summary>
        /// Calculates the fee for the half-size container based on its volume.
        /// </summary>
        /// <returns>
        /// The fee for the container.
        /// </returns>
        public override decimal CalculateFee()
        {
            return _volume * FeePerM3;
        }

        /// <summary>
        /// Gets the type of the container.
        /// </summary>
        /// <returns>
        /// A string representing the container type (e.g., "HalfSize").
        /// </returns>
        public override string GetType()
        {
            return "HalfSize";
        }

        /// <summary>
        /// Returns a string that represents the current half-size container.
        /// </summary>
        /// <returns>
        /// A string representing the half-size container with its properties.
        /// </returns>
        public override string ToString()
        {
            string volume = $"{Volume}m3";
            return String.Format("|{0, -10}|{1, -10}|{2, -10}|{3, -10}|{4, -10}|{5, -10}|{5, -10}", SerialNumber, GetType(), OriginCountry, "N/A","N/A", volume, CalculateFee().ToString("F2"));
        }
    }
}