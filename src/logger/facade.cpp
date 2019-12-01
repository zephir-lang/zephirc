// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "facade.hpp"

template <class Type>
zephir::logger::Facade<Type>::Facade(const std::string logger_name = "zephir_logger") {
  _logger = spdlog::stdout_color_mt(logger_name);
}

template <class Type>
zephir::logger::Facade<Type>::~Facade() {}

