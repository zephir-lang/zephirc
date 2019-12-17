// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_COMPILE_COMMAND_HPP_
#define ZEPHIR_CLI_COMMANDS_COMPILE_COMMAND_HPP_

#include <zephir/cli/commands/command.hpp>

namespace zephir::cli::commands {
struct CompileOptions {
  CompileOptions() : backend(""), dev(true) {}
  std::string backend;
  bool dev;
};

using CompileOptionsPtr = std::unique_ptr<CompileOptions>;

class CompileCommand : public Command {
 public:
  explicit CompileCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  CompileOptionsPtr options_;
};
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_COMPILE_COMMAND_HPP_
