// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_OPTIMIZATIONS_HPP_
#define ZEPHIR_CONFIG_OPTIMIZATIONS_HPP_

#include "zephir/config/yaml/optimizations.hpp"

namespace zephir {
namespace config {
class Optimizations {
 public:
  Optimizations();
  explicit Optimizations(bool sti, bool stisp, bool lcp, bool cf, bool sccf,
                         bool cgp, bool cir, bool ict);

  friend YAML::Node YAML::convert<OptimizationsPtr>::encode(
      const zephir::config::OptimizationsPtr &optr);
  friend bool YAML::convert<OptimizationsPtr>::decode(
      const YAML::Node &node, zephir::config::OptimizationsPtr &optr);

  bool operator==(const Optimizations &rhs) const;
  Optimizations &operator=(const Optimizations &rhs);

 private:
  // static type inference
  bool sti_;
  // static type inference second pass
  bool stisp_;
  // local context pass
  bool lcp_;
  // constant folding
  bool cf_;
  // static constant class folding
  bool sccf_;
  // call gatherer pass
  bool cgp_;
  // check invalid reads
  bool cir_;
  // internal call transformation
  bool ict_;
};
}  // namespace config
}  // namespace zephir

#endif  // ZEPHIR_CONFIG_OPTIMIZATIONS_HPP_
