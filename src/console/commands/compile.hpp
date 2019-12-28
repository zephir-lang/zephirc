// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_COMPILE_HPP_
#define ZEPHIR_CLI_COMMANDS_COMPILE_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of CompileCommand subcommand.
struct CompileOptions {
  CompileOptions() : dev(true) {}
  std::string backend{""};
  bool dev;
};

using CompileOptionsPtr = std::unique_ptr<CompileOptions>;

/// \brief Compile a Zephir extension.
class CompileCommand : public AbstractCommand {
 public:
  /// \brief Construct CompileCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit CompileCommand(std::string name);

  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes CompileCommand command.
  void Execute() override;

 private:
  CompileOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_COMPILE_HPP_
