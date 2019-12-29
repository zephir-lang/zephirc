// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file build.hpp
/// \brief Provides BuildOptions, BuildOptionsPtr and BuildCommand.

#ifndef ZEPHIR_CLI_COMMANDS_BUILD_HPP_
#define ZEPHIR_CLI_COMMANDS_BUILD_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of BuildCommand subcommand.
struct BuildOptions {
  BuildOptions() : dev(true) {}
  /// Used backend to generate extension.
  std::string backend{""};
  /// Compile the extension in development mode
  bool dev;
};

/// \brief A type definition for a unique pointer to a BuildOptions instance.
using BuildOptionsPtr = std::unique_ptr<BuildOptions>;

/// \brief Generates/Compiles/Installs a Zephir extension.
/// \sa AbstractCommand
class BuildCommand : public AbstractCommand {
 public:
  /// \brief Construct BuildCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit BuildCommand(std::string name);

  /// \brief Configures the BuildCommand command.
  ///
  /// \param app A `CLI::App` instance
  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes BuildCommand command.
  void Execute() override;

 private:
  BuildOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_BUILD_HPP_
