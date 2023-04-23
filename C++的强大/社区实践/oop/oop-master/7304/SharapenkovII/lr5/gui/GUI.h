//
// Created by smokfyz on 14.04.19.
//

#ifndef XGAME_GUI_H
#define XGAME_GUI_H

#include <AppCore/AppCore.h>
#include "UI.h"

using namespace ultralight;


class GUI {
    RefPtr<App> app_;
    RefPtr<Window> window_;
    std::unique_ptr<UI> ui_;

public:
    GUI();
    virtual ~GUI();

    virtual void run();
};


#endif //XGAME_GUI_H
