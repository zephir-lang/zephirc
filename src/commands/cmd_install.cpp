// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "cmd_install.hpp"

#include <zephir/commands.hpp>

using zephir::commands::InstallOptions;

void zephir::commands::SetupInstallCommand(const std::shared_ptr<CLI::App>& app,
                                           const std::string& group) {
  auto options = std::make_shared<InstallOptions>();
  auto cmd =
      app->add_subcommand("install",
                          "Installs the extension in the extension directory")
          ->group(group);

  options->dev = true;

  // Add options to cmd, binding them to options.
  auto dev = cmd->add_flag(
      "--dev", "Compile the extension in development mode [default]");
  auto no_dev =
      cmd->add_flag("--no-dev", "Compile the extension in production mode");
  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  if (no_dev->count()) {
    options->dev = false;
  }

  if (dev->count()) {
    options->dev = true;
  }

  // TODO(klay): Check for PHP build mode
  // else {
  //  options.dev = true;
  //}

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
  cmd->callback([options]() { ExecuteInstallCommand(*options); });
}

void zephir::commands::ExecuteInstallCommand(InstallOptions const& options) {
  // Do stuff...
  std::cout << "Install command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
  std::cout << "    options.dev = " << options.dev << std::endl;
}
