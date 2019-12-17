// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_GENERATE_HPP_
#define ZEPHIR_CLI_COMMANDS_GENERATE_HPP_

#include <zephir/cli/commands/abstract_command.hpp>

namespace zephir::cli::commands {
struct GenerateOptions {
  GenerateOptions() : backend("") {}
  std::string backend;
};

using GenerateOptionsPtr = std::unique_ptr<GenerateOptions>;

class GenerateCommand : public AbstractCommand {
 public:
  explicit GenerateCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  GenerateOptionsPtr options_;
};
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_GENERATE_HPP_
