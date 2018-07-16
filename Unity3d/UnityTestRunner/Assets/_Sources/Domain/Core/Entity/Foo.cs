
namespace Domain.Core.Entity
{
    public interface Foo
    {
        void ChangeInternalState();
        void ChangeInternalState(int state);

        bool IsStateChanged();
        int GetCurrentState();
    }
}