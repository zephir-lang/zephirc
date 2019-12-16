// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "application.hpp"

#include <utility>

#include <zephir/filesystem.hpp>
#include <zephir/version.hpp>

zephir::cli::Application::Application(std::vector<std::string> args)
    : base_path_(zephir::filesystem::GetCurrentWorkingPath()),
      args_(std::move(args)) {
  config_ = zephir::Config::Factory(args_, base_path_ + "/.zephir.yml");

  auto out = std::string(ZEPHIR_NAME) + " " +
             std::string(ZEPHIR_VERSION_STRING) + " by " +
             std::string(ZEPHIR_AUTHORS);

  app_ = std::make_shared<CLI::App>(out, "zephir");

  out = "See \"" + app_->get_name() + " <command> --help\"";
  out += " to read about a specific command or concept.";

  app_->footer(out);
};

void zephir::cli::Application::Run() {}

void zephir::cli::Application::AddCommand(zephir::cli::commands::Command) {}
