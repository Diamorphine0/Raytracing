#ifndef LOG_H
#define LOG_H

#include "engine.h"
#include "spdlog/spdlog.h"


namespace engine {
class Log
{
public:
    Log();
    ~Log();

    static void Init();
    inline static Ref<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
private:
    static Ref<spdlog::logger> s_EngineLogger;

};

}

// Core log macros
#define HZ_CORE_TRACE(...)    ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)     ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)     ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)    ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_CRITICAL(...) ::Hazel::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HZ_TRACE(...)         ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)          ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)          ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)         ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_CRITICAL(...)      ::Hazel::Log::GetClientLogger()->critical(__VA_ARGS__)







#endif // LOG_H

