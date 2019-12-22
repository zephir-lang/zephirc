// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#include "config.hpp"

#include <fstream>
#include <regex>

#include "../filesystem/filesystem.hpp"

zephir::Config::Config(const std::string &path)
    : container_(YAML::Load(getInitData())),
      path_(path),
      changed_(false),
      loaded_(false) {
  populate();
}

zephir::Config::Config::~Config() {
  if (changed_) {
    dump();
  }
}

void zephir::Config::dump() {
  if (!path_.empty() && !zephir::filesystem::exists(path_)) {
    std::ofstream file(path_);
    file << container_;
    file.close();
  }
}

void zephir::Config::populate() {
  if (path_.empty() || !zephir::filesystem::exists(path_)) {
    // Nothing to do if we unable to find config file at the disk.
    return;
  }

  // YAML::BadFile should normally never thrown here
  // because we did check for file existence before.
  try {
    auto yaml = YAML::LoadFile(path_);
    loaded_ = true;

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
bool zephir::Config::loaded() { return loaded_; }

zephir::ConfigPtr zephir::Config::factory(std::vector<std::string> &options,
                                          const std::string &path) {
  auto config = std::make_shared<zephir::Config>(path);

  const std::regex no_optimizations("^-fno-([a-z0-9-]+)$");

  const auto check = [&](const std::string &op) {
    std::smatch match;
    if (std::regex_search(op, match, no_optimizations)) {
      config->set(match.str(1), "optimizations", false);
      return true;
    }

    return false;
  };

  options.erase(std::remove_if(std::begin(options), std::end(options), check),
                std::end(options));

  return config;
}

std::string zephir::Config::getInitData() noexcept {
  return R"(
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
  })";
}
