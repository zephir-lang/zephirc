// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_API_HPP_
#define ZEPHIR_CONFIG_API_HPP_

#include <string>

#include <zephir/config/api/theme.hpp>
#include <zephir/config/yaml/api.hpp>

namespace zephir::config {
class Api {
 public:
  Api();
  explicit Api(std::string path, const api::Theme &theme);

  /**
   * @brief Encode Api object to the Yaml Node.
   *
   * @param aptr Api smart pointer
   * @return Yaml Node
   */
  friend YAML::Node
  YAML::convert<ApiPtr>::encode(const zephir::config::ApiPtr &aptr);

  /**
   * @brief Decode Yaml Node to the Api object.
   *
   * @param node Yaml Node
   * @param aptr Api smart pointer
   * @return true on success, false otherwise
   */
  friend bool YAML::convert<ApiPtr>::decode(const YAML::Node &node,
                                            zephir::config::ApiPtr &aptr);

  bool operator==(const Api &rhs) const;
  Api &operator=(const Api &rhs);

 private:
  std::string path_;
  api::Theme theme_;
};
}  // namespace zephir::config
#endif  // ZEPHIR_CONFIG_EXTRA_HPP_
