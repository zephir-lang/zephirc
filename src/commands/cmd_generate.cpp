// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "cmd_generate.hpp"

#include <memory>

#include "commands.hpp"

zephir::commands::GenerateCommand::GenerateCommand(CLI::App* app,
                                                   const std::string& group) {
  options.backend = "ZendEngine3";  // default
  Configure(app, group);
}

void zephir::commands::GenerateCommand::Configure(CLI::App* app,
                                                  const std::string& group) {
  auto cmd =
      app->add_subcommand(
             "generate",
             "Generates C code from the Zephir code without compiling it")
          ->group(group);

  // Add options to cmd, binding them to options.
  cmd->add_option(
      "--backend", options.backend,
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

void zephir::commands::GenerateCommand::Execute() {
  // Do stuff...
  std::cout << "NOT IMPLEMENTED" << std::endl;
}
