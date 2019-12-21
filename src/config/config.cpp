// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "config.hpp"

#include <sstream>
#include <utility>

#include "../filesystem/filesystem.hpp"

zephir::Config::Config(std::string path)
    : container_(), path_(std::move(path)), changed_(false) {
  container_ = YAML::Load(R"(
  {
    namespace: null,
    name: null,
    description: null,
    author: 'Zephir Team',
    version: 0.0.1,
    backend: ZendEngine3,
    verbose: false,
    silent: false,

    requires: {
      extensions: []
    },

    stubs: {
      path: ide/%version%/%namespace%,
      stubs-run-after-generate: false,
      banner: null
    },

    api: {
      path: doc/%version%,
      theme: {
        name: zephir,
        options: {
          github: null,
          analytics: null,
          main_color: '#333975',
          link_color: '#5a4b5e',
          link_hover_color: '#99182e'
        }
      }
    },

    warnings: {
      unused-variable: true,
      unused-variable-external: false,
      possible-wrong-parameter: true,
      possible-wrong-parameter-undefined: false,
      nonexistent-function: true,
      nonexistent-class: true,
      non-valid-isset: true,
      non-array-update: true,
      non-valid-objectupdate: true,
      non-valid-fetch: true,
      invalid-array-index: true,
      non-array-append: true,
      invalid-return-type: true,
      unreachable-code: true,
      nonexistent-constant: true,
      not-supported-magic-constant: true,
      non-valid-decrement: true,
      non-valid-increment: true,
      non-valid-clone: true,
      non-valid-new: true,
      non-array-access: true,
      invalid-reference: true,
      invalid-typeof-comparison: true,
      conditional-initialization: true
    },


    optimizations: {
      call-gatherer-pass: true,
      check-invalid-reads: false,
      constant-folding: true,
      internal-call-transformation: false,
      local-context-pass: true,
      static-constant-class-folding: true,
      static-type-inference-second-pass: true,
      static-type-inference: true
    },

    extra: {
      indent: spaces,
      export-classes: false
    }
  })");

  populate();
}

void zephir::Config::populate() {
  if (path_.empty() || !zephir::filesystem::Exists(path_)) {
    // Nothing to do if we unable to find config file at the disk.
    return;
  }

  // YAML::BadFile should normally never thrown here
  // because we did check for file existence before.
  try {
    auto yaml = YAML::LoadFile(path_);

    for (YAML::const_iterator it = yaml.begin(); it != yaml.end(); ++it) {
      const auto &key = it->first.as<std::string>();
      if (it->second.IsDefined()) {
        container_[key] = it->second;
      }
    }
  } catch (YAML::ParserException &e) {
    throw std::runtime_error("Config file is broken");
  }
}

bool zephir::Config::changed() { return changed_; }

zephir::ConfigPtr zephir::Config::factory(std::vector<std::string> &options,
                                          const std::string &path) {
  auto config = std::make_shared<zephir::Config>(path);

  if (!options.empty()) {
    // TODO(klay): Process config, use argv
  }

  return config;
}

bool zephir::Config::operator==(const zephir::Config &rhs) const {
  return std::tie(container_) == std::tie(rhs.container_);
}

zephir::Config &zephir::Config::operator=(const zephir::Config &rhs) = default;

template <class T, class S>
T zephir::Config::get(const std::string &key, const S &fallback) const {
  return container_[key].as<T, S>(fallback);
}

template <class T, class S>
T zephir::Config::get(const std::string &key, const std::string &ns,
                      const S &fallback) const {
  return container_[ns][key].as<T, S>(fallback);
}
