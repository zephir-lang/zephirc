// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "formatter.hpp"

std::string
zephir::console::Formatter::make_usage(const CLI::App *app,
                                       const std::string /* name */) const {
  auto out = get_label("Usage") + ":\n";

  if (app->get_parent()) {
    out += "  " + app->get_name();
  } else {
    out += "  " + get_label("COMMAND");
  }

  auto groups = app->get_groups();

  // Print an OPTIONS badge if any options exist
  auto non_positionals = app->get_options(
      [](const CLI::Option *opt) { return opt->nonpositional(); });
  if (!non_positionals.empty()) {
    out += " [" + get_label("OPTIONS") + "]";
  }

  // Print an ARGUMENTS badge if any arguments exist
  // or we're show help for the main program
  auto positionals = app->get_options(
      [](const CLI::Option *opt) { return opt->get_positional(); });
  if (!app->get_parent() || !positionals.empty()) {
    out += " [--] [" + get_label("ARGUMENTS") + "]";
  }

  return out += "\n";
}

std::string
zephir::console::Formatter::make_description(const CLI::App *app) const {
  std::string out;

  // Show banner and version only for main app
  if (!app->get_parent()) {
    const auto BANNER = R"BANNER(
 _____              __    _
/__  /  ___  ____  / /_  (_)____
  / /  / _ \/ __ \/ __ \/ / ___/
 / /__/  __/ /_/ / / / / / /
/____/\___/ .___/_/ /_/_/_/
         /_/)BANNER";

    std::string banner(BANNER);
    out += banner.replace(0, 1, "") + "\n\n";

    auto desc = app->get_description();
    out += desc + "\n\n";
  }

  // TODO(klay): Deal with "min_options" and "max_options".
  // See parent class for more.

  return out;
}

std::string zephir::console::Formatter::make_footer(const CLI::App *app) const {
  std::string out;

  // Show general help usage only for the main app.
  // Any particular command should provide its own concrete help.
  const auto &footer = app->get_footer();
  if (!app->get_parent() && !footer.empty()) {
    out += "\n" + footer + "\n";
  } else if (app->get_parent()) {
    out += "\n" + get_label("Help") + ":\n";
    out += "  " + app->get_description() + ".\n";

    // Any additional command specific help should be
    // declared in the footer.
    if (!app->get_footer().empty()) {
      out += "  " + app->get_footer() + "\n";
    }
  }

  return out;
}
