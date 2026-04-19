

#include <optional>

enum class StateId {
    Idle,
    Patrol,
    Tracking,
    Recovering,
    Error
};


class IState
{
private:
    StateId id;

public:
    StateId id() const { return id; }
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual std::optional<StateId> handleEvent() = 0;
};
