// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_GENERATE_HPP_
#define ZEPHIR_COMMANDS_CMD_GENERATE_HPP_

#include <string>

#include <CLI/CLI11.hpp>

namespace zephir::commands {
/**
 * Generates C code from the Zephir code without compiling it.
 */
class GenerateCommand {
 public:
  GenerateCommand(CLI::App* app, const std::string& group);

 private:
  /**
   * Configures the current command.
   * @param app CLI::App instance
   * @param group The command group membership
   */
  void Configure(CLI::App* app, const std::string& group);

  /**
   * Executes the current command.
   */
  void Execute();

  // Collection of all options of Generate Command.
  struct Options {
    std::string backend;
  } options;
};
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_GENERATE_HPP_
