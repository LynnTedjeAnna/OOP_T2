namespace ContainerShipping
{
    /// <summary>
    /// Represents a full-size container.
    /// </summary>
    public class FullSizeContainer : Container
    {
        public const decimal FeePerKg = 0.91m;
        public const int MaxWeight = 20000;
        public bool IsRefrigerated { get; set; }
        private int _weight;

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

        public override decimal CalculateFee()
        {
            decimal fee = Weight * FeePerKg;
            if (IsRefrigerated)
            {
                fee *= 1.08m;  // Additional 8% for refrigerated containers
            }
            return fee;
        }
    }
}