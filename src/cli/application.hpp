// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_SRC_CLI_APPLICATION_HPP_
#define ZEPHIR_SRC_CLI_APPLICATION_HPP_

#include <string>
#include <vector>

#include <CLI/CLI.hpp>
#include <zephir/cli/commands/command.hpp>
#include <zephir/cli/formatter.hpp>
#include <zephir/config.hpp>

namespace zephir::cli {
using CommandPtr = std::unique_ptr<zephir::cli::commands::Command>;

class Application {
 public:
  explicit Application(std::vector<std::string> args, std::string base_path);
  Application(const Application&) = delete;
  ~Application() = default;
  void AddCommand(CommandPtr command);
  int Run();
  Application& operator=(const Application&) = delete;

 private:
  std::vector<std::string> args_;
  std::string base_path_;
  zephir::ConfigPtr config_;
  std::shared_ptr<zephir::cli::Formatter> formatter_;
  std::shared_ptr<CLI::App> app_;
  CLI::Option* help_;
  std::vector<std::unique_ptr<zephir::cli::commands::Command>> commands_;
};
}  // namespace zephir::cli

#endif  // ZEPHIR_SRC_CLI_APPLICATION_HPP_
