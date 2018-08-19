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

#include <iostream>
#include <string>

#include "utils/shred.h"

namespace Utils {

    class SafeString: public std::string {

    public:
        SafeString()
            noexcept(std::is_nothrow_default_constructible <allocator_type> ::value)
        : std::string() {}

        explicit SafeString(const allocator_type & a): std::string(a) {}

        SafeString(const std::string & str): std::string(str) {}
        SafeString(std::string && str)
            noexcept(std::is_nothrow_move_constructible <allocator_type> ::value)
        : std::string(str) {}

        SafeString(
                const std::string & str,
                size_type pos,
                const allocator_type & a = allocator_type()
        ): std::string(str, pos, a) {}

        SafeString(
                const std::string & str,
                size_type pos,
                size_type n,
                const std::allocator <char> & a = std::allocator <char> ()
        ): std::string(str, pos, n, a) {}

        template <class T>
        SafeString(
                const T & t,
                size_type pos,
                size_type n,
                const std::allocator <char> & a = std::allocator <char> ()
        ): std::string(t, pos, n, a) {} // C++17

        explicit SafeString(
                const std::basic_string_view <char, std::char_traits <char> > sv,
                const std::allocator <char> & a = std::allocator <char> ()
        ): std::string(sv, a) {}

        SafeString(
                const value_type * s,
                const allocator_type & a = allocator_type()
        ): std::string(s, a) {}
        SafeString(
                const value_type * s,
                size_type n,
                const allocator_type & a = allocator_type()
        ): std::string(s, n, a) {}
        SafeString(
                size_type n,
                value_type c,
                const allocator_type & a = allocator_type()
        ): std::string(n, c, a) {}

        template <class InputIterator>
        SafeString(
                InputIterator begin,
                InputIterator end,
                const allocator_type & a = allocator_type()
        ): std::string(begin, end, a) {}

        SafeString(
                std::initializer_list <value_type> il,
                const std::allocator <char> & a = std::allocator <char>()
        ): std::string(il, a) {}

        SafeString(const std::string & s, const std::allocator <char> & a):
            std::string(s, a)
        {}
        SafeString(std::string && s, const std::allocator <char> & a):
            std::string(s, a)
        {}

        inline ~SafeString() {
            if (!Utils::shred(const_cast <char *> (c_str()), size())) {
                std::cerr << "Warning: An error occured while removing master passphrase from RAM!\n";
            }
        }
    };

}
