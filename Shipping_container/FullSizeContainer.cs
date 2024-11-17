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
        private int? _volume = 0;  // Volume is fixed to 0

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

        // Volume is fixed to 0 for this container
        public override int? Volume
        {
            get => _volume;
            set
            {
                // Prevent modifying volume from outside
                _volume = 0;
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

        // Property to check if the container is refrigerated
        public override bool IsRefrigerated()
        {
            return _currentRefrig;
        }

        // Set refrigerated status
        public void SetRefrigerated(bool refrigerated)
        {
            _currentRefrig = refrigerated;
        }
    }
}