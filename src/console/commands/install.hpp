// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file install.hpp
/// \brief Provides InstallOptions, InstallOptionsPtr and InstallCommand.

#ifndef ZEPHIR_CLI_COMMANDS_INSTALL_HPP_
#define ZEPHIR_CLI_COMMANDS_INSTALL_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of InstallCommand subcommand.
struct InstallOptions {
  InstallOptions() : dev(true) {}
  /// Compile the extension in development mode
  bool dev;
};

/// \brief A type definition for a unique pointer to a InstallOptions instance.
using InstallOptionsPtr = std::unique_ptr<InstallOptions>;

/// \brief Installs the extension in the extension directory.
/// \sa AbstractCommand
class InstallCommand : public AbstractCommand {
 public:
  /// \brief Construct InstallCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit InstallCommand(std::string name);

  /// \brief Configures the InstallCommand command.
  ///
  /// \param app A `CLI::App` instance
  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes InstallCommand command.
  void Execute() override;

 private:
  InstallOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_INSTALL_HPP_
