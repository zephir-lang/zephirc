// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file CompileCommand.hpp
/// \brief Provides CompileOptions, CompileOptionsPtr and CompileCommand.

#ifndef ZEPHIR_CLI_COMMANDS_COMPILE_HPP_
#define ZEPHIR_CLI_COMMANDS_COMPILE_HPP_

#include "AbstractCommand.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of CompileCommand subcommand.
struct CompileOptions {
  CompileOptions() : dev(true) {}
  /// Used backend to generate extension.
  std::string backend{""};
  /// Compile the extension in development mode
  bool dev;
};

/// \brief A type definition for a unique pointer to a CompileOptions instance.
using CompileOptionsPtr = std::unique_ptr<CompileOptions>;

/// \brief Compile a Zephir extension.
/// \sa AbstractCommand
class CompileCommand : public AbstractCommand {
 public:
  /// \brief Construct CompileCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit CompileCommand(std::string name);

  /// \brief Configures the CompileCommand command.
  ///
  /// \param app A `CLI::App` instance
  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes CompileCommand command.
  void Execute() override;

 private:
  CompileOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_COMPILE_HPP_
