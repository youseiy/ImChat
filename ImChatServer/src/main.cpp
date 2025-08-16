#include <iostream>
#include <thread>
#include "ImChatServer.h"

int main() {

    // Run the server in its own thread
    std::thread serverThread([](){
        ImChat::Server::runServer(5000);
    });

    // Optional: main thread can do other things
    std::cout << "Server is running in a separate thread.\n";
    std::cout << "Press Enter to stop...\n";
    std::cin.get(); // wait for user input



    // Join the thread before exiting
    serverThread.join();

    return 0;

}
