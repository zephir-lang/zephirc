// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_COMMAND_HPP_
#define ZEPHIR_CLI_COMMANDS_COMMAND_HPP_

#include <string>

#include <CLI/CLI.hpp>

namespace zephir::cli::commands {
class Command {
 public:
  explicit Command(std::string name);
  virtual ~Command() = default;
  virtual void Setup(std::shared_ptr<CLI::App> app) = 0;
  virtual void Execute() = 0;

 protected:
  static std::string CommonCompilationFlagsHelp();

  const std::string name_;
  const std::string group_;
};

using CommandPtr = std::unique_ptr<Command>;
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_COMMAND_HPP_
