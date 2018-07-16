

namespace Domain.Core.Entity
{
    internal class FooImpl : Foo
    {
        const int StateDefault = int.MinValue;
        private int state = StateDefault;

        public void ChangeInternalState()
        {
            System.Random random = new System.Random();
            state = random.Next();
        }

        public void ChangeInternalState(int state)
        {
            this.state = state;
        }

        public int GetCurrentState()
        {
            return state;
        }

        public bool IsStateChanged()
        {
            return state != StateDefault;
        }
    }
}
