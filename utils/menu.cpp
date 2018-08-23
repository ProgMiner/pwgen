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

#include "menu.h"

#include <exception>
#include <iostream>
#include <locale>
#include <map>

#include "utils/getline.h"

int Utils::menu(
        const std::list <std::string> & items,
        const std::string & prePrompt,
        const std::string & postPrompt
) {
    std::cout << prePrompt << '\n';

    std::map <char, int> chars;

    int j = 1;
    for (const std::string & item: items) {
        bool andSym = false;
        std::string result;

        if (item.find("# ") == 0) {
            result = std::string(item, 2);
#ifdef _WIN32
            std::cout << " _" << result << '_';
#else
            std::cout << " \e[1;4m " << result << " \e[0m";
#endif
            std::cout << '\n';
            continue;
        }

        for (char c: item) {
            if (c == '&') {
                if (andSym) {
                    result += '&';
                }

                andSym = !andSym;
                continue;
            }

            if (andSym) {
                chars.insert({c, j});

                char cLower = std::tolower(c);
                if (chars.find(cLower) == chars.end()) {
                    chars.insert({cLower, j});
                }
#ifdef _WIN32
                result += '_';
                result += c;
#else
                result += "\e[4m";
                result += c;
                result += "\e[24m";
#endif
                andSym = false;
            } else {
                result += c;
            }
        }

        if (!item.empty()) {
            std::cout << j << ". " << result;

            ++j;
        }

        std::cout << '\n';
    }

    int ret;
    do {
        std::cout << postPrompt;

        std::string in = getLine();

        ret = 0;
        if (in.size() == 1) {
            auto it = chars.find(in[0]);

            if (it != chars.end()) {
                ret = it->second;
            }
        }

        if (ret == 0) {
            try {
                ret = std::stoi(in);
            } catch (std::exception e) {}
        }

        if (items.empty()) {
            return ret - 1;
        }
    } while (ret <= 0 || ret >= j);

    return ret - 1;
}
