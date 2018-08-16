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

#include <stdexcept>

#include "Exception.h"

const std::map <std::string, std::function <bool(const std::string *)> > CLI::Parser::OPTIONS = {
    {"--", [](const std::string *) { return false; }}
};

const std::map <char, std::string> CLI::Parser::SHORT_OPTIONS = {
};

void CLI::Parser::parse(const std::list <std::string> & args) {
    for (const std::string & arg: args) {
        parseArgument(arg);
    }
}

void CLI::Parser::parseArgument(const std::string & arg) {
    try {
        if (arg[0] == '-') {
            clearOptionsBuffer();

            if (arg[1] == '-') {
                    auto splitter = arg.find_first_of("= ");
                    if (splitter != std::string::npos) {
                        auto value = new std::string(arg, splitter + 1);
                        OPTIONS.at(std::string(arg, 0, splitter))(value);
                        delete value;
                    } else {
                        optionsBuffer.push_back(arg);
                    }
            } else {
                const char * option = arg.c_str();

                while (* ++option) {
                    try {
                        optionsBuffer.push_back(SHORT_OPTIONS.at(* option));
                    } catch (std::out_of_range e) {
                        throw Exception(std::string("Undefined option -") + * option, e);
                    }
                }
            }

            return;
        }

        if (clearOptionsBuffer(& arg)) {
            return;
        }
    } catch (std::out_of_range e) {
        throw Exception("Undefined option " + arg, e);
    }

    // Arguments
}

bool CLI::Parser::clearOptionsBuffer(const std::string * arg) {
    for (std::string & option: optionsBuffer) {
        if (OPTIONS.at(std::move(option))(arg)) {
            clearOptionsBuffer(nullptr);
            return true;
        }
    }

    optionsBuffer.clear();
    return false;
}
