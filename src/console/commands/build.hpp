// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CLI_COMMANDS_BUILD_HPP_
#define ZEPHIR_CLI_COMMANDS_BUILD_HPP_

#include "abstract_command.hpp"

namespace zephir::console::commands {

struct BuildOptions {
  BuildOptions() : dev(true) {}
  std::string backend{""};
  bool dev;
};

using BuildOptionsPtr = std::unique_ptr<BuildOptions>;

class BuildCommand : public AbstractCommand {
 public:
  explicit BuildCommand(std::string name);
  void Setup(std::shared_ptr<CLI::App> app) override;
  void Execute() override;

 private:
  BuildOptionsPtr options_;
};
}  // namespace zephir::console::commands

#endif  // ZEPHIR_CLI_COMMANDS_BUILD_HPP_
