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
  Cmd parseopt(char **argv);

 private:
  inline void set_help_flag(Cmd &cmd);
  inline void set_backend(Cmd &cmd, const char *backend);
  std::string m_program;
};

}  // namespace commands

#endif  // ZEPHIR_COMMANDS_OPTIONS_HPP_
