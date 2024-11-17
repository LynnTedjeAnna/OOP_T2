namespace ContainerShipping
{
    /// <summary>
    /// Represents a full-size container.
    /// </summary>
    public class FullSizeContainer : Container
    {
        public const decimal FeePerKg = 0.91m;
        public const int MaxWeight = 20000;
        private bool _currentRefrig;

        private int? _weight;  // Nullable weight to fit the abstract base class
        private int? _volume = null;  // Volume is fixed to null

        // Implementing the IsRefrigerated property
        public override bool IsRefrigerated
        {
            get => _currentRefrig;    // Return the current refrigerated status
            set => _currentRefrig = value;  // Set the refrigerated status
        }

        public override int? Weight
        {
            get => _weight;
            set
            {
                if (value.HasValue && value.Value > MaxWeight)
                {
                    throw new ExceededWeightException("Weight Exceeded");
                }
                _weight = value;
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

        // Fee calculation based on weight, and refrigerated status
        public override decimal CalculateFee()
        {
            if (!_weight.HasValue)
            {
                throw new InvalidOperationException("Weight must be set before calculating the fee.");
            }

            decimal fee = _weight.Value * FeePerKg;
            if (_currentRefrig)
            {
                fee *= 1.08m;  // Additional 8% for refrigerated containers
            }
            return fee;
        }

        // Override GetType to return a custom string
        public override string GetType()
        {
            return "FullSize";
        }
    }
}