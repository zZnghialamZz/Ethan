#include "ethan/utils/console/console.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace ethan {

std::shared_ptr<spdlog::logger> Console::core_logger_;
std::shared_ptr<spdlog::logger> Console::client_logger_;

void Console::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");

  core_logger_ = spdlog::stdout_color_mt("ETHAN");
  core_logger_->set_level(spdlog::level::trace);

  client_logger_ = spdlog::stdout_color_mt("APP");
  client_logger_->set_level(spdlog::level::trace);
}

} // namespace ethan
