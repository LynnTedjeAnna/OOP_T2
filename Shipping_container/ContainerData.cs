public class ContainerData
{
    public int Id { get; set; }
    public int? Weight { get; set; }
    public int? Volume { get; set; }
    public string Refrid { get; set; } // Store "YES" or "NO" as a string here
    public decimal Fee { get; set; }
    public string ContainerType { get; set; } // This stores the name of the container type
}