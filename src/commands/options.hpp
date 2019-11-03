// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

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
