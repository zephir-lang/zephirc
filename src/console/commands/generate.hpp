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
struct GenerateOptions {
  std::string backend{""};
};

using GenerateOptionsPtr = std::unique_ptr<GenerateOptions>;

class GenerateCommand : public AbstractCommand {
 public:
  explicit GenerateCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  GenerateOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_GENERATE_HPP_
