// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_COMMANDS_FORMATTER_HPP_
#define ZEPHIR_COMMANDS_FORMATTER_HPP_

#include <string>

#include <CLI/CLI.hpp>

namespace zephir::commands {
class Formatter : public CLI::Formatter {
 public:
  Formatter();

  /**
   * @brief Displays the description line.
   *
   * @param app The pointer to a CLI::App instance
   * @return Program/command description string.
   */
  std::string make_description(const CLI::App *app) const override;

  /**
   * @brief Gets the usage line.
   *
   * @param app The pointer to a CLI::App instance
   * @param name Application name (e.g. "zephir"). Currently not unused
   * @return Program/command usage string.
   */
  std::string make_usage(const CLI::App *app, std::string name) const override;

  /**
   * @brief Prints the footer line.
   *
   * @param app The pointer to a CLI::App instance
   * @return Program/command footer string.
   */
  std::string make_footer(const CLI::App *app) const override;
};
}  // namespace zephir::commands

#endif  // ZEPHIR_COMMANDS_FORMATTER_HPP_
