#ifndef ZEPHIR_COMMANDS_OPTIONEXCEPTION_HPP_
#define ZEPHIR_COMMANDS_OPTIONEXCEPTION_HPP_

#include <exception>
#include <string>

namespace commands {
class OptionException : public std::exception {
 public:
  explicit OptionException(std::string message);
  const char* what() const noexcept override;

 private:
  std::string m_message;
};
}  // namespace commands

#endif  // ZEPHIR_COMMANDS_OPTIONEXCEPTION_HPP_
