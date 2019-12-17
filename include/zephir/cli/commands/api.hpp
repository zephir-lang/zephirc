// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_API_HPP_
#define ZEPHIR_CLI_COMMANDS_API_HPP_

#include <zephir/cli/commands/abstract_command.hpp>

namespace zephir::cli::commands {
struct ApiOptions {
  ApiOptions()
      : backend(""),
        template_path(""),
        output(""),
        theme_options(""),
        url("") {}
  std::string backend;
  std::string template_path;
  std::string output;
  std::string theme_options;
  std::string url;
};

using ApiOptionsPtr = std::unique_ptr<ApiOptions>;

class ApiCommand : public AbstractCommand {
 public:
  explicit ApiCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  ApiOptionsPtr options_;
};
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_API_HPP_
