// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <utility>

#include <zephir/cli/commands/clean.hpp>

zephir::cli::commands::CleanCommand::CleanCommand(std::string name)
    : AbstractCommand(std::move(name)) {}

void zephir::cli::commands::CleanCommand::Setup(CLI::App_p app) {
  auto cmd = app->group(group_)->add_subcommand(
      "clean", "Cleans any object files created by the extension");

  // Add options to cmd, binding them to options.
  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  // TODO(klay): Make it better.
  // Right now I've set empty string to override parent footer
  cmd->footer("");

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([&]() { Execute(); });
}

void zephir::cli::commands::CleanCommand::Execute() {
  // Do stuff...
  std::cout << "Fullclean command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
}
