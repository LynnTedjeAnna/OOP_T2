namespace ContainerShipping
{
    /// <summary>
    /// Represents a half-size container.
    /// </summary>
    public class HalfSizeContainer : Container
    {
        public const decimal FeePerM3 = 19.37m;
        public const int MaxVolume = 40;
        private int _volume;

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

        public override decimal CalculateFee()
        {
            return Volume * FeePerM3;
        }
    }
}