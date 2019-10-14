#include <iostream>
#include <cstring>

#include "commands/commands.hpp"

int main(int argc, char **argv) {
    commands::Cmd cmd{};
    std::memset(&cmd, 0, sizeof(cmd));

    if (!commands::parseopt(argv, cmd)) {
        return 1;
    }

    switch (cmd.kind) {
        case commands::NONE:
            std::cout << "NONE" << std::endl;
            break;
        case commands::API:
            std::cout << "API" << std::endl;
            std::cout << "\tbackend: " << (cmd.api.backend ? cmd.api.backend : "-") << std::endl;
            std::cout << "\tpath: " << (cmd.api.path ? cmd.api.path : "-") << std::endl;
            std::cout << "\toutput: " << (cmd.api.output ? cmd.api.output : "-") << std::endl;
            std::cout << "\toptions: " << (cmd.api.options ? cmd.api.options : "-") << std::endl;
            std::cout << "\turl: " << (cmd.api.url ? cmd.api.url : "-") << std::endl;
            std::cout << "\thelp: " << cmd.api.help << std::endl;
            break;
    }

    return 0;
}
