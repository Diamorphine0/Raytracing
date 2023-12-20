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







#endif // LOG_H

