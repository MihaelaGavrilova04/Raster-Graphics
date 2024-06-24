#pragma once

#include "Session.hpp"
#include "myVector.hpp"
#include "UniquePtr.hpp"
#include <iostream>

template<const int S>
class SessionHolder {
private:
    myVector<UniquePtr<Session<S>>> sessions;
    int nextSessionId = 1;
    int currentSessionId = -1;
public:
    SessionHolder()= default;

    int createSession();
    Session<S>* getSession(int sessionId);
    void removeSession(int sessionId);
    bool sessionExists(int sessionId) const;
    
    void saveAllSessions();
    void printAllSessionsInfo() const;
    void setCurrentSession(int sessionId);
    int getCurrentSessionId() const;
};

template<const int S>
int SessionHolder<S>::createSession() {
    sessions.pushBack(UniquePtr<Session<S>>(new Session<S>(nextSessionId)));
    return nextSessionId++;
}

template<const int S>
Session<S>* SessionHolder<S>::getSession(int sessionId) {
    int numSessions = sessions.getSize();
    for (int i = 0; i < numSessions; i++) {
        if (sessions[i]->getSessionId() == sessionId) {
            return sessions[i].get();
        }
    }
    return nullptr;
}

// check for session with given ID
template<const int S>
bool SessionHolder<S>::sessionExists(int sessionId) const {
    int numSessions = sessions.getSize();
    for (int i = 0; i < numSessions; i++) {
        if (sessions[i]->getSessionId() == sessionId) {
            return true;
        }
    }
    return false;
}

// remove a session by its ID
template<const int S>
void SessionHolder<S>::removeSession(int sessionId) {
    int numSessions = sessions.getSize();
    int indexToRemove = -1;

    for (int i = 0; i < numSessions; i++) {
        if (sessions[i]->getSessionId() == sessionId) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove != -1) {
        for (int i = indexToRemove; i < numSessions - 1; i++) {
            sessions[i] = std::move(sessions[i + 1]);
        }
        sessions.setSize(numSessions - 1);
    }
}

template<const int S>
void SessionHolder<S>::saveAllSessions()
{
    int numSessions = sessions.getSize();
    for (int i = 0; i < numSessions; i++) 
        sessions[i]->saveSession();
    
}


// print info for all sessions
template<const int S>
void SessionHolder<S>::printAllSessionsInfo() const {
    std::cout << "\n -Session Holder Information- \n";
    int numSessions = sessions.getSize();
    for (int i = 0; i < numSessions; i++) {
        sessions[i]->sessionInfo();
        std::cout << std::endl;
    }
}

template<const int S>
void SessionHolder<S>::setCurrentSession(int sessionId) 
{
    if (sessionExists(sessionId))
        currentSessionId = sessionId;
    else 
        throw std::logic_error("Session doesn't exist!\n");
}

template<const int S>
int SessionHolder<S>::getCurrentSessionId() const
{
    return currentSessionId;
}