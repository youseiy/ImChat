#pragma once
#include "Thread.h"
#include "Window.h"


namespace ImChat{
    class ChatThread : public Thread {
    public:
        ChatThread() : Thread() {

        }
        ~ChatThread() = default;

        virtual void Start() override;
        virtual void Run() override;
        virtual void Stop() override;

        // Enable move
        ChatThread(ChatThread&&)  = default;
        ChatThread& operator=(ChatThread&&)  = default;


    private:
        std::shared_ptr<ImChat::Window> window;
    };
};
