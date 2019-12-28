// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_STUBS_HPP_
#define ZEPHIR_CLI_COMMANDS_STUBS_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of StubsCommand subcommand.
struct StubsOptions {
  /// Used backend to generate extension.
  std::string backend{""};
};

using StubsOptionsPtr = std::unique_ptr<StubsOptions>;

/// \brief Generates stubs that can be used in a PHP IDE.
class StubsCommand : public AbstractCommand {
 public:
  /// \brief Construct StubsCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit StubsCommand(std::string name);

  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes StubsCommand command.
  void Execute() override;

 private:
  StubsOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_STUBS_HPP_
