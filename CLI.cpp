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

#include "utils/getline.h"
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
        std::cout << "Master passphrase: " << (core.getContext().isMasterKeyHashSet()? "set": "not set") << '\n';
        std::cout << "Password length:   " << core.getContext().getPasswordLength() << '\n';
        std::cout << "Password alphabet: " << core.getContext().getPasswordAlphabet() << '\n';
        std::cout << '\n';

        MenuItems action = static_cast <MenuItems> (
            Utils::menu(MENU_ITEMS)
        );

        switch (action) {
        case SET_MASTER_KEY:
            try {
                std::cout << "Master passphrase (" << (core.getContext().isMasterKeyHashSet()? "set": "not set") << "): ";

                core.setMasterKey(input(ReadFactory().password()));
                std::cout << "\n"
                             "Done.";
            } catch (bool e) {
                std::cout << "\n"
                             "Abort!";
            }
            break;

        case GENERATE:
            try {
                std::cout << "Password ID: ";

                auto passwordId = input(ReadFactory().line());
                std::cout << "Password: " << core.generate(std::move(passwordId)) << '\n';
            } catch (bool e) {
                std::cout << "\n"
                             "Abort!";
            }
            break;

        case SET_PASSWORD_LENGTH:
            try {
                auto prompt = "Password length (" + std::to_string(core.getContext().getPasswordLength()) + "): ";

                using T = std::string::size_type;
                core.setPasswordLength(input <T> (ReadFactory(prompt).line(), [=](const std::string & in, bool & retry) {
                    T ret = 0;

                    try {
                        long n = std::stol(in);

                        if (n <= 0) {
                            std::cout << "Password length cannot be lower or equal zero\n";
                            retry = true;
                        } else {
                            ret = n;
                            retry = false;
                        }
                    } catch (std::exception e) {
                        retry = true;
                    }

                    return ret;
                }));
                std::cout << "Done.";
            } catch (bool e) {
                std::cout << "\n"
                             "Abort!";
            }
            break;

        case SET_PASSWORD_ALPHABET:
            try {
                std::cout << "Password alphabet (" << core.getContext().getPasswordAlphabet() << "): ";

                core.setPasswordAlphabet(input(ReadFactory().line()));
                std::cout << "Done.";
            } catch (bool e) {
                std::cout << "\n"
                             "Abort!";
            }
            break;

        case REMIND:
        case MAKE_REMINDER:

        case QUIT:
            std::cout << "Bye!\n";
            return;
        }

        std::cout << "\n"
                     "Press Enter to continue...\n";
        Utils::getLine();
    }
}

std::string CLI::input(const CLI::ReadType & read) {
    bool abort = false;
    std::string ret = read(abort);

    if (abort) {
        // TODO
        throw false;
    }

    return ret;
}

CLI::ReadType CLI::ReadFactory::line(std::istream * cin) {
    return [=] (bool & abort) {
        std::cout << prompt;

        std::string ret = Utils::getLine(separators, cin);

        abort = cin->eof();
        return ret;
    };
}

CLI::ReadType CLI::ReadFactory::password(char replacementChar) {
    return [=] (bool & abort) {
        std::cout << prompt;

        return Utils::getPassword(
                abort,
                replacementChar,
                std::string(separators)
        );
    };
}
