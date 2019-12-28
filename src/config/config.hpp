// This file is part of the Zephir.
//
// (c) Phalcon Team <team@zephir-lang.com>
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
/// \brief Manages compiler global configuration.
class Config {
 public:
  /// \brief Construct Config object using the given path to the configuration
  /// file.
  ///
  /// \param path The used path to load the project configuration.
  explicit Config(const std::string &path);

  /// \brief Dumps the project configuration to the disk.
  ///
  /// \param path The used path to dump the project configuration.
  void dump(const std::string &path);

  /// \brief The factory method to create a Config instance from argv and config
  /// file.
  ///
  /// \details Initialize configuration from both the CLI and a possible config
  /// file. Items specified in the CLI take priority over any settings loaded
  /// from config file. The Config object, if file not found in the given path,
  /// will load sane defaults.
  ///
  /// \param options Provided command line arguments
  /// \param path The path to the project configuration file
  /// \return A fresh Config instance with loaded configurations
  static ConfigPtr factory(std::vector<std::string> &options,
                           const std::string &path);

  /// \brief Check for a key existence
  bool has(const std::string &key) const;

  /// \brief Check for a key existence in the given namespace
  bool has(const std::string &key, const std::string &ns) const;

  /// \brief Gets a value by its key
  template <typename T>
  inline T get(const std::string &key, const T &fallback) const;

  /// \brief Gets a value by its key and namespace
  template <typename T>
  inline T get(const std::string &key, const std::string &ns,
               const T &fallback) const;

  /// \brief Sets a value for a provided key
  template <typename T>
  inline Config &set(const std::string &key, const T &rhs);

  /// \brief Sets a value for a provided key for the the given namespace
  template <typename T>
  inline Config &set(const std::string &key, const std::string &ns,
                     const T &rhs);

 private:
  /// \brief Gets the initial project configuration data
  static std::string getInitData() noexcept;

  /// \brief Populate config container using the given path to the configuration
  /// file.
  ///
  /// \param path The used path to load project configuration.
  void populate(const std::string &path);

  YAML::Node container_;
};
}  // namespace zephir

#include "impl.hpp"

#endif  // ZEPHIR_CONFIG_HPP_
