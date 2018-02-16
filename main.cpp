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
#include <string>

#include "utils/digest.h"
#include "utils/getline.h"
#include "utils/string.h"
#include "utils/shred.h"
#include "utils/xor.h"

int main(int argc, char ** argv) {
    std::cout << "Master passphrase: ";
    std::string * masterKey = new std::string(Utils::getPassword());

    std::cout << '\n';

    std::string masterKeyHash = Utils::doubleDigest(* masterKey);

    if (!Utils::shred(masterKey, sizeof(* masterKey))) {
        std::cerr << "An error occured while removing master passphrase from RAM!\n";
    }

    std::cout << "Now you can generate someone passwords.\n"
                 "Send an End-Of-File for quit.\n";

    do {
        std::cout << "Password ID: ";
        std::string passwordId = Utils::doubleDigest(Utils::getLine());

        if (std::cin.eof()) {
            std::cout << '\n';
            break;
        }

        passwordId.append(masterKeyHash);
        passwordId = Utils::doubleDigest(std::move(passwordId));

        passwordId = Utils::xorShorten(std::move(passwordId), 24);
        std::cout << "Password: " << Utils::stringGenerator(passwordId) << '\n';
    } while (true);

    return 0;
}

