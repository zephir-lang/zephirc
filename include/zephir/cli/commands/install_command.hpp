// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_INSTALL_COMMAND_HPP_
#define ZEPHIR_CLI_COMMANDS_INSTALL_COMMAND_HPP_

#include <zephir/cli/commands/command.hpp>

namespace zephir::cli::commands {
struct InstallOptions {
  bool dev = true;
};

using InstallOptionsPtr = std::unique_ptr<InstallOptions>;

class InstallCommand : public Command {
 public:
  explicit InstallCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  InstallOptionsPtr options_;
};
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_INSTALL_COMMAND_HPP_
