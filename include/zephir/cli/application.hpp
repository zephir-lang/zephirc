// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_APPLICATION_HPP_
#define ZEPHIR_CLI_APPLICATION_HPP_

#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <zephir/cli/commands/abstract_command.hpp>
#include <zephir/cli/formatter.hpp>
#include <zephir/config.hpp>

namespace zephir::cli {

class Application {
 public:
  explicit Application(std::vector<std::string> args, std::string base_path);
  Application(const Application&) = delete;
  ~Application() = default;
  void AddCommand(commands::CommandPtr command);
  int Run();
  Application& operator=(const Application&) = delete;

 private:
  std::vector<std::string> args_;
  std::string base_path_;
  zephir::ConfigPtr config_;
  std::shared_ptr<zephir::cli::Formatter> formatter_;
  CLI::App_p app_;
  CLI::Option* help_;
  std::vector<commands::CommandPtr> commands_;
};
}  // namespace zephir::cli

#endif  // ZEPHIR_SRC_CLI_APPLICATION_HPP_