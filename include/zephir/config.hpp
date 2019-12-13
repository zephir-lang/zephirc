// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_HPP_
#define ZEPHIR_CONFIG_HPP_

#include <memory>
#include <string>
#include <vector>

#include "zephir/config/extra.hpp"
#include "zephir/config/optimizations.hpp"
#include "zephir/config/requires.hpp"
#include "zephir/config/stubs.hpp"
#include "zephir/config/warnings.hpp"

namespace zephir {
/**
 * @brief Manages compiler global configuration.
 */
class Config {
 public:
  /**
   * @brief Config constructor.
   *
   * @param path The default name/location of the config file
   * @throws std::runtime_error Thrown if config could not be parsed
   */
  explicit Config(std::string path);

  /**
   * @brief Config destructor.
   */
  ~Config();

  /**
   * @brief Writes the configuration if it has been changed.
   */
  void DumpToFile();

  /**
   * @brief Is config changed?
   *
   * @return true if default config is changed, false otherwise.
   */
  bool IsChanged();

  /**
   * @brief Factory method to create a Config instance from argv and config
   * file. Initialize configuration from both the CLI and a possible config
   * file.
   *
   * @param options Provided command line arguments
   * @param path The default name/location of the config file
   * @return A fresh Config instance with loaded configurations
   *
   * Items specified in the CLI take priority over any settings loaded from
   * config file. Configuration file, if not found from the provided parameter
   * or set specifically in the CLI, will also search through any search paths
   * provided from the CLI for the provided filename.
   */
  static std::shared_ptr<Config>
  CreateFromArgv(std::vector<std::string> &options, const std::string &path);

 private:
  /**
   * @brief Populate project configuration.
   *
   * @param path Configuration file.
   * @return 0 on success, a positive number on failure
   */
  static int Populate(const std::string &path);

  /**
   * Default configuration for project.
   */
  struct Container {
    std::string ns;
    std::string name;
    std::string description;
    std::string author;
    std::string version = "0.0.1";
    bool verbose = false;

    zephir::config::Requires requires;
    zephir::config::Stubs stubs;

    struct Api {
      std::string path = "doc/%version%";

      struct Theme {
        std::string name = "zephir";
        struct Options {
          std::string github = "";
          std::string analytics = "";
          std::string main_color = "#3E6496";
          std::string link_color = "#3E6496";
          std::string link_hover_color = "#5F9AE7";
        } options;
      } theme;
    } api;

    zephir::config::Warnings warnings;
    zephir::config::Optimizations optimizations;
    zephir::config::Extra extra;
  } container_;

  std::string path_;

  /**
   * Is config changed?
   */
  bool changed_;
};
}  // namespace zephir

#endif  // ZEPHIR_CONFIG_HPP_
