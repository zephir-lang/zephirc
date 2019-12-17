// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <utility>

#include <zephir/cli/commands/install_command.hpp>

zephir::cli::commands::InstallCommand::InstallCommand(std::string name)
    : Command(std::move(name)), options_(std::make_unique<InstallOptions>()) {}

void zephir::cli::commands::InstallCommand::Setup(
    std::shared_ptr<CLI::App> app) {
  auto cmd = app->group(group_)->add_subcommand(
      "install", "Installs the extension in the extension directory");

  options_->dev = true;

  // Add options to cmd, binding them to options.
  auto dev = cmd->add_flag(
      "--dev", "Compile the extension in development mode [default]");
  auto no_dev =
      cmd->add_flag("--no-dev", "Compile the extension in production mode");
  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  // TODO(klay): Check for PHP build mode if no_dev == false && dev == false
  options_->dev = no_dev->count() <= dev->count();

  const char* HELP = R"HELP(
  Using --dev option will force compiling the extension in development mode
  (debug symbols and no optimizations). An extension compiled with debugging symbols means
  you can run a program or library through a debugger and the debugger's output will be user
  friendlier. These debugging symbols also enlarge the program or library significantly.

  NOTE: Zephir development mode will be enabled silently if your PHP binary was compiled in
  a debug configuration.

  In some cases, we would like to get production ready extension even if the PHP binary was
  compiled in a debug configuration. Use --no-dev option to achieve this behavior.)HELP";

  // TODO(klay): These flags should be parsed before CLI11 initialization.
  // Current plan is:
  // 1. read these flags
  // 2. set the appropriate configuration
  // 3. remove these flags (if any) from argv
  cmd->footer(std::string(HELP) + "\n" + CommonCompilationFlagsHelp());

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([&]() { Execute(); });
}

void zephir::cli::commands::InstallCommand::Execute() {
  // Do stuff...
  std::cout << "Install command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
  std::cout << "    options.dev = " << options_->dev << std::endl;
  ;
}
