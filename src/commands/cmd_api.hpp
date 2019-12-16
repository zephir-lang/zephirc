// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_API_HPP_
#define ZEPHIR_COMMANDS_CMD_API_HPP_

#include <memory>
#include <string>

#include <CLI/CLI.hpp>

namespace zephir::commands {
/**
 * @brief Collection of all options of api command.
 */
struct ApiOptions {
  std::string backend;
  std::string template_path;
  std::string output;
  std::string theme_options;
  std::string url;
};

/**
 * @brief Configures the current command.
 *
 * @param app The smart pointer to a CLI::App instance
 * @param group The command group membership
 */
void SetupApiCommand(const std::shared_ptr<CLI::App> &app,
                     const std::string &group);

/**
 * @brief Executes the current command.
 *
 * @param opt Collection of all options of api command.
 */
void ExecuteApiCommand(ApiOptions const &opt);
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_API_HPP_
