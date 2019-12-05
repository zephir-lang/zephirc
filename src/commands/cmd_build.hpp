// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_BUILD_HPP_
#define ZEPHIR_COMMANDS_CMD_BUILD_HPP_

#include <string>

#include <CLI/CLI11.hpp>

namespace zephir::commands {
/**
 * @brief Collection of all options of build command.
 */
struct BuildOptions {
  std::string backend;
  bool dev;
};

/**
 * @brief Configures the current command.
 *
 * @param app CLI::App instance
 * @param group The command group membership
 */
void SetupBuildCommand(CLI::App &app, const std::string &group);

/**
 * @brief Executes the current command.
 * @param opt Collection of all options of build command.
 */
void ExecuteBuildCommand(BuildOptions const &opt);
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_BUILD_HPP_
