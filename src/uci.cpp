#include "uci.hpp"

#include <ios>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>

namespace Clockwork::UCI {

void UCIHandler::loop() {
    std::string input, command;

    while (std::getline(std::cin, input))
    {
        std::istringstream is{input};

        is >> std::skipws >> command;

        if (command == "isready")
            std::cout << "readyok" << std::endl;
        else if (command == "quit")
            break;
        else
            std::cout << "Unknown command" << std::endl;
    }
}

}
