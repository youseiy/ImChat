
#pragma once
#include "UIScreen.h"


namespace ImChat {
    class UIChatInstance : public UIScreen{
    public:
        UIChatInstance(const std::shared_ptr<Window> &InRenderWindow, const std::string &InScreenName,Client& InClient)
            : UIScreen{InRenderWindow, InScreenName,InClient} {
        }

        void Render() override;

    private:

    };

}

