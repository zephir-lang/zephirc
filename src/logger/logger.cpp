// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "logger.hpp"

zephir::Logger::Logger() {
  _logger = spdlog::stdout_color_mt(this->_logger_name);
}

zephir::Logger::Logger(std::shared_ptr<spdlog::logger> logger) {
  _logger =
      logger == nullptr ? spdlog::stdout_color_mt(this->_logger_name) : logger;
}

zephir::Logger::~Logger() { spdlog::drop_all(); }

void zephir::Logger::info(const std::string& message) {
  _logger->info(message);
}

void zephir::Logger::warning(const std::string& message) {
  _logger->warn(message);
}

void zephir::Logger::error(const std::string& message) {
  _logger->error(message);
}

void zephir::Logger::debug(const std::string& message) {
  _logger->debug(message);
}

void zephir::Logger::exception(const std::exception& error,
                               const Context& ctx) {
  ///
}

void zephir::Logger::log(const std::string& message, int level,
                         const std::string& category, const Context& ctx) {
  ///
}
