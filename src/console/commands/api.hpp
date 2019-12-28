// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_API_HPP_
#define ZEPHIR_CLI_COMMANDS_API_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
/// \brief Collection of all options of ApiCommand subcommand.
struct ApiOptions {
  std::string backend{""};
  std::string template_path{""};
  std::string output{""};
  std::string theme_options{""};
  std::string url{""};
};

using ApiOptionsPtr = std::unique_ptr<ApiOptions>;

/// \brief Generates a HTML API based on the classes exposed in the extension.
class ApiCommand : public AbstractCommand {
 public:
  /// \rief Construct ApiCommand object with a given name.
  ///
  /// \param name The name of the command
  explicit ApiCommand(std::string name);

  void Setup(std::shared_ptr<CLI::App> app) override;

  /// \brief Executes ApiCommand command.
  void Execute() override;

 private:
  ApiOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_API_HPP_
