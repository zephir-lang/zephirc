#include "zephir/config/yaml/extra.hpp"

#include "zephir/config/extra.hpp"

YAML::Node YAML::convert<zephir::config::ExtraPtr>::encode(
    const zephir::config::ExtraPtr &eptr) {
  Node node;
  node["indent"] = eptr->indent_;
  node["export-classes"] = eptr->exportc_;

  return node;
}

bool YAML::convert<zephir::config::ExtraPtr>::decode(
    const YAML::Node &node, zephir::config::ExtraPtr &eptr) {
  if (!node.IsMap()) {
    return false;
  }

  if (node["indent"] && node["indent"].IsScalar()) {
    eptr->indent_ = node["indent"].as<std::string>();
  }

  if (node["export-classes"] && node["export-classes"].IsScalar()) {
    eptr->exportc_ = node["export-classes"].as<bool>();
  }

  return true;
}
