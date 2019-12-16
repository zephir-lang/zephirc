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

zephir::commands::Application::Application(std::vector<std::string> args)
    : base_path_(zephir::filesystem::GetCurrentWorkingPath()),
      args_(std::move(args)) {
  config_ = zephir::Config::Factory(args_, base_path_ + "/.zephir.yml");

  auto out = "Zephir " + std::string(ZEPHIR_VERSION_STRING);
  out += " by Serghei Iakovlev and Alexander Andriiako";

  app_ = std::make_shared<CLI::App>(out, "zephir");
};

void zephir::commands::Application::Run() {}
