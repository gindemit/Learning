using NUnit.Framework;

namespace Domain.Core.Entity.Test
{
    class FooImplTest
    {
        [Test]
        public void StateChanges()
        {
            Foo foo = new FooImpl();
            Assert.AreEqual(foo.GetCurrentState(), int.MinValue);

            foo.ChangeInternalState();
            Assert.Greater(foo.GetCurrentState(), int.MinValue);
        }
    }
}