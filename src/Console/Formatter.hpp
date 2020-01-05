// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file Formatter.hpp
/// \brief Provides custom CLI::Formatter implementation.

#ifndef ZEPHIR_CLI_FORMATTER_HPP_
#define ZEPHIR_CLI_FORMATTER_HPP_

#include <string>

#include <CLI/CLI.hpp>
#include <CLI/Formatter.hpp>

namespace zephir::console {
/// \brief This is the default Formatter for Application. It pretty prints help
/// output, and is broken into quite a few overridable methods, to be highly
/// customizable with minimal effort.
class Formatter : public CLI::Formatter {
 public:
  /// \brief Displays the description line.
  ///
  /// \param app The pointer to a CLI::App instance
  /// \return Program/command description string.
  std::string make_description(const CLI::App *app) const override;

  /// \brief Gets the usage line.
  ///
  /// \param app The pointer to a CLI::App instance
  /// \param name The application name (e.g. "zephir"). Currently not unused
  /// \return A program (command) usage string.
  std::string make_usage(const CLI::App *app, std::string name) const override;

  /// \brief Prints the footer line.
  ///
  /// \param app The pointer to a CLI::App instance
  /// \return A program (command) footer string.
  std::string make_footer(const CLI::App *app) const override;
};
}  // namespace zephir::console

#endif  // ZEPHIR_CLI_FORMATTER_HPP_
