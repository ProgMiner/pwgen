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

#include "utils/menu.h"

const std::list <std::string> CLI::MENU_ITEMS {
    "# Password generation",
    "  Set &master passphrase", // SET_MASTER_KEY
    "",
    "  &Generate password",     // GENERATE
    "  Set password &length",   // SET_PASSWORD_LENGTH
    "  Set password &alphabet", // SET_PASSWORD_ALPHABET
    "",
    "# Passphrase reminding",
    "  &Remind passphrase",     // REMIND
    "  Make reminder file",     // MAKE_REMINDER
    "",
    "&Quit"                     // QUIT
};

void CLI::run() {
    while (true) {
        MenuItems action = static_cast <MenuItems> (Utils::menu(MENU_ITEMS));

        switch (action) {
        case SET_MASTER_KEY:

        case GENERATE:
        case SET_PASSWORD_LENGTH:
        case SET_PASSWORD_ALPHABET:

        case REMIND:
        case MAKE_REMINDER:

        case QUIT:
            std::cout << "Bye!\n";
            return;
        }
    }
}
