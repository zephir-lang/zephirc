// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_HPP_
#define ZEPHIR_CONFIG_HPP_

#include <yaml-cpp/yaml.h>

#include <string>
#include <vector>

#include "ptr.hpp"

namespace zephir {
/**
 * @brief Manages compiler global configuration.
 */
class Config {
 public:
  /**
   * @brief Config constructor.
   */
  explicit Config(const std::string &path);

  /**
   * @brief Config destructor.
   */
  ~Config();

  /**
   * @brief Dumps the project configuration to the disk.
   */
  void dump();

  /**
   * @brief Is config changed?
   *
   * @return true if default config is changed, false otherwise.
   */
  bool changed();

  bool loaded();

  /**
   * \brief factory method to create a Config instance from argv and config
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
  static ConfigPtr factory(std::vector<std::string> &options,
                           const std::string &path);

  /// Check for a key existence
  bool has(const std::string &key) const;

  /// Check for a key existence in the given namespace
  bool has(const std::string &key, const std::string &ns) const;

  /// Getting a value by its key
  template <typename T>
  inline T get(const std::string &key, const T &fallback) const;

  /// Getting a value by its key and namespace
  template <typename T>
  inline T get(const std::string &key, const std::string &ns,
               const T &fallback) const;

  template <typename T>
  inline Config &set(const std::string &key, const T &rhs);

  template <typename T>
  inline Config &set(const std::string &key, const std::string &ns,
                     const T &rhs);

 private:
  static std::string getInitData() noexcept;

  YAML::Node container_;

  /**
   * \brief Populate config container_ from a file path_.
   */
  void populate();

  /**
   * @brief Used path to load project configuration.
   */
  const std::string &path_;

  /**
   * @brief Is project configuration was changed?
   */
  bool changed_;

  bool loaded_;
};
}  // namespace zephir

#include "impl.hpp"

#endif  // ZEPHIR_CONFIG_HPP_
