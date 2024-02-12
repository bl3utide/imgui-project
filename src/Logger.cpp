#ifdef _DEBUG
#include "Common.hpp"
#include "Logger.hpp"

// TODO change app namespace
namespace ImGuiApp
{
namespace Logger
{

// public
std::list<Log> logs;
const size_t MAX_DISPLAY_LOGS = 100;
// TODO 上のバージョンがうまくいったら、下のバージョンは消す
/*
std::list<plog::util::nstring> debug_log;
const size_t MAX_DEBUG_LOG_SIZE = 100;
*/

} // Logger
} // ImGuiApp
#endif