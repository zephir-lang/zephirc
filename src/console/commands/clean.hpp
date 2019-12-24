// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_CLEAN_HPP_
#define ZEPHIR_CLI_COMMANDS_CLEAN_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {
class CleanCommand : public AbstractCommand {
 public:
  explicit CleanCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_CLEAN_HPP_
