using System;
using Xunit;

namespace Shipping_container.Tests
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

            // Assert
            Assert.Equal(0, container.CalculateFee());
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
