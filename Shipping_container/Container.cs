public abstract class Container
{
    private static int _serialNumberCounter = 1000;

    public int SerialNumber { get; }
    public string Description { get; set; }
    public string OriginCountry { get; set; }
    public abstract int? Weight { get; set; }
    public abstract int? Volume { get; set; }
    public abstract bool IsRefrigerated { get; set; }

    protected Container()
    {
        SerialNumber = _serialNumberCounter++;
    }

    // Abstract method that will be overridden in subclasses
    public abstract decimal CalculateFee();
    public abstract string GetType();
}