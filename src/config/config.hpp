/// \file config.hpp
/// \brief The main Config class. Manages compiler global configuration.

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


  /// \brief Allows to check whether a \a key is defined.
  ///
  /// \param key The requested configuration key.
  /// \return true on success, false otherwise
  bool has(const std::string &key) const;

  /// \brief Allows to check whether a \a key in the given namespace (\a ns).
  ///
  /// \param key The requested configuration key.
  /// \param ns The requested configuration namespace.
  /// \return true on success, false otherwise
  bool has(const std::string &key, const std::string &ns) const;

  /// \brief Fetch a configuration value using a simple key.
  ///
  /// \tparam T Requested return type.
  /// \param key Which config item to look up.
  /// \param fallback  Fallback default value to use when configuration object
  /// has no value.
  ///
  /// \return Requested configuration setting if any,
  /// fallback otherwise
  template <typename T>
  inline T get(const std::string &key, const T &fallback) const;

  /// \brief Fetch a configuration value using a simple key.
  ///
  /// \tparam T Requested return type.
  /// \param key Which config item to look up.
  /// \param ns Used configuration namespace to retrieve value.
  /// \param fallback  Fallback default value to use when configuration object
  /// has no value.
  ///
  /// \return Requested configuration setting if any,
  /// fallback otherwise
  template <typename T>
  inline T get(const std::string &key, const std::string &ns,
               const T &fallback) const;

  /// \brief Set a configuration value, using simple key.
  ///
  /// \tparam T Used type for new value.
  /// \param key This configuration key will be set.
  /// \param rhs This value will be set for the given configuration key.
  /// \return Returns Config instance
  template <typename T>
  inline Config &set(const std::string &key, const T &rhs);

  /// \brief Set a configuration value, using simple key and the given
  /// namespace.
  ///
  /// \tparam T Used type for new value.
  /// \param key This configuration key will be set.
  /// \param ns This configuration namespace will be used.
  /// \param rhs This value will be set for the given configuration key.
  /// \return Returns Config instance
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
