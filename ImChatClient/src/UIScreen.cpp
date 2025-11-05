//
// Created by theus on 21/08/2025.
//

#include "UIScreen.h"

#include <utility>
#include "Window.h"

namespace ImChat {

    UIScreen::UIScreen(const std::shared_ptr<Window>& InRenderWindow,std::string  InScreenName,Client& InClient) :
    m_owning_window(InRenderWindow),
    m_screen_name(std::move(InScreenName)),
    m_owning_client(InClient) {

    }

    Window* UIScreen::GetOwningWindow() const {
        return m_owning_window.get();
    }
}
