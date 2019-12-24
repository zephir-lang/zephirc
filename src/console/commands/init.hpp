// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_INIT_HPP_
#define ZEPHIR_CLI_COMMANDS_INIT_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
struct InitOptions {
  std::string backend{""};
  std::string ns{""};
};

using InitOptionsPtr = std::unique_ptr<InitOptions>;

class InitCommand : public AbstractCommand {
 public:
  explicit InitCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  InitOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_INIT_HPP_
