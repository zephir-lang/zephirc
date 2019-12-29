// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file init.hpp
/// \brief Provides GenerateOptions, GenerateOptionsPtr and GenerateCommand.

#ifndef ZEPHIR_CLI_COMMANDS_INIT_HPP_
#define ZEPHIR_CLI_COMMANDS_INIT_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of InitCommand subcommand.
struct InitOptions {
  /// Used backend to generate extension.
  std::string backend{""};
  /// The extension namespace
  std::string ns{""};
};

/// \brief A type definition for a unique pointer to a InitOptions instance.
using InitOptionsPtr = std::unique_ptr<InitOptions>;

/// \brief Initializes a Zephir extension.
/// \sa AbstractCommand
class InitCommand : public AbstractCommand {
 public:
  /// \brief Construct InitCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit InitCommand(std::string name);

  /// \brief Configures the InitCommand command.
  ///
  /// \param app A `CLI::App` instance
  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes InitCommand command.
  void Execute() override;

 private:
  InitOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_INIT_HPP_
