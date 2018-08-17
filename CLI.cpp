/* MIT License

Copyright (c) 2018 Eridan Domoratskiy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include "CLI.h"

#include <iostream>

void CLI::run() {
    // TODO Menu with actions
}

/*
void CLI::printHelp() {
    std::cout << "Using:\n" <<
                 "  " << * parser.arguments.front() << " [<options>]";

    bool first = false;
    for (const auto & argument: parser.arguments) {
        if (!first) {
            first = true;
            continue;
        }

        std::cout << ' ';

        if (!argument.required) {
            std::cout << '[';
        }

        std::cout << '<' << argument.name << '>';

        if (!argument.required) {
            std::cout << ']';
        }
    }

    if (parser.arguments.size() > 1) {
        std::cout << "\n\n"
                     "Arguments:\n\n";

        first = false;
        for (const auto & argument: parser.arguments) {
            if (!first) {
                first = true;
                continue;
            }

            std::cout << "  " << argument.name << '\n';

            for (const std::string & line: argument.description) {
                std::cout << "    " << line << "\n";
            }

            std::cout << '\n';
        }
    }

    std::cout << "\n\n"
                 "Allowed options:\n\n";

    static const auto shortOptions = std::move(([&]() -> std::map <std::string, char> && {
        std::map <std::string, char> ret;

        for (const auto & option: Parser::SHORT_OPTIONS) {
            ret.insert({option.second, option.first});
        }

        return std::move(ret);
    })());

    for (const auto & option: Parser::OPTIONS) {
        std::cout << "  " << option.first;

        auto it = shortOptions.find(option.first);
        if (it != shortOptions.end()) {
            std::cout << " (-" << it->second << ')';
        }

        if (!option.second.valueName.empty()) {
            std::cout << ' ';

            if (!option.second.requiresValue) {
                std::cout << '[';
            }

            std::cout << '<' << option.second.valueName << '>';

            if (!option.second.requiresValue) {
                std::cout << ']';
            }
        }

        std::cout << '\n';

        for (const std::string & line: option.second.description) {
            std::cout << "    " << line << "\n";
        }

        std::cout << '\n';
    }
}
*/
