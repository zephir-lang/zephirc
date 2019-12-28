// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_BUILD_HPP_
#define ZEPHIR_CLI_COMMANDS_BUILD_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of BuildCommand subcommand.
struct BuildOptions {
  BuildOptions() : dev(true) {}
  std::string backend{""};
  bool dev;
};

using BuildOptionsPtr = std::unique_ptr<BuildOptions>;

/// \brief Generates/Compiles/Installs a Zephir extension.
class BuildCommand : public AbstractCommand {
 public:
  /// \brief Construct BuildCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit BuildCommand(std::string name);

  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes BuildCommand command.
  void Execute() override;

 private:
  BuildOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_BUILD_HPP_
