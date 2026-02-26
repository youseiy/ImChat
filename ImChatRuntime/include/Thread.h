#pragma once
#include <thread>


namespace ImChat {
    class Thread {
    public:

        Thread() = default;
        virtual ~Thread() {

        };

        Thread(const Thread&) = delete;
        Thread& operator=(const Thread&) = delete;

        Thread(Thread&&) noexcept = default;
        Thread& operator=(Thread&&) noexcept = default;


        virtual void Start();
        virtual void Run()=0;
        virtual void Stop();


    protected:
        std::jthread m_thread;

        std::atomic<bool> bIsRunning{false};
    };
}
