// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "facade.hpp"

zephir::logger::Facade::Facade() {
  _logger = spdlog::stdout_color_mt(this->_logger_name);
}

zephir::logger::Facade::Facade(std::shared_ptr<spdlog::logger> logger) {
  _logger =
      logger == nullptr ? spdlog::stdout_color_mt(this->_logger_name) : logger;
}

zephir::logger::Facade::~Facade() { spdlog::drop_all(); }

void zephir::logger::Facade::info(const std::string& message) {
  _logger->info(message);
}

void zephir::logger::Facade::warning(const std::string& message) {
  _logger->warn(message);
}

void zephir::logger::Facade::error(const std::string& message) {
  _logger->error(message);
}

void zephir::logger::Facade::debug(const std::string& message) {
  _logger->debug(message);
}

void zephir::logger::Facade::exception(const std::exception& error,
                                       const Context& ctx) {
  ///
}

void zephir::logger::Facade::log(const std::string& message, int level,
                                 const std::string& category,
                                 const Context& ctx) {
  ///
}
