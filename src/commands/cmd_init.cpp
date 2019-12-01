// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "cmd_init.hpp"

zephir::commands::InitCommand::InitCommand(CLI::App* app,
                                           const std::string& group) {
  options.backend = "ZendEngine3";  // default
  Configure(app, group);
}

void zephir::commands::InitCommand::Configure(CLI::App* app,
                                              const std::string& group) {
  auto cmd = app->add_subcommand("init", "Initializes a Zephir extension")
                 ->group(group);

  // Add options to cmd, binding them to options.
  cmd->add_option(
      "--backend", options.backend,
      "Used backend to generate extension [default: \"ZendEngine3\"]");
  cmd->add_option("namespace", options.ns, "The extension namespace");
  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  // TODO(klay): Make it better.
  // Right now I've set empty string to override parent footer
  cmd->footer("");

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([&]() { Execute(); });
}

void zephir::commands::InitCommand::Execute() {
  // Do stuff...
  std::cout << "Init command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
  std::cout << "    options.backend = " << options.backend << std::endl;
  std::cout << "    options.ns = " << options.ns << std::endl;
}
