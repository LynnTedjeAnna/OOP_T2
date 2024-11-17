namespace ContainerShipping
{
    /// <summary>
    /// Represents a quarter-size container.
    /// </summary>
    public class QuarterSizeContainer : Container
    {
        public const decimal FixedFee = 1692.72m;

        private int? _weight = null;  // Nullable weight for consistency with the base class
        private int? _volume = null;  // Nullable volume for consistency with the base class
        private bool _currentRefrig;  // Field to store the refrigerated status

        // Quarter-size containers don't use weight or volume, so we'll just return null here
        public override int? Weight
        {
            get => _weight;
            set
            {
                // Quarter-size containers should not have weight set, so throw an exception if attempted
                throw new InvalidOperationException("Weight is not applicable for QuarterSizeContainer.");
            }
        }

        public override int? Volume
        {
            get => _volume;
            set
            {
                // Quarter-size containers should not have volume set, so throw an exception if attempted
                throw new InvalidOperationException("Volume is not applicable for QuarterSizeContainer.");
            }
        }

        // Implementing the IsRefrigerated property
        public override bool IsRefrigerated
        {
            get => _currentRefrig;    // Return the current refrigerated status
            set => _currentRefrig = value;  // Set the refrigerated status
        }

        public override decimal CalculateFee()
        {
            return FixedFee;
        }

        public override string GetType()
        {
            return "QuarterSize";
        }
    }
}