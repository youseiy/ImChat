

#include "Thread.h"





void ImChat::Thread::Start() {
    bIsRunning = true;
    m_thread = std::jthread(&Thread::Run, this);
}

void ImChat::Thread::Stop() {
    bIsRunning = false;
    if (m_thread.joinable()) m_thread.join();
}
