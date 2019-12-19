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

#include "../config/config.hpp"
#include "commands/abstract_command.hpp"
#include "formatter.hpp"

namespace zephir::console {

class Application {
 public:
  /**
   * @brief Application constructor.
   */
  explicit Application(std::vector<std::string> args, std::string base_path);
  Application(const Application&) = delete;

  /**
   * @brief Application destructor.
   */
  ~Application();

  /**
   * @brief Dumps the project configuration to the disk if it has been changed.
   */
  void DumpConfig();

  void AddCommand(commands::CommandPtr command);
  int Run();
  Application& operator=(const Application&) = delete;

 private:
  std::vector<std::string> args_;
  std::string base_path_;
  zephir::ConfigPtr config_;
  std::shared_ptr<zephir::console::Formatter> formatter_;
  CLI::App_p app_;
  CLI::Option* help_;
  std::vector<commands::CommandPtr> commands_;
};
}  // namespace zephir::console

#endif  // ZEPHIR_SRC_CLI_APPLICATION_HPP_
