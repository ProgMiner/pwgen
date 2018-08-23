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

#include <string>
#include <list>

#include "Core.h"

class Context {

public:
    Context() noexcept {}

    Context(const Context & context) noexcept:
        masterKeyHash   (context.masterKeyHash),
        passwordLength  (context.passwordLength),
        passwordAlphabet(context.passwordAlphabet)
    {}

    Context(Context && context) noexcept {
        std::swap(context.masterKeyHash,    masterKeyHash);
        std::swap(context.passwordLength,   passwordLength);
        std::swap(context.passwordAlphabet, passwordAlphabet);
    }

    Context & operator=(const Context & context) noexcept {
        masterKeyHash    = context.masterKeyHash;
        passwordLength   = context.passwordLength;
        passwordAlphabet = context.passwordAlphabet;

        return * this;
    }

    Context & operator=(Context && context) noexcept {
        std::swap(context.masterKeyHash,    masterKeyHash);
        std::swap(context.passwordLength,   passwordLength);
        std::swap(context.passwordAlphabet, passwordAlphabet);

        return * this;
    }

    inline bool isMasterKeyHashSet() const noexcept {
        return !masterKeyHash.empty();
    }

    inline std::string::size_type getPasswordLength() const noexcept {
        return passwordLength;
    }

    inline const std::string & getPasswordAlphabet() const noexcept {
        return passwordAlphabet;
    }

protected:
    std::string masterKeyHash;

    std::string::size_type passwordLength = 12;

    std::string passwordAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    friend class Core;
};
