// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_COMMAND_HPP_
#define ZEPHIR_CLI_COMMANDS_COMMAND_HPP_

#include <string>

namespace zephir::cli::commands {
class Command {
 public:
  Command();

 protected:
  const std::string group_;
};
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_COMMAND_HPP_
