#ifndef LOGGER_H
#define LOGGER_H
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <Common_export.h>

class COMMON_EXPORT Logger
{
public:
    static void init(const std::string& modulename="global_logger");
    static void log(const std::string& module, const spdlog::level::level_enum& level, const std::string& file, const int& line, const std::string& func, const std::string& message);
};

#define LOG_INFO(module, message) Logger::log(module, spdlog::level::info, __FILE__, __LINE__, __FUNCTION__, message)
#define LOG_WARN(module, message) Logger::log(module, spdlog::level::warn, __FILE__, __LINE__, __FUNCTION__, message)
#define LOG_ERR(module, message) Logger::log(module, spdlog::level::err, __FILE__, __LINE__, __FUNCTION__, message)
#define LOG_CRIT(module, message) Logger::log(module, spdlog::level::critical, __FILE__, __LINE__, __FUNCTION__, message)
#define LOG_DEBUG(module, message) Logger::log(module, spdlog::level::debug, __FILE__, __LINE__, __FUNCTION__, message)

#endif // LOGGER_H