// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "Application.hpp"

#include <utility>

#include <zephir/Version.hpp>

#include "FileSystem/FileSystem.hpp"

zephir::console::Application::Application(zephir::ConfigPtr config,
                                          std::vector<std::string> args,
                                          const std::string& base_path)
    : args_(std::move(args)),
      base_path_(base_path),
      config_(std::move(config)),
      app_(std::make_shared<CLI::App>()),
      help_(nullptr),
      commands_() {
  auto out =
      std::string(ZEPHIR_PACKAGE_NAME) + " " + std::string(ZEPHIR_VERSION);

  app_->description(out);
  app_->name("zephir");

  out = "See \"" + app_->get_name() + " <command> --help\"";
  out += " to read about a specific command or concept.";

  app_->footer(out);

  // Create an instance of the CLI Formatter
  app_->formatter(std::make_shared<zephir::console::Formatter>());

  app_->get_formatter()->column_width(17);
  app_->get_formatter()->label("OPTIONS", "options");
  app_->get_formatter()->label("ARGUMENTS", "arguments");
  app_->get_formatter()->label("COMMAND", "command");
  app_->get_formatter()->label("Positionals", "Arguments");

  // Global options

  app_->add_flag("--dumpversion", PrintVersion,
                 "Print the version of the compiler and don't do anything else "
                 "(also works with a single hyphen)");

  app_->add_flag("--vernum", PrintVersionId,
                 "Print the version of the compiler as integer and quit");

  app_->add_flag("-V, --version", PrintFullVersion,
                 "Print compiler version information and quit");

  // Remove help flag because it shortcuts all processing
  app_->set_help_flag();

  // Add custom flag that activates help
  help_ = app_->add_flag("-h, --help", "Print this help message and quit");
}

void zephir::console::Application::PrintVersion(std::size_t /* count */) {
  std::cout << ZEPHIR_VERSION << std::endl;
}

void zephir::console::Application::PrintFullVersion(std::size_t /* count */) {
  std::cout << ZEPHIR_VERSION_FULL << " (built: " << ZEPHIR_PACKAGE_BUILD_DATE
            << ") " << std::endl;
  std::cout << "Copyright " << ZEPHIR_COPYRIGHT << " (" << ZEPHIR_PACKAGE_URL
            << ")" << std::endl;
  std::cout << "This is free software; see the source for copying "
               "conditions.  There is NO"
            << std::endl;
  std::cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
               "PARTICULAR PURPOSE."
            << std::endl
            << std::endl;
}

void zephir::console::Application::PrintVersionId(std::size_t /* count */) {
  std::cout << ZEPHIR_VERSION_ID << std::endl;
}

void zephir::console::Application::AddCommand(
    zephir::console::commands::CommandPtr command) {
  if (command) {
    commands_.push_back(std::move(command));
  }
}

int zephir::console::Application::Run() {
  for (const auto& cmd : commands_) {
    cmd->Setup(app_);
  }

  try {
    app_->parse(args_);

    if (*help_) {
      throw CLI::CallForHelp();
    }
  } catch (const CLI::Error& e) {
    auto retval = app_->exit(e);

    // TODO(klay): print error message
    return retval;
  }

  return EXIT_SUCCESS;
}
