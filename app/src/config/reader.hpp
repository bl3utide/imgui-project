﻿#pragma once
#include "config/cv.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Config
{
namespace Reader
{

void iniValueToCv(const mINI::INIStructure& is, Cv& cv) noexcept;

} // Reader
} // Config
} // ImGuiProject
