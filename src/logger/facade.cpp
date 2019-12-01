// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "facade.hpp"

template <class Type>
zephir::logger::Facade<Type>::Facade(const std::string& logger_name) {
  _logger = spdlog::stdout_color_mt(logger_name);
}

template <class Type>
zephir::logger::Facade<Type>::~Facade() {
  spdlog::drop_all();
}

template <class Type>
void zephir::logger::Facade<Type>::info(const std::string& message) {
  _logger->info(message);
}

template <class Type>
void zephir::logger::Facade<Type>::warning(const std::string& message) {
  _logger->warn(message);
}

template <class Type>
void zephir::logger::Facade<Type>::error(const std::string& message) {
  _logger->error(message);
}

template <class Type>
void zephir::logger::Facade<Type>::debug(const std::string& message) {
  _logger->debug(message);
}

template <class Type>
void zephir::logger::Facade<Type>::exception(const std::exception& error,
                                             const Type& context) {
  ///
}

template <class Type>
void zephir::logger::Facade<Type>::log(const std::string& message, int level,
                                       const std::string& category,
                                       const Type& context) {
  ///
}
