/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "RedexTool.h"
#include "Tool.h"
#include "ToolRegistry.h"

static constexpr char usage_header[] =
    "Usage:\n"
    "  redex-tool [<options>]\n"
    "  redex-tool <tool> --help\n"
    "  redex-tool <tool> [<tool-options>]\n"
    "\n"
    "Available tools:"
  ;
static constexpr char usage_footer[] =
    "\n"
    "Options:"
  ;

void show_help(const po::options_description& od) {
  std::cout << usage_header << std::endl;
  for (const auto& tool : ToolRegistry::get().get_tools()) {
    printf("  %-20s %s\n", tool->name().c_str(), tool->desc().c_str());
  }
  std::cout << usage_footer << std::endl << od << std::endl;
}

int main(int argc, char* argv[]) {
  po::options_description od;
  od.add_options()
    ("help,h", "show this screen and exit")
  ;

  Tool* tool =
    argc > 1 ? ToolRegistry::get().get_tool(argv[1]) : nullptr;
  if (tool) {
    tool->add_options(od);
  }

  // This is annoying. Since arguments can be required, we can't parse
  // arguments to figure out that help was asked for. So, manually look
  // for '--help' or '-h' in all argv's >= 2
  if (tool && argc >= 2) {
    for (int i = 2 ; i < argc ; ++i) {
      if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
        show_help(od);
        return 0;
      }
    }
  }

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, od), vm);
  po::notify(vm);

  if (vm.count("help")) {
    show_help(od);
    return 0;
  } else if (!tool) {
    show_help(od);
    if (argc > 1) {
      std::cout << argv[1] << " is not a valid tool name!" << std::endl;
    }
    return 1;
  } else {
    g_redex = new RedexContext();
    tool->run(vm);
    delete g_redex;
    return 0;
  }
}
