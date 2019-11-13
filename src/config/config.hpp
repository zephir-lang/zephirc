// This file is part of the Zephir.
//
// (c) Zephir Team <team@zephir-lang.com>
//
// For the full copyright and license information, please view
// the LICENSE file that was distributed with this source code.

#ifndef ZEPHIR_CONFIG_CONFIG_HPP_
#define ZEPHIR_CONFIG_CONFIG_HPP_

#include <map>
#include <set>
#include <string>

#define INDENT_USING_SPACES 1;
#define INDENT_USING_TABS 2;

namespace zephir {
struct Config {
  std::string ns;
  std::string name;
  std::string description;
  std::string author;
  std::string version = "0.0.1";
  bool verbose = false;

  struct Requires {
    std::set<std::string> extensions = {};
  } requires;

  struct Stubs {
    std::string path = "ide/%version%/%namespace%";
    bool stubs_run_after_generate = false;
  } stubs;

  struct Api {
    std::string path = "doc/%version%";

    struct Theme {
      std::string name = "zephir";
      std::map<std::string, std::string> options;
    } theme;
  } api;

  struct Warnings {
    bool unused_variable = false;
    bool unused_variable_external = false;
    bool possible_wrong_parameter = false;
    bool possible_wrong_parameter_undefined = false;
    bool nonexistent_function = true;
    bool nonexistent_class = true;
    bool non_valid_isset = true;
    bool non_array_update = true;
    bool non_valid_objectupdate = true;
    bool non_valid_fetch = true;
    bool invalid_array_index = true;
    bool non_array_append = true;
    bool invalid_return_type = true;
    bool unreachable_code = true;
    bool nonexistent_constant = true;
    bool not_supported_magic_constant = true;
    bool non_valid_decrement = true;
    bool non_valid_increment = true;
    bool non_valid_clone = true;
    bool non_valid_new = true;
    bool non_array_access = true;
    bool invalid_reference = true;
    bool invalid_typeof_comparison = true;
    bool conditional_initialization = true;
  } warnings;

  struct Optimizations {
    bool static_type_inference = true;
    bool static_type_inference_second_pass = true;
    bool local_context_pass = true;
    bool constant_folding = true;
    bool static_constant_class_folding = true;
    bool call_gatherer_pass = true;
    bool check_invalid_reads = false;
    bool internal_call_transformation = false;
  } optimizations;

  struct Extra {
    unsigned char indent = INDENT_USING_SPACES;
    bool export_classes = false;
  } extra;

  Config() {
    api.theme.options["github"] = "";
    api.theme.options["analytics"] = "";
    api.theme.options["main_color"] = "#3E6496";
    api.theme.options["link_color"] = "#3E6496";
    api.theme.options["link_hover_color"] = "#5F9AE7";
  }
};

/** Initialize configuration from both the CLI and a possible config file.
 * @param argc Number of CLI arguments provided
 * @param argv Provided CLI arguments
 * @param config_file The default name/location of the config file
 * @return All loaded configurations
 *
 * Items specified in the CLI take priority over any settings loaded from config
 * file. Configuration file, if not found from the provided parameter or set
 * specifically in the CLI, will also search through any search paths provided
 * from the CLI for the provided filename.
 */
Config load_config(int argc, char **argv, std::string config_file);
}  // namespace zephir

#endif  // ZEPHIR_CONFIG_CONFIG_HPP_
