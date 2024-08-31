#include <iostream>

using namespace std;
#include "logger.h"
#include <future>

// // 自定义宏，方便在每次日志记录时自动添加文件名、函数名和行号
// #define LOG_INFO(...) SPDLOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::info, __FILE__, __LINE__, SPDLOG_FUNCTION, __VA_ARGS__)
// #define LOG_WARN(...) SPDLOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::warn, __FILE__, __LINE__, SPDLOG_FUNCTION, __VA_ARGS__)
// #define LOG_ERROR(...) SPDLOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::err, __FILE__, __LINE__, SPDLOG_FUNCTION, __VA_ARGS__)
// #define LOG_DEBUG(...) SPDLOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::debug, __FILE__, __LINE__, SPDLOG_FUNCTION, __VA_ARGS__)


void module1test()
{
    for (int i=0; i<1000; i++)
    {
        LOG_INFO("module1", "Some info message from module1 iteration");
        LOG_WARN("module1", "Some warning message from module1 iteration");
        LOG_ERR("module1", "Some error message from module1 iteration");
        LOG_DEBUG("module1", "Some debug message from module1 iteration");
    }
}

void module2test()
{
    for (int i=0; i<1000; i++)
    {
        LOG_INFO("module2", "Some info message from module2 iteration");
        LOG_WARN("module2", "Some warning message from module2 iteration");
        LOG_ERR("module2", "Some error message from module2 iteration");
        LOG_DEBUG("module2", "Some debug message from module2 iteration");
    }
}

int main()
{
    cout << "Hello World!" << endl;
    Logger::init();
    auto fut1 = async(launch::async, module1test);
    auto fut2 = async(launch::async, module2test);
    fut1.wait();
    fut2.wait();
    
    spdlog::info("Finished");
    
    return 0;
}
