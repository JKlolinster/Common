#include <logger.h>
#include <iostream>
#include <filesystem>

void Logger::init(const std::string& modulename)
{
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("log.log", 1024 * 1024 * 50, 4);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    // 将文件和控制台sink合并
    std::vector<spdlog::sink_ptr> sinks{file_sink, console_sink};
    auto logger = std::make_shared<spdlog::logger>(modulename, sinks.begin(), sinks.end());
    logger->set_pattern("[%L] [%n] [%t] [%m-%d %H:%M:%S.%e] %v");
    // 设置日志记录器
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug);
}

void Logger::log(const std::string& module, const spdlog::level::level_enum& level, const std::string& filepath, const int& line, const std::string& func, const std::string& message)
{
    auto logger_for_thread = spdlog::get(module);
    if (!logger_for_thread) {
        Logger::init(module);
        logger_for_thread = spdlog::get(module);
    }
    std::string file = std::filesystem::path(filepath).filename().string();
    // 根据日志级别记录日志
    switch (level) 
    {
        case spdlog::level::debug:
            spdlog::debug("[{}] L:{} [{}] {}", file, line, func, message);
            break;
        case spdlog::level::info:
            spdlog::info("[{}] L:{} [{}] {}", file, line, func, message);
            break;
        case spdlog::level::warn:
            spdlog::warn("[{}] L:{} [{}] {}", file, line, func, message);
            break;
        case spdlog::level::err:
            spdlog::error("[{}] L:{} [{}] {}", file, line, func, message);
            break;
        case spdlog::level::critical:
            spdlog::critical("[{}] L:{} [{}] {}", file, line, func, message);
            break;
        default:
            // 如果遇到未知的日志级别，可以选择记录到默认级别
            spdlog::info("[{}] L:{} [{}] {}", file, line, func, message);
            break;
    }
}