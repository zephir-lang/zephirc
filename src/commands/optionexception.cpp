#include "optionexception.hpp"

#include <utility>

commands::OptionException::OptionException(std::string message)
    : m_message(std::move(message)) {}

const char* commands::OptionException::what() const noexcept {
  return m_message.c_str();
}
