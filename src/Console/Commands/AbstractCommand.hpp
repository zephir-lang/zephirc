// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file AbstractCommand.hpp
/// \brief This file contains the declaration of the AbstractCommand class,
/// which is the base class for all of the Zephir commands.

#ifndef ZEPHIR_CLI_COMMANDS_ABSTRACT_COMMAND_HPP_
#define ZEPHIR_CLI_COMMANDS_ABSTRACT_COMMAND_HPP_

#include <memory>
#include <string>

#include <CLI/CLI.hpp>

namespace zephir::console::commands {
/// \brief Base class for all commands.
class AbstractCommand {
 public:
  /// \brief Construct command object with a given name.
  ///
  /// \param name The name of the command
  explicit AbstractCommand(std::string name);

  /// Command destructor
  virtual ~AbstractCommand() = default;

  /// \brief Configures the current command.
  ///
  /// \param app A `CLI::App` instance
  /// \return void
  virtual void Setup(std::shared_ptr<CLI::App> app) = 0;

  /// \brief Executes the current command
  /// \return void
  virtual void Execute() = 0;

 protected:
  /// \brief Gets the common compilation flags help.
  ///
  /// \return The formatted string that contains the help
  static std::string CommonCompilationFlagsHelp();

  /// The default command name
  const std::string name_;

  /// The group membership
  const std::string group_ = std::string("Available commands");
};

/// \brief A type definition for a unique pointer to a AbstractCommand instance.
using CommandPtr = std::unique_ptr<AbstractCommand>;
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_ABSTRACT_COMMAND_HPP_
