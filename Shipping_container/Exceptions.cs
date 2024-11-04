using System;

namespace ContainerShipping
{
    public class ContainerException : Exception
    {
        public ContainerException(string message) : base(message) { }
    }

    public class ExceededWeightException : ContainerException
    {
        public ExceededWeightException(string message) : base(message) { }
    }

    public class ExceededVolumeException : ContainerException
    {
        public ExceededVolumeException(string message) : base(message) { }
    }
}