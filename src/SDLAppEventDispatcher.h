#pragma once
#include <deque>
#include <iostream>

enum class AppEvents {
    RequestPlay,
    RequestMenu,
    RequestSettings,
    RequestExit,
    RequestWindowClose,
    KeyPress,
    MousePress,
};

struct AppEvent {
    AppEvents event;  
};

class AppEventDispatcher {
public:
    AppEventDispatcher() = default;
    ~AppEventDispatcher() = default;

    void Queue(const AppEvent&);
    bool Poll(AppEvent&);
private:
    std::deque<AppEvent> m_AppEventQueue;
};