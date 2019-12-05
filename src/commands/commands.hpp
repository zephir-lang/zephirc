// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_COMMANDS_HPP_
#define ZEPHIR_COMMANDS_COMMANDS_HPP_

#include <string>

namespace zephir::commands {
/**
 * @brief Parse options from both the CLI.
 *
 * @param argc Number of CLI arguments provided
 * @param argv Provided CLI arguments
 */
int CreateFromArgv(int argc, char **argv);

/**
 * @brief Gets a help for common compilation flags.
 *
 * @return A formatted text with line breaks
 */
std::string CommonCompilationFlagsHelp();
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_COMMANDS_HPP_
