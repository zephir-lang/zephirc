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
#include <zephir/config.hpp>

namespace zephir::commands {
class Application {
 public:
  explicit Application(std::vector<std::string> args);
  void Run();

 private:
  std::string base_path_;
  zephir::ConfigPtr config_;
  std::vector<std::string> args_;
  std::shared_ptr<CLI::App> app_;
};
}  // namespace zephir::commands

#endif  // ZEPHIR_SRC_CLI_APPLICATION_HPP_
