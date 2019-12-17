// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_FULLCLEAN_COMMAND_HPP_
#define ZEPHIR_CLI_COMMANDS_FULLCLEAN_COMMAND_HPP_

#include <zephir/cli/commands/command.hpp>

namespace zephir::cli::commands {
class FullCleanCommand : public Command {
 public:
  explicit FullCleanCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;
};
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_FULLCLEAN_COMMAND_HPP_
