// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "facade.hpp"

template <class T>
zephir::logger::Facade<T>::Facade() {
  _logger = spdlog::stdout_color_mt(this->_logger_name);
}

template <class T>
zephir::logger::Facade<T>::Facade(std::shared_ptr<T> logger) {
  _logger =
      logger == nullptr ? spdlog::stdout_color_mt(this->_logger_name) : logger;
}

template <class T>
zephir::logger::Facade<T>::~Facade() {
  spdlog::drop_all();
}

template <class T>
void zephir::logger::Facade<T>::info(const std::string& message) {
  _logger->info(message);
}

template <class T>
void zephir::logger::Facade<T>::warning(const std::string& message) {
  _logger->warn(message);
}

template <class T>
void zephir::logger::Facade<T>::error(const std::string& message) {
  _logger->error(message);
}

template <class T>
void zephir::logger::Facade<T>::debug(const std::string& message) {
  _logger->debug(message);
}

template <class T>
void zephir::logger::Facade<T>::exception(
    const std::exception& error,
    const std::vector<std::tuple<std::string, std::string>>& context) {
  ///
}

template <class T>
void zephir::logger::Facade<T>::log(
    const std::string& message, int level, const std::string& category,
    const std::vector<std::tuple<std::string, std::string>>& context) {
  ///
}
