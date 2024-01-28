#pragma once

#include <SDL.h>
#include <imgui.h>
#include "Main.hpp"

// TODO change app namespace
namespace ImGuiApp
{
namespace Gui
{

enum class Font : int
{
    Title,
    Version,
    OptionItem,
    OptionItemBold,
    Section,
    Text,
    TextBold,
    Debug,
    DebugProcHead,
    DebugProcHex,
    _COUNT_,
};

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

void initialize(const char* app_title);
void finalize();
void drawGui();

// sub modules
#ifdef _DEBUG
void drawDebugMenuBar(const ImVec2 viewport_pos);
void drawDebugContents(const int window_w, const int window_h, const State current_state);
#endif

} // Gui
} // ImGuiApp
