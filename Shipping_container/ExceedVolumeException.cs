namespace Shipping_container;

/// <summary>
/// Exception thrown when a container's volume exceeds the allowed capacity.
/// </summary>
public class ExceededVolumeException : ContainerException
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ExceededVolumeException"/> class with a default message.
    /// </summary>
    public ExceededVolumeException()
        : base("The container's volume exceeds the allowed capacity.") { }

    /// <summary>
    /// Initializes a new instance of the <see cref="ExceededVolumeException"/> class with a custom message.
    /// </summary>
    /// <param name="message">The message that describes the error.</param>
    public ExceededVolumeException(string message)
        : base(message) { }

    /// <summary>
    /// Initializes a new instance of the <see cref="ExceededVolumeException"/> class with a custom message and inner exception.
    /// </summary>
    /// <param name="message">The message that describes the error.</param>
    /// <param name="inner">The inner exception that is the cause of the current exception.</param>
    public ExceededVolumeException(string message, Exception inner)
        : base(message, inner) { }
}