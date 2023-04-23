//
// Created by smokfyz on 14.04.19.
//
#include <iostream>
#include <Ultralight/platform/Platform.h>
#include <Ultralight/platform/Config.h>
#include <Ultralight/Renderer.h>
#include "GUI.h"

using namespace std;

GUI::GUI() {
    app_ = App::Create();

    window_ = Window::Create(app_->main_monitor(), 1280, 720, false,
                             kWindowFlags_Resizable | kWindowFlags_Titled | kWindowFlags_Maximizable);
    window_->SetTitle("Xgame");
    app_->set_window(*(window_.get()));

    // Create the UI
    ui_ = make_unique<UI>(*(window_.get()));
    window_->set_listener(ui_.get());
}

GUI::~GUI() {
    window_->set_listener(nullptr);

    ui_.reset();

    window_ = nullptr;
    app_ = nullptr;
}

void GUI::run() {
    app_->Run();
}