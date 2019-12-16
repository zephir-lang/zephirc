// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_PTR_COMMAND_HPP_
#define ZEPHIR_CLI_COMMANDS_PTR_COMMAND_HPP_

#include <memory>

namespace zephir::cli::commands {
class Command;
using CommandPtr = std::unique_ptr<Command>;
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_PTR_COMMAND_HPP_
