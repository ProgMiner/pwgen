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
#include <iostream>

#include "Exception.h"

const std::map <std::string, CLI::Parser::Option> CLI::Parser::OPTIONS = {
    {"--", CLI::Parser::Option({"Disables option parsing"}, "", false, [](CLI::Parser * parser, const std::string *) {
        parser->allowOptions = false;
    })},
    {"--help", CLI::Parser::Option({"Displays help and quit"}, "", false, [](CLI::Parser * parser, const std::string *) {
        std::cout << "Using:\n" <<
                     "  " << parser->arguments.front()() << " [<options>]";

        bool first = false;
        for (const Argument & argument: parser->arguments) {
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

        std::cout << "\n\n"
                     "Allowed options:\n\n";

        static const auto shortOptions = std::move(([&]() -> std::map <std::string, char> && {
            std::map <std::string, char> ret;

            for (const auto & option: SHORT_OPTIONS) {
                ret.insert({option.second, option.first});
            }

            return std::move(ret);
        })());

        for (const auto & option: OPTIONS) {
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
                std::cout << "    " << line << "\n\n";
            }
        }

        exit(0);
    })},
    {"--no-menu", CLI::Parser::Option({"Disables menu", "For no interactive using"}, "", false, [](CLI::Parser * parser, const std::string *) {
        parser->options.menu = false;
        return;
    })},
    {"--quite", CLI::Parser::Option({"Disables standart output", "For no interactive using"}, "", false, [](CLI::Parser * parser, const std::string *) {
        parser->options.quite = true;
        return;
    })},
    {"--verbose", CLI::Parser::Option({"Enables additional output"}, "", false, [](CLI::Parser * parser, const std::string *) {
        // parser->options.verbose = true;
        return;
    })}
};

const std::map <char, std::string> CLI::Parser::SHORT_OPTIONS = {
    {'h', "--help"},
    {'M', "--no-menu"},
    {'q', "--quite"},
    {'v', "--verbose"}
};

void CLI::Parser::parse(const std::list <std::string> & args) {
    for (const std::string & arg: args) {
        parseArgument(arg);
    }
}

void CLI::Parser::parseArgument(const std::string & arg) {
    try {
        if (arg[0] == '-' && allowOptions) {
            clearOptionsBuffer();

            if (arg[1] == '-') {
                    auto splitter = arg.find_first_of('=');

                    if (splitter != std::string::npos) {
                        auto value = new std::string(arg, splitter + 1);

                        OPTIONS.at(std::string(arg, 0, splitter))(this, value);

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

bool CLI::Parser::clearOptionsBuffer(const std::string * value) {
    for (std::string & option: optionsBuffer) {
        auto opt = OPTIONS.at(std::move(option));
        opt(this, value);

        if (!opt.valueName.empty()) {
            clearOptionsBuffer(nullptr);
            return true;
        }
    }

    optionsBuffer.clear();
    return false;
}
