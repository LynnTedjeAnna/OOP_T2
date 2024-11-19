
using System;
using Xunit;
using ContainerShipping;

namespace ContainerShippingTests
{
    public class HalfSizeContainerTests
    {
        [Fact]
        public void SetVolume_ValidVolume_SetsVolume()
        {
            // Arrange
            var container = new HalfSizeContainer();
            int validVolume = 30;

            // Act
            container.Volume = validVolume;

            // Assert
            Assert.Equal(validVolume, container.Volume);
        }

        [Fact]
        public void SetVolume_ExceedMaxVolume_ThrowsException()
        {
            // Arrange
            var container = new HalfSizeContainer();
            int invalidVolume = HalfSizeContainer.MaxVolume + 1;

            // Act & Assert
            Assert.Throws<ExceededVolumeException>(() => container.Volume = invalidVolume);
        }

        [Fact]
        public void CalculateFee_ValidVolume_ReturnsCorrectFee()
        {
            // Arrange
            var container = new HalfSizeContainer();
            container.Volume = 20;
            decimal expectedFee = 20 * HalfSizeContainer.FeePerM3;

            // Act
            var fee = container.CalculateFee();

            // Assert
            Assert.Equal(expectedFee, fee);
        }

        [Fact]
        public void CalculateFee_VolumeNotSet_ThrowsException()
        {
            // Arrange
            var container = new HalfSizeContainer();

            // Act & Assert
            Assert.Throws<InvalidOperationException>(() => container.CalculateFee());
        }

        [Fact]
        public void SetWeight_ThrowsInvalidOperationException()
        {
            // Arrange
            var container = new HalfSizeContainer();

            // Act & Assert
            Assert.Throws<InvalidOperationException>(() => container.Weight = 100);
        }

        [Fact]
        public void SetIsRefrigerated_UpdatesRefrigerationStatus()
        {
            // Arrange
            var container = new HalfSizeContainer();

            // Act
            container.IsRefrigerated = true;

            // Assert
            Assert.True(container.IsRefrigerated);
        }

        [Fact]
        public void GetType_ReturnsHalfSize()
        {
            // Arrange
            var container = new HalfSizeContainer();

            // Act
            var type = container.GetType();

            // Assert
            Assert.Equal("HalfSize", type);
        }
    }
}
