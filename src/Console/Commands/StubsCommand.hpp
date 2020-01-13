// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file StubsCommand.hpp
/// \brief Provides StubsOptions, StubsOptionsPtr and StubsCommand.

#ifndef ZEPHIR_CLI_COMMANDS_STUBS_HPP_
#define ZEPHIR_CLI_COMMANDS_STUBS_HPP_

#include <memory>
#include <string>

#include "AbstractCommand.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of StubsCommand subcommand.
struct StubsOptions {
  /// Used backend to generate extension.
  std::string backend{""};
};

/// \brief A type definition for a unique pointer to a StubsOptions instance.
using StubsOptionsPtr = std::unique_ptr<StubsOptions>;

/// \brief Generates stubs that can be used in a PHP IDE.
/// \sa AbstractCommand
class StubsCommand : public AbstractCommand {
 public:
  /// \brief Construct StubsCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit StubsCommand(std::string name);

  /// \brief Configures the StubsCommand command.
  ///
  /// \param app A `CLI::App` instance
  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes StubsCommand command.
  void Execute() override;

 private:
  StubsOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_STUBS_HPP_
