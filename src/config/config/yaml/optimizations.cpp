// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "zephir/config/yaml/optimizations.hpp"

#include "zephir/config/optimizations.hpp"

YAML::Node YAML::convert<zephir::config::OptimizationsPtr>::encode(
    const zephir::config::OptimizationsPtr &optr) {
  Node node;

  node["static-type-inference"] = optr->sti_;
  node["static-type-inference-second-pass"] = optr->stisp_;
  node["local-context-pass"] = optr->lcp_;
  node["constant-folding"] = optr->cf_;
  node["static-constant-class-folding"] = optr->sccf_;
  node["call-gatherer-pass"] = optr->cgp_;
  node["check-invalid-reads"] = optr->cir_;
  node["internal-call-transformation"] = optr->ict_;

  return node;
}

bool YAML::convert<zephir::config::OptimizationsPtr>::decode(
    const YAML::Node &node, zephir::config::OptimizationsPtr &optr) {
  if (!node.IsMap()) {
    return false;
  }

  if (node["static-type-inference"] &&
      node["static-type-inference"].IsScalar()) {
    optr->sti_ = node["static-type-inference"].as<bool>();
  }

  if (node["static-type-inference-second-pass"] &&
      node["static-type-inference-second-pass"].IsScalar()) {
    optr->stisp_ = node["static-type-inference-second-pass"].as<bool>();
  }

  if (node["local-context-pass"] && node["local-context-pass"].IsScalar()) {
    optr->lcp_ = node["local-context-pass"].as<bool>();
  }

  if (node["constant-folding"] && node["constant-folding"].IsScalar()) {
    optr->cf_ = node["constant-folding"].as<bool>();
  }

  if (node["static-constant-class-folding"] &&
      node["static-constant-class-folding"].IsScalar()) {
    optr->sccf_ = node["static-constant-class-folding"].as<bool>();
  }

  if (node["call-gatherer-pass"] && node["call-gatherer-pass"].IsScalar()) {
    optr->cgp_ = node["call-gatherer-pass"].as<bool>();
  }

  if (node["check-invalid-reads"] && node["check-invalid-reads"].IsScalar()) {
    optr->cir_ = node["check-invalid-reads"].as<bool>();
  }

  if (node["internal-call-transformation"] &&
      node["internal-call-transformation"].IsScalar()) {
    optr->ict_ = node["internal-call-transformation"].as<bool>();
  }

  return true;
}
