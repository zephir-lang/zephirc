// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_CMD_CLEAN_HPP_
#define ZEPHIR_COMMANDS_CMD_CLEAN_HPP_

#include <memory>
#include <string>

#include <CLI/CLI.hpp>

namespace zephir::commands {
/**
 * @brief Configures the current command.
 *
 * @param app The smart pointer to a CLI::App instance
 * @param group The command group membership
 */
void SetupCleanCommand(const std::shared_ptr<CLI::App>& app,
                       const std::string& group);

/**
 * @brief Executes the current command.
 */
void ExecuteCleanCommand();
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_CMD_CLEAN_HPP_
