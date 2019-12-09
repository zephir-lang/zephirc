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

#include "zephir/config.hpp"

namespace zephir::commands {
/**
 * @brief Collection of all options of init command.
 */
struct InitOptions {
  std::string backend;
  std::string ns;
};

/**
 * @brief Configures the current command.
 *
 * @param app CLI::App instance
 * @param group The command group membership
 */
void SetupInitCommand(CLI::App &app, const std::string &group);

/**
 * @brief Executes the current command.
 * @param opt Collection of all options of init command.
 */
void ExecuteInitCommand(InitOptions const &opt);
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_INIT_HPP_
