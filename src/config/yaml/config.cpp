// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include <zephir/config.hpp>

YAML::Node
YAML::convert<zephir::ConfigPtr>::encode(const zephir::ConfigPtr &cptr) {
  Node node;

  node["namespace"] = cptr->ns_;
  node["name"] = cptr->name_;
  node["description"] = cptr->description_;
  node["author"] = cptr->author_;
  node["version"] = cptr->version_;
  node["backend"] = cptr->backend_;
  node["verbose"] = cptr->verbose_;
  node["silent"] = cptr->silent_;
  node["requires"] =
      std::make_shared<zephir::config::Requires>(cptr->requires_);
  node["stubs"] = std::make_shared<zephir::config::Stubs>(cptr->stubs_);
  node["api"] = std::make_shared<zephir::config::Api>(cptr->api_);
  node["warnings"] =
      std::make_shared<zephir::config::Warnings>(cptr->warnings_);
  node["optimizations"] =
      std::make_shared<zephir::config::Optimizations>(cptr->optimizations_);
  node["extra"] = std::make_shared<zephir::config::Extra>(cptr->extra_);

  return node;
}

bool YAML::convert<zephir::ConfigPtr>::decode(const YAML::Node &node,
                                              zephir::ConfigPtr &cptr) {
  if (!node.IsMap()) {
    return false;
  }

  if (node["namespace"] && node["namespace"].IsScalar()) {
    cptr->ns_ = node["namespace"].as<std::string>();
  }

  if (node["name"] && node["name"].IsScalar()) {
    cptr->name_ = node["name"].as<std::string>();
  }

  if (node["description"] && node["description"].IsScalar()) {
    cptr->description_ = node["description"].as<std::string>();
  }

  if (node["author"] && node["author"].IsScalar()) {
    cptr->author_ = node["author"].as<std::string>();
  }

  if (node["version"] && node["version"].IsScalar()) {
    cptr->version_ = node["version"].as<std::string>();
  }

  if (node["backend"] && node["backend"].IsScalar()) {
    cptr->backend_ = node["backend"].as<std::string>();
  }

  if (node["verbose"] && node["verbose"].IsScalar()) {
    cptr->verbose_ = node["verbose"].as<bool>();
  }

  if (node["silent"] && node["silent"].IsScalar()) {
    cptr->silent_ = node["silent"].as<bool>();
  }

  if (node["requires"] && node["requires"].IsMap()) {
    auto r = std::make_shared<zephir::config::Requires>();
    YAML::convert<zephir::config::RequiresPtr>::decode(node["requires"], r);
    cptr->requires_ = *r;
  }

  if (node["stubs"] && node["stubs"].IsMap()) {
    auto s = std::make_shared<zephir::config::Stubs>();
    YAML::convert<zephir::config::StubsPtr>::decode(node["stubs"], s);
    cptr->stubs_ = *s;
  }

  if (node["api"] && node["api"].IsMap()) {
    auto a = std::make_shared<zephir::config::Api>();
    YAML::convert<zephir::config::ApiPtr>::decode(node["api"], a);
    cptr->api_ = *a;
  }

  if (node["warnings"] && node["warnings"].IsMap()) {
    auto w = std::make_shared<zephir::config::Warnings>();
    YAML::convert<zephir::config::WarningsPtr>::decode(node["warnings"], w);
    cptr->warnings_ = *w;
  }

  if (node["optimizations"] && node["optimizations"].IsMap()) {
    auto o = std::make_shared<zephir::config::Optimizations>();
    YAML::convert<zephir::config::OptimizationsPtr>::decode(
        node["optimizations"], o);
    cptr->optimizations_ = *o;
  }

  if (node["extra"] && node["extra"].IsMap()) {
    auto e = std::make_shared<zephir::config::Extra>();
    YAML::convert<zephir::config::ExtraPtr>::decode(node["extra"], e);
    cptr->extra_ = *e;
  }

  return true;
}
