namespace Shipping_container
{
    /// <summary>
    /// Represents a full-size container.
    /// </summary>
    public class FullSizeContainer : Container
    {
        /// <summary>
        /// The fee per kilogram for a full-size container.
        /// </summary>
        public const decimal FeePerKg = 0.91m;

        /// <summary>
        /// The maximum weight allowed for a full-size container.
        /// </summary>
        public const int MaxWeight = 20000;

        private bool _currentRefrig;
        private int _weight;

        /// <summary>
        /// Gets or sets a value indicating whether the container is refrigerated.
        /// </summary>
        /// <value>
        /// <c>true</c> if the container is refrigerated; otherwise, <c>false</c>.
        /// </value>
        public bool IsRefrigerated
        {
            get => _currentRefrig;          // Return the current refrigerated status
            set => _currentRefrig = value;  // Set the refrigerated status
        }

        /// <summary>
        /// Gets or sets the weight of the container.
        /// </summary>
        /// <value>
        /// The weight of the container.
        /// </value>
        /// <exception cref="ExceededWeightException">Thrown when the weight exceeds the maximum allowed.</exception>
        public int Weight
        {
            get => _weight;
            set
            {
                if (value > MaxWeight)
                {
                    throw new ExceededWeightException("Weight Exceeded");
                }
                _weight = value;
            }
        }

        /// <summary>
        /// Calculates the fee for the full-size container based on its weight and refrigeration status.
        /// </summary>
        /// <returns>
        /// The fee for the container.
        /// </returns>
        public override decimal CalculateFee()
        {
            decimal fee = _weight * FeePerKg;
            if (_currentRefrig)
            {
                fee *= 1.08m;  // Additional 8% for refrigerated containers
            }
            return fee;
        }

        /// <summary>
        /// Gets the type of the container.
        /// </summary>
        /// <returns>
        /// A string representing the container type (e.g., "FullSize").
        /// </returns>
        public override string GetType()
        {
            return "FullSize";
        }

        /// <summary>
        /// Returns a string that represents the current full-size container.
        /// </summary>
        /// <returns>
        /// A string representing the full-size container with its properties.
        /// </returns>
        public override string ToString()
        {
            string weight = $"{Weight}kg";
            string refrigerated = IsRefrigerated ? "YES" : "NO";
            return String.Format("|{0, -10}|{1, -10}|{2, -10}|{3, -10}|{4, -10}|{5, -10}|{6, -10}", SerialNumber, GetType(), OriginCountry,refrigerated, weight, "N/A", CalculateFee().ToString("F2"));
            //"ID", "Type", "Origin", "Weight", "Volume", "Fee"
        }
    }
}