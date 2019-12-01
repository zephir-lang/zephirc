// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_INIT_HPP_
#define ZEPHIR_COMMANDS_CMD_INIT_HPP_

#include <string>

#include <CLI/CLI11.hpp>

namespace zephir::commands {
/**
 * @brief Initializes a Zephir extension.
 */
class InitCommand {
 public:
  InitCommand(CLI::App* app, const std::string& group);

 private:
  /**
   * @brief Configures the current command.
   *
   * @param app CLI::App instance
   * @param group The command group membership
   */
  void Configure(CLI::App* app, const std::string& group);

  /**
   * @brief Executes the current command.
   */
  void Execute();

  // Collection of all options of InitCommand.
  struct Options {
    std::string backend;
    std::string ns;
  } options;
};
}  // namespace zephir::commands

#endif //ZEPHIR_COMMANDS_CMD_INIT_HPP_
