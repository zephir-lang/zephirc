// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "formatter.hpp"

#include <CLI/CLI11.hpp>
#include <vector>

zephir::commands::Formatter::Formatter() = default;

std::string zephir::commands::Formatter::make_usage(
    const CLI::App *app, __attribute__((unused)) const std::string name) const {
  std::stringstream out;

  out << get_label("Usage") << ":" << std::endl;

  if (app->get_parent()) {
    out << "  " << app->get_name();
  } else {
    out << "  " << get_label("COMMAND");
  }

  std::vector<std::string> groups = app->get_groups();

  // Print an OPTIONS badge if any options exist
  std::vector<const CLI::Option *> non_positionals = app->get_options(
      [](const CLI::Option *opt) { return opt->nonpositional(); });
  if (!non_positionals.empty()) {
    out << " [" << get_label("OPTIONS") << "]";
  }

  // Print an ARGUMENTS badge if any arguments exist
  // or we're show help for the main program
  std::vector<const CLI::Option *> positionals = app->get_options(
      [](const CLI::Option *opt) { return opt->get_positional(); });
  if (!app->get_parent() || !positionals.empty()) {
    out << " [" << get_label("ARGUMENTS") << "]";
  }

  out << std::endl;

  return out.str();
}

std::string zephir::commands::Formatter::make_description(
    const CLI::App *app) const {
  const char *BANNER = R"BANNER(
 _____              __    _
/__  /  ___  ____  / /_  (_)____
  / /  / _ \/ __ \/ __ \/ / ___/
 / /__/  __/ /_/ / / / / / /
/____/\___/ .___/_/ /_/_/_/
         /_/)BANNER";

  std::stringstream out;
  out << "";

  // Show banner and version only for main app
  if (!app->get_parent()) {
    std::string banner(BANNER);
    out << banner.replace(0, 1, "") << std::endl << std::endl;

    std::string desc = app->get_description();
    out << desc << std::endl << std::endl;
  }

  // TODO(klay): Deal with "min_options" and "max_options".
  // See parent class for more.

  return out.str();
}

std::string zephir::commands::Formatter::make_footer(
    const CLI::App *app) const {
  std::stringstream out;
  out << "";

  // Show general help usage only for the main app.
  // Any particular command should provide its own concrete help.
  const std::string &footer = app->get_footer();
  if (!app->get_parent() && !footer.empty()) {
    out << std::endl << footer << std::endl;
  } else if (app->get_parent()) {
    out << std::endl << get_label("Help") << ":" << std::endl;
    out << "  " << app->get_description() << "." << std::endl;
  }

  return out.str();
}
