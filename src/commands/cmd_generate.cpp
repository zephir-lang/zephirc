// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "cmd_generate.hpp"

#include <CLI/CLI11.hpp>

zephir::commands::GenerateCommand::GenerateCommand(CLI::App& app,
                                                   const std::string& group) {
  options.backend = "ZendEngine3";  // default
  Configure(app, group);
}

void zephir::commands::GenerateCommand::Configure(CLI::App& app,
                                                  const std::string& group) {
  auto cmd =
      app.add_subcommand(
             "generate",
             "Generates C code from the Zephir code without compiling it")
          ->group(group);

  // Add options to cmd, binding them to options.
  cmd->add_option("--backend", options.backend,
                  "Used backend to generate extension", true);

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([&]() { Execute(); });
}

void zephir::commands::GenerateCommand::Execute() {
  // Do stuff...
  std::cout << "Working with backend: " << options.backend << std::endl;
}
