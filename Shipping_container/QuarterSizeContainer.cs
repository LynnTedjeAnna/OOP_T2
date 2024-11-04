namespace ContainerShipping
{
    /// <summary>
    /// Represents a quarter-size container.
    /// </summary>
    public class QuarterSizeContainer : Container
    {
        public const decimal FixedFee = 1692.72m;

        public override decimal CalculateFee()
        {
            return FixedFee;
        }
    }
}