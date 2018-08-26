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

#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <list>

#include "UI.h"

class CLI: public UI {

public:
    CLI() noexcept: UI() {}

    explicit CLI(const Core & core) noexcept:
        UI(core)
    {}

    void run() override;

protected:
    enum MenuItems {
        SET_MASTER_KEY,

        GENERATE,
        SET_PASSWORD_LENGTH,
        SET_PASSWORD_ALPHABET,

        REMIND,
        MAKE_REMINDER,

        QUIT
    };

    using ReadType = std::function <std::string(bool &)>;

    template <typename T>
    using ValidateType = std::function <T(const std::string &, bool &)>;

    class ReadFactory {

    public:
        ReadFactory(
                const std::string & prompt = "",
                const std::string & separators = "\n\r"
        ): prompt(prompt), separators(separators) {}

        ReadType line(std::istream * cin = & std::cin);

        ReadType password(char replacementChar = '*');

    protected:
        std::string prompt;
        std::string separators;
    };

    static const std::list <std::string> MENU_ITEMS;

    std::string input(const ReadType & read);

    template <typename T>
    T input(
            const ReadType & read,
            const ValidateType <T> & validate
    ) {
        T ret;

        bool retry = false;
        do {
            bool abort = false;
            std::string in = read(abort);

            if (abort) {
                // TODO
                throw false;
            }

            ret = validate(in, retry);
        } while (retry);

        return ret;
    }
};
