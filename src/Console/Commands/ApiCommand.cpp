// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "ApiCommand.hpp"

#include <utility>

zephir::console::commands::ApiCommand::ApiCommand(std::string name)
    : AbstractCommand(std::move(name)),
      options_(std::make_unique<ApiOptions>()) {}

void zephir::console::commands::ApiCommand::Setup(CLI::App_p app) {
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
         "Used backend to generate extension [default: \"ZendEngine3\"]")
      ->type_name("BACKEND");

  cmd->add_option("-p,--path", options_->template_path,
                  "The API theme to be used")
      ->type_name("PATH");

  cmd->add_option("-o,--output", options_->output,
                  "Output directory to generate theme")
      ->type_name("OUTPUT");

  cmd->add_option("--options", options_->theme_options, "Theme options")
      ->type_name("OPTIONS");

  cmd->add_option("--url", options_->url,
                  "The base URL to be used when generating links")
      ->type_name("URL");

  cmd->set_help_flag("-h, --help", "Print this help message and quit");

  cmd->footer(CommonCompilationFlagsHelp());

  // Set the run function as callback to be called when this subcommand is
  // issued.
  cmd->callback([&]() { Execute(); });
}

void zephir::console::commands::ApiCommand::Execute() {
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
