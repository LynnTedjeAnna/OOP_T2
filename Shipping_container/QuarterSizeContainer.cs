namespace Shipping_container
{
    /// <summary>
    /// Represents a quarter-size container.
    /// </summary>
    public class QuarterSizeContainer : Container
    {
        /// <summary>
        /// The fixed fee for a quarter-size container.
        /// </summary>
        private const decimal FixedFee = 1692.72m;

        /// <summary>
        /// Calculates the fee for the quarter-size container.
        /// </summary>
        /// <returns>
        /// The fixed fee for the quarter-size container.
        /// </returns>
        public override decimal CalculateFee()
        {
            return FixedFee;
        }

        /// <summary>
        /// Gets the type of the container.
        /// </summary>
        /// <returns>
        /// A string representing the container type (e.g., "QuarterSize").
        /// </returns>
        public override string GetType()
        {
            return "QuartSize";
        }

        /// <summary>
        /// Returns a string that represents the current quarter-size container.
        /// </summary>
        /// <returns>
        /// A string representing the quarter-size container with its properties.
        /// </returns>
        public override string ToString()
        {
            return String.Format("|{0, -10}|{1, -10}|{2, -10}|{3, -10}|{4, -10}|{5, -10}|{6, -10}", SerialNumber, GetType(), OriginCountry,"N/A", "N/A", "N/A", CalculateFee());
        }
    }
}