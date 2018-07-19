using NUnit.Framework;

namespace Domain.Core.Entity.Test
{
    class FooImplTest
    {
        [Test]
        public void StateChanges()
        {

            Foo foo = new FooImpl();

            Assert.Equals(1, 1);
        }
    }
}