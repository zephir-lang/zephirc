// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_CLEAN_HPP_
#define ZEPHIR_COMMANDS_CMD_CLEAN_HPP_

#include <string>

#include <CLI/CLI11.hpp>

namespace zephir::commands {
/**
 * @brief Cleans any object files created by the extension.
 */
class CleanCommand {
 public:
  CleanCommand(CLI::App* app, const std::string& group);

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
};
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_CLEAN_HPP_
