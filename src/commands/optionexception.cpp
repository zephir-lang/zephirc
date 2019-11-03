// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view the LICENSE
// file that was distributed with this source code.

#include "optionexception.hpp"

#include <utility>

commands::OptionException::OptionException(std::string message)
    : m_message(std::move(message)) {}

const char* commands::OptionException::what() const noexcept {
  return m_message.c_str();
}
