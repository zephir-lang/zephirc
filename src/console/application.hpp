// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

/// \file application.hpp
/// \brief Represent console Application class.

#ifndef ZEPHIR_CLI_APPLICATION_HPP_
#define ZEPHIR_CLI_APPLICATION_HPP_

#include <string>
#include <vector>

#include "../config/config.hpp"
#include "commands/abstract_command.hpp"
#include "formatter.hpp"

namespace zephir::console {

/// \brief An Application is the container for a collection of commands.
///
/// \details It is the main entry point of a Console application. This class is
/// optimized for a standard CLI environment.
class Application {
 public:
  /// \brief Construct application object with a given configuration, CLI args
  /// and project base path.
  ///
  /// \param config The configuration of the current project
  /// \param args CLI args / options
  /// \param base_path The base path of the current project
  explicit Application(zephir::ConfigPtr config, std::vector<std::string> args,
                       const std::string& base_path);

  Application(const Application&) = delete;

  /// \brief Adds the console command.
  ///
  /// \param command Console command implements AbstractCommand
  void AddCommand(commands::CommandPtr command);

  /// \brief Runs the current application.
  ///
  /// \return 0 if everything went fine, or an error code
  int Run();

  Application& operator=(const Application&) = delete;

 private:
  /// A vector of CLI arguments
  std::vector<std::string> args_;

  /// Current working path
  const std::string& base_path_;

  /// An instance of the application Config
  zephir::ConfigPtr config_;

  /// An instance of the application Formatter
  std::shared_ptr<zephir::console::Formatter> formatter_;

  /// An instance of the CLI::App
  CLI::App_p app_;

  /// An instance of the CLI::Option used to indicate that help was requested
  /// (may be nullptr)
  CLI::Option* help_;

  /// A vector of application commands
  std::vector<commands::CommandPtr> commands_;
};
}  // namespace zephir::console

#endif  // ZEPHIR_SRC_CLI_APPLICATION_HPP_
