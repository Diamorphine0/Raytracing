#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
namespace engine  {

    Ref<spdlog::logger> Log::s_CoreLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_EngineLogger = spdlog::stdout_color_mt("Engine")
        s_EngineLogger->set_level(spdlog::level::trace);
    }
