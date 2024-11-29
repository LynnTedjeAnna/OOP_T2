namespace Shipping_container
{
    /// <summary>
    /// Represents a base exception for container-related errors.
    /// </summary>
    public class ContainerException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ContainerException"/> class with a default message.
        /// </summary>
        public ContainerException() 
            : base("An error occurred with the container.") { }

        /// <summary>
        /// Initializes a new instance of the <see cref="ContainerException"/> class with a custom message.
        /// </summary>
        /// <param name="message">The message that describes the error.</param>
        public ContainerException(string message) 
            : base(message) { }

        /// <summary>
        /// Initializes a new instance of the <see cref="ContainerException"/> class with a custom message and inner exception.
        /// </summary>
        /// <param name="message">The message that describes the error.</param>
        /// <param name="inner">The inner exception that is the cause of the current exception.</param>
        public ContainerException(string message, Exception inner) 
            : base(message, inner) { }
    }
}