// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_INIT_HPP_
#define ZEPHIR_CLI_COMMANDS_INIT_HPP_

#include <zephir/cli/commands/abstract_command.hpp>

namespace zephir::cli::commands {
struct InitOptions {
  InitOptions() : backend(""), ns("") {}
  std::string backend;
  std::string ns;
};

using InitOptionsPtr = std::unique_ptr<InitOptions>;

class InitCommand : public AbstractCommand {
 public:
  explicit InitCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  InitOptionsPtr options_;
};
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_INIT_HPP_
