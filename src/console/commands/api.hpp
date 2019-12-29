// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file api.hpp
/// \brief Provides ApiOptions, ApiOptionsPtr and ApiCommand

#ifndef ZEPHIR_CLI_COMMANDS_API_HPP_
#define ZEPHIR_CLI_COMMANDS_API_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of ApiCommand subcommand.
struct ApiOptions {
  /// Used backend to generate extension.
  std::string backend{""};
  /// The API theme to be used
  std::string template_path{""};
  /// The output directory to generate theme
  std::string output{""};
  /// The current theme options
  std::string theme_options{""};
  /// The base URL to be used when generating links
  std::string url{""};
};

/// \brief A type definition for a unique pointer to a ApiOptions instance.
using ApiOptionsPtr = std::unique_ptr<ApiOptions>;

/// \brief Generates a HTML API based on the classes exposed in the extension.
/// \sa AbstractCommand
class ApiCommand : public AbstractCommand {
 public:
  /// \brief Construct ApiCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit ApiCommand(std::string name);

  /// \brief Configures the ApiCommand command.
  ///
  /// \param app A `CLI::App` instance
  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes ApiCommand command.
  void Execute() override;

 private:
  ApiOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_API_HPP_
