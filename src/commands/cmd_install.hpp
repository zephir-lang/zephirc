// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_INSTALL_HPP_
#define ZEPHIR_COMMANDS_CMD_INSTALL_HPP_

#include <string>

#include <CLI/CLI11.hpp>

namespace zephir::commands {

/**
 * Collection of all options of install command.
 */
struct InstallOptions {
  bool dev;
};

/**
 * @brief Configures the current command.
 *
 * @param app CLI::App instance
 * @param group The command group membership
 */
void SetupInstallCommand(CLI::App &app, const std::string &group);

/**
 * @brief Executes the current command.
 */
void ExecuteInstallCommand(InstallOptions const &opt);
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_INSTALL_HPP_
