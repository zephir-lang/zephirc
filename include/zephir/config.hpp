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

#include <zephir/config/api.hpp>
#include <zephir/config/extra.hpp>
#include <zephir/config/optimizations.hpp>
#include <zephir/config/requires.hpp>
#include <zephir/config/stubs.hpp>
#include <zephir/config/warnings.hpp>

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

  std::string ns_;
  std::string name_;
  std::string description_;
  std::string author_;
  std::string version_;
  bool verbose_;

  /**
   * @brief Used path to load project configuration.
   */
  std::string path_;

  /**
   * @brief Is project configuration was changed?
   */
  bool changed_;

  config::Requires requires;
  config::Stubs stubs;
  config::Api api;
  config::Warnings warnings;
  config::Optimizations optimizations;
  zephir::config::Extra extra;
};
}  // namespace zephir

#endif  // ZEPHIR_CONFIG_HPP_
