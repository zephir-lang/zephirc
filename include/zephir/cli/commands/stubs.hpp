// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_STUBS_HPP_
#define ZEPHIR_CLI_COMMANDS_STUBS_HPP_

#include <zephir/cli/commands/abstract_command.hpp>

namespace zephir::cli::commands {
struct StubsOptions {
  std::string backend{""};
};

using StubsOptionsPtr = std::unique_ptr<StubsOptions>;

class StubsCommand : public AbstractCommand {
 public:
  explicit StubsCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  StubsOptionsPtr options_;
};
}  // namespace zephir::cli::commands

#endif  // ZEPHIR_CLI_COMMANDS_STUBS_HPP_
