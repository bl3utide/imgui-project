﻿/*
    ImGui Project
    v0.1

    - Dependencies
      SDL       2.0.10
      imgui     1.87 dock
      plog      1.1.10

    - Create project template
      Project -> Export Template -> Project Template

    - Create a new project from that project template

    - Copy include and lib directories from template project
*/
/*
    (Project Name)
    Copyright (C) 20xx bl3utide <bl3utide@gmail.com>
*/
#pragma once

// TODO change app namespace
namespace ImGuiApp
{

#define DEF_APP_NAME        "ImGuiProject"      // TODO fix app name
#define DEF_APP_VERSION     "1.0"
#define DEF_APP_DEV_BY      "bl3utide"
#define DEF_APP_DEV_YR      2024                // TODO fix dev year
#define DEF_APP_TITLE       "ImGui Project"     // TODO fix app title

enum class State : int
{
    InitInternalData,
    Idle,
    None,
    _COUNT_
};

extern bool has_error;
extern std::string error_message;
extern bool showing_error_message;
#ifdef _DEBUG
extern const char* STATE_STR[static_cast<int>(State::_COUNT_)];
#endif

State getState();
#ifdef _DEBUG
State getNextState();
#endif
void setNextState(State state);
std::string getAppVersion();
std::string getAppCopyright();
std::string getAppTitle();
void setAppError(const std::string& message);

} // ImGuiApp
