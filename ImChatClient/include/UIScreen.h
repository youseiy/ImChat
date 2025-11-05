#pragma once
#include <memory>
#include <string>

#include "Client.h"


namespace ImChat {
    class Window;

    class UIScreen {
    public:
        explicit UIScreen(const std::shared_ptr<Window>& InRenderWindow,std::string  InScreenName,Client& InClient);

        virtual ~UIScreen() = default;
        virtual void Render() = 0;


    protected:
        [[nodiscard]] Window* GetOwningWindow() const;

        std::string m_screen_name;

        std::shared_ptr<Window> m_owning_window;

        Client& m_owning_client;
    };
}
