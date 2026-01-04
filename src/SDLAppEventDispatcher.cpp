#include "SDLAppEventDispatcher.h"

void AppEventDispatcher::Queue(const AppEvent& event) {
    // should I search whether this event already queued
    m_AppEventQueue.emplace_back(event);
}

bool AppEventDispatcher::Poll(AppEvent& event) {
    if(m_AppEventQueue.empty()) {
        return false;
    }

    event = m_AppEventQueue.front();
    m_AppEventQueue.pop_front();
    // if std::vector not deque then below code is used;
    // m_AppEventQueue.erase(m_AppEventQueue.begin());
    return true;
}
