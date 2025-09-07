
#include "ImChatLog.h"
#include "ImChatServer.h"

int main() {
    std::atomic<bool> running{true};

    ImChatLog::info("Welcome to ImChatServer!");

    ImChatLog::warn("Running on IP {}:{}",ImChat::IMCHAT_SERVER_IP.toString(),ImChat::IMCHAT_PORT);

    ImChat::ImChatServer Server;
    Server.runServer(ImChat::IMCHAT_PORT, running);





    return 0;

}
