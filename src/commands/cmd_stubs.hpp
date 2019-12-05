// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_STUBS_HPP_
#define ZEPHIR_COMMANDS_CMD_STUBS_HPP_

#include <string>

#include <CLI/CLI11.hpp>

namespace zephir::commands {

/**
 * Collection of all options of stubs command.
 */
struct StubsOptions {
  std::string backend;
};

/**
 * @brief Configures the current command.
 *
 * @param app CLI::App instance
 * @param group The command group membership
 */
void SetupStubsCommand(CLI::App &app, const std::string &group);

/**
 * @brief Executes the current command.
 * @param opt Collection of all options of stubs command.
 */
void ExecuteStubsCommand(StubsOptions const &opt);
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_STUBS_HPP_
