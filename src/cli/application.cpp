// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <utility>

#include <zephir/cli/application.hpp>
#include <zephir/version.hpp>

#include "../filesystem/filesystem.hpp"

zephir::cli::Application::Application(std::vector<std::string> args,
                                      std::string base_path)
    : args_(std::move(args)),
      base_path_(std::move(base_path)),
      config_(zephir::Config::Factory(args_, base_path_ + "/.zephir.yml")),
      formatter_(std::make_shared<zephir::cli::Formatter>()),
      app_(std::make_shared<CLI::App>()),
      help_(nullptr),
      commands_() {
  auto out = std::string(ZEPHIR_NAME) + " " +
             std::string(ZEPHIR_VERSION_STRING) + " by " +
             std::string(ZEPHIR_AUTHORS);

  app_->description(out);
  app_->name("zephir");

  out = "See \"" + app_->get_name() + " <command> --help\"";
  out += " to read about a specific command or concept.";

  app_->footer(out);

  formatter_->column_width(17);
  formatter_->label("OPTIONS", "options");
  formatter_->label("ARGUMENTS", "arguments");
  formatter_->label("COMMAND", "command");
  formatter_->label("Positionals", "Arguments");

  app_->formatter(formatter_);

  // Global options
  app_->add_flag("--dumpversion",
                 "Print the version of the compiler and don't do anything else "
                 "(also works with a single hyphen)");

  help_ = app_->set_help_flag("-h, --help", "Print this help message and quit");

  app_->add_flag("--vernum",
                 "Print the version of the compiler as integer and quit");
  app_->add_flag("-V, --version",
                 "Print compiler version information and quit");
};

void zephir::cli::Application::AddCommand(
    zephir::cli::commands::CommandPtr command) {
  if (command) {
    commands_.push_back(std::move(command));
  }
}

int zephir::cli::Application::Run() {
  for (const auto& cmd : commands_) {
    cmd->Setup(app_);
  }

  try {
    app_->parse(args_);

    if (*help_) {
      throw CLI::CallForHelp();
    }
  } catch (const CLI::ParseError& e) {
    auto retval = app_->exit(e);
    if (e.get_name() == "CallForHelp") {
      retval = EXIT_HELP;
    }

    // TODO(klay): print error message
    return retval;
  }

  return 0;
}