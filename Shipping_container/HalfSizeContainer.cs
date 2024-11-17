namespace ContainerShipping
{
    /// <summary>
    /// Represents a half-size container.
    /// </summary>
    public class HalfSizeContainer : Container
    {
        public const decimal FeePerM3 = 19.37m;
        public const int MaxVolume = 40;

        private int? _volume;  // Nullable volume to fit the abstract base class

        public override int? Volume
        {
            get => _volume;
            set
            {
                if (value.HasValue && value.Value > MaxVolume)
                {
                    throw new ExceededVolumeException("Volume Exceeded");
                }
                _volume = value;
            }
        }

        private int? _weight = null;  // Nullable weight, as weight is not used for this container type

        public override int? Weight
        {
            get => _weight;
            set
            {
                // Weight is not typically set for HalfSizeContainer, so you could throw an exception if desired.
                throw new InvalidOperationException("Weight is not applicable for HalfSizeContainer.");
            }
        }

        public override decimal CalculateFee()
        {
            if (!_volume.HasValue)
            {
                throw new InvalidOperationException("Volume must be set before calculating the fee.");
            }
            return _volume.Value * FeePerM3;
        }

        public override bool IsRefrigerated()
        {
            return false;  // Half-size containers are not refrigerated
        }
    }
}