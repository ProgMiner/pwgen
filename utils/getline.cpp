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

#include "getline.h"

#include <stdio.h>

#ifndef __linux
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>

int getch() {
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
#endif

std::string Utils::getLine(std::istream * cin, std::string && separators) {
    std::string ret;

    char c;
    do {
        c = cin->get();
        ret.push_back(c);
    } while (!cin->eof() && separators.find(c) == std::string::npos);

    ret.pop_back();

    return ret;
}

std::string Utils::getLine(std::istream * cin, const std::string & separators) {
    return Utils::getLine(cin, std::string(separators));
}

std::string Utils::getPassword(char replacementChar, std::string && separators) {
    bool replace = replacementChar != '\0';
    separators.push_back((char) 4);
    std::string ret;

    char c;
    do {
        c = getch();

        if (c == 8 || c == 127) {
            if (!ret.empty()) {
                ret.pop_back();

                if (replace) {
                    std::cout << "\b \b";
                }
            }
        } else {
            ret.push_back(c);

            if (replace && separators.find(c) == std::string::npos) {
                std::cout << replacementChar;
            }
        }
    } while (separators.find(c) == std::string::npos);

    ret.pop_back();

    return ret;
}

std::string Utils::getPassword(char replacementChar, const std::string & separators) {
    return Utils::getPassword(replacementChar, std::string(separators));
}
