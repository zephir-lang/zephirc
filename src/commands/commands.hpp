// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_COMMANDS_HPP_
#define ZEPHIR_COMMANDS_COMMANDS_HPP_

#include <CLI/CLI11.hpp>

#define ZEPHIR_COMMANDS_EXIT_HELP -1;

namespace commands {
/** Parse options from both the CLI.
 * @param argc Number of CLI arguments provided
 * @param argv Provided CLI arguments
 */
int optparse(int argc, char **argv);
}  // namespace commands

#endif  // ZEPHIR_COMMANDS_COMMANDS_HPP_
