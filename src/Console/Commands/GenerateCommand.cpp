// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "GenerateCommand.hpp"

#include <utility>

zephir::console::commands::GenerateCommand::GenerateCommand(std::string name)
    : AbstractCommand(std::move(name)),
      options_(std::make_unique<GenerateOptions>()) {}

void zephir::console::commands::GenerateCommand::Setup(CLI::App_p app) {
  auto cmd = app->group(group_)->add_subcommand(
      "generate", "Generates C code from the Zephir code without compiling it");

  options_->backend = "ZendEngine3";

  // Add options to cmd, binding them to options.
  cmd->add_option(
      "--backend", options_->backend,
      "Used backend to generate extension [default: \"ZendEngine3\"]");
  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  // TODO(klay): These flags should be parsed before CLI11 initialization.
  // Current plan is:
  // 1. read these flags
  // 2. set the appropriate configuration
  // 3. remove these flags (if any) from argv
  cmd->footer(CommonCompilationFlagsHelp());

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([&]() { Execute(); });
}

void zephir::console::commands::GenerateCommand::Execute() {
  // Do stuff...
  std::cout << "Generate command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
  std::cout << "    options.backend = " << options_->backend << std::endl;
}
