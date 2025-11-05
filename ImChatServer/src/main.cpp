
#include "ImChatLog.h"
#include "Server.h"

int main() {
    std::atomic<bool> running{true};

    ImChatLog::info("Welcome to ImChatServer!");

    ImChatLog::warn("Running on IP {}:{}",ImChat::IMCHAT_SERVER_IP.toString(),ImChat::IMCHAT_PORT);

    ImChat::Server Server;
    Server.runServer(ImChat::IMCHAT_PORT, running);





    return 0;

}
