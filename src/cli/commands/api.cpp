// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "api.hpp"

#include <utility>

zephir::cli::commands::ApiCommand::ApiCommand(std::string name)
    : AbstractCommand(std::move(name)),
      options_(std::make_unique<ApiOptions>()) {}

void zephir::cli::commands::ApiCommand::Setup(CLI::App_p app) {
  auto cmd = app->group(group_)->add_subcommand(
      "api",
      "Generates a HTML API based on the classes "
      "exposed in the extension");

  // TODO(klay): Use config here
  options_->backend = "ZendEngine3";

  cmd->get_formatter()->column_width(19);

  // Add options to cmd, binding them to options.
  cmd->add_option(
      "--backend", options_->backend,
      "Used backend to generate extension [default: \"ZendEngine3\"]");
  cmd->add_option("-p,--path", options_->template_path,
                  "The API theme to be used");
  cmd->add_option("-o,--output", options_->output,
                  "Output directory to generate theme");
  cmd->add_option("--options", options_->theme_options, "Theme options");
  cmd->add_option("--url", options_->url,
                  "The base URL to be used when generating links");
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

void zephir::cli::commands::ApiCommand::Execute() {
  // Do stuff...
  std::cout << "Api command" << std::endl;
  std::cout << "NOT IMPLEMENTED" << std::endl;
  std::cout << "    options.template_path = " << options_->template_path
            << std::endl;
  std::cout << "    options.backend = " << options_->backend << std::endl;
  std::cout << "    options.output = " << options_->output << std::endl;
  std::cout << "    options.theme_options = " << options_->theme_options
            << std::endl;
  std::cout << "    options.url = " << options_->url << std::endl;
}
