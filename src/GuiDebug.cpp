#ifdef _DEBUG
#include "Gui.hpp"
#include "GuiUtil.hpp"

// TODO change app namespace
namespace ImGuiApp
{
namespace Gui
{

// private
bool _show_debug_menu_bar = true;
bool _show_demo_window = false;
bool _show_debug_window = false;

void drawDebugMenuBar(const ImVec2 viewport_pos)
{
    ImGui::PushFont((int)Font::Debug);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.35f, 0.35f, 0.35f, 0.65f));
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(ImVec2(center.x - 140.0f, viewport_pos.y), ImGuiCond_Always);
    ImGui::Begin("debug_control", nullptr,
        ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.0f, 3.0f));
        if (_show_debug_menu_bar)
        {
            if (ImGui::Button("_")) _show_debug_menu_bar = false;
        }
        else
        {
            if (ImGui::Button(">")) _show_debug_menu_bar = true;
        }
        ImGui::MouseCursorToHand();
        ImGui::PopStyleVar();

        if (_show_debug_menu_bar)
        {
            ImGui::Checkbox("demo", &_show_demo_window);
            ImGui::MouseCursorToHand();
            ImGui::SameLine();
            ImGui::Checkbox("debug", &_show_debug_window);
            ImGui::MouseCursorToHand();
        }
    }
    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopFont();
}

void pushDebugStyles()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.282f, 0.282f, 0.282f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.034f, 0.035f, 0.086f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.034f, 0.035f, 0.086f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.034f, 0.035f, 0.086f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.111f, 0.178f, 0.301f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.069f, 0.111f, 0.188f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.069f, 0.111f, 0.188f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.09f, 0.09f, 0.12f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.24f, 0.24f, 0.28f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.24f, 0.24f, 0.28f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.275f, 0.275f, 0.275f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.380f, 0.380f, 0.380f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.427f, 0.427f, 0.427f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, ImVec4(0.275f, 0.275f, 0.275f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.965f, 0.965f, 0.965f, 1.0f));
}

void popDebugStyles()
{
    ImGui::PopStyleColor(17);
    ImGui::PopStyleVar();
}

void drawDebugTabItemGeneral()
{
    if (ImGui::BeginTabItem("General"))
    {
        // TODO add general data

        ImGui::EndTabItem();
    }
}

void drawDebugWindow(bool* open, const int window_w, const int window_h,
    const State current_state)
{
    pushDebugStyles();

    ImGui::Begin("debug", open,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::Text("%dx%d", window_w, window_h);
        ImGui::SameLine();
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Separator(); //--------------------------------------------------

        ImGui::Text("%-24s: %d / %d", "has_error / showing?", has_error ? 1 : 0, showing_error_message ? 1 : 0);
        if (0 <= static_cast<int>(current_state)
            && static_cast<int>(current_state) <= static_cast<int>(State::None))
        {
            ImGui::Text("%-24s: [%d]%s", "state",
                current_state, STATE_STR[static_cast<int>(current_state)]);
        }

        State next_state = getNextState();
        if (0 <= static_cast<int>(next_state)
            && static_cast<int>(next_state) <= static_cast<int>(State::None))
        {
            ImGui::Text("%-24s: [%d]%s", "next state",
                next_state, STATE_STR[static_cast<int>(next_state)]);
        }

        if (ImGui::BeginTabBar("DebugTab", ImGuiTabBarFlags_None))
        {
            drawDebugTabItemGeneral();
            ImGui::EndTabBar();
        }
    }
    ImGui::End();

    popDebugStyles();
}

void drawDebugContents(const int window_w, const int window_h, const State current_state)
{
    ImGui::PushFont((int)Font::Debug);

    if (_show_demo_window)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
        ImGui::ShowDemoWindow(&_show_demo_window);
        ImGui::PopStyleVar();
    }

    if (_show_debug_window)
        drawDebugWindow(&_show_debug_window, window_w, window_h, current_state);

    ImGui::PopFont();
}

} // Gui
} // ImGuiApp
#endif