// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_GENERATE_HPP_
#define ZEPHIR_CLI_COMMANDS_GENERATE_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of GenerateCommand subcommand.
struct GenerateOptions {
  std::string backend{""};
};

using GenerateOptionsPtr = std::unique_ptr<GenerateOptions>;

/// \brief Generates C code from the Zephir code without compiling it.
class GenerateCommand : public AbstractCommand {
 public:
  /// \brief Construct GenerateCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit GenerateCommand(std::string name);

  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes GenerateCommand command.
  void Execute() override;

 private:
  GenerateOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_GENERATE_HPP_
