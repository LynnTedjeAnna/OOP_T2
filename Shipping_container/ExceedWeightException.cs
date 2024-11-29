namespace Shipping_container;


/// <summary>
/// Exception thrown when a container's weight exceeds the allowed limit.
/// </summary>
public class ExceededWeightException : ContainerException
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ExceededWeightException"/> class with a default message.
    /// </summary>
    public ExceededWeightException()
        : base("The container's weight exceeds the allowed limit.") { }

    /// <summary>
    /// Initializes a new instance of the <see cref="ExceededWeightException"/> class with a custom message.
    /// </summary>
    /// <param name="message">The message that describes the error.</param>
    public ExceededWeightException(string message)
        : base(message) { }

    /// <summary>
    /// Initializes a new instance of the <see cref="ExceededWeightException"/> class with a custom message and inner exception.
    /// </summary>
    /// <param name="message">The message that describes the error.</param>
    /// <param name="inner">The inner exception that is the cause of the current exception.</param>
    public ExceededWeightException(string message, Exception inner)
        : base(message, inner) { }
}