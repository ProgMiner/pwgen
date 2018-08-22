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

#include <iostream>

#include "Arguments.h"
#include "SimpleUI.h"
#include "CLI.h"
#include "UI.h"

void printHelp(const std::string & path, const Arguments & args) {
    std::cout << "Using:\n" <<
                 "  " << path << " [<options>]\n\n";

    std::cout << args.getOptionsDescription();
}

int main(int argc, char ** argv) {
    Arguments args;
    args.parse(argc, argv);

    if (args.find("help") != args.end()) {
        printHelp(argv[0], args);
        return 0;
    }

    UI * ui = nullptr;

    Core core;
    core.setPasswordLength(args["length"].as <std::string::size_type> ());
    core.setPasswordAlphabet(args["alphabet"].as <std::string> ());

    if (args.find("simple-mode") != args.end()) {
        ui = new SimpleUI(std::move(core));
    } else {
        ui = new CLI(std::move(core));
    }

    ui->quiet = args.find("quiet") != args.end();

    ui->run();
    return 0;
}
