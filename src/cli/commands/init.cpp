// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "init.hpp"

#include <utility>

zephir::cli::commands::InitCommand::InitCommand(std::string name)
    : AbstractCommand(std::move(name)),
      options_(std::make_unique<InitOptions>()) {}

void zephir::cli::commands::InitCommand::Setup(CLI::App_p app) {
  auto cmd = app->group(group_)->add_subcommand(
      "init", "Initializes a Zephir extension");

  options_->backend = "ZendEngine3";

  // Add options to cmd, binding them to options.
  cmd->add_option(
      "--backend", options_->backend,
      "Used backend to generate extension [default: \"ZendEngine3\"]");
  cmd->add_option("namespace", options_->ns, "The extension namespace");
  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  // TODO(klay): Make it better.
  // Right now I've set empty string to override parent footer
  cmd->footer("");

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([&]() { Execute(); });
}

void zephir::cli::commands::InitCommand::Execute() {
  // Do stuff...
  std::cout << "Init command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
  std::cout << "    options.backend = " << options_->backend << std::endl;
  std::cout << "    options.ns = " << options_->ns << std::endl;
}
