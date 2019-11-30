// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_API_HPP_
#define ZEPHIR_COMMANDS_CMD_API_HPP_

#include <string>

#include <CLI/CLI11.hpp>

namespace zephir::commands {
/**
 * @brief Generates a HTML API based on the classes exposed in the extension.
 */
class ApiCommand {
 public:
  ApiCommand(CLI::App* app, const std::string& group);

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

  // Collection of all options of ApiCommand.
  struct Options {
    std::string backend;
    std::string template_path;
    std::string output;
    std::string theme_options;
    std::string url;
  } options;
};
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_API_HPP_
