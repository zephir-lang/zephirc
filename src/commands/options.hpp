#ifndef ZEPHIR_COMMANDS_OPTIONS_HPP_
#define ZEPHIR_COMMANDS_OPTIONS_HPP_

#include <string>

#include "cmd.hpp"

namespace commands {
class Options {
 public:
  Options() noexcept;
  void parseopt(char **argv, Cmd &cmd);

 private:
  std::string m_program;
};

}  // namespace commands

#endif  // ZEPHIR_COMMANDS_OPTIONS_HPP_
