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

#include "xor.h"

#include <cstring>
#include <algorithm>

char * Utils::xorCString(const char * a, const char * b, char * dst) {
    size_t length, xorLength,
           aLength = strlen(a),
           bLength = strlen(b);

    const char * longest;

    if (aLength < bLength) {
        length = bLength;
        xorLength = aLength;
        longest = b;
    } else {
        length = aLength;
        xorLength = bLength;
        longest = a;
    }

    for (size_t i = 0; i < xorLength; ++i) {
        dst[i] = a[i] ^ b[i];
    }

    for (size_t i = xorLength; i < length; ++i) {
        dst[i] = longest[i];
    }

    return dst;
}

void Utils::xorCStringWith(char * a, const char * b) {
    size_t length = strlen(a);

    for (size_t i = 0; i < length; ++i) {
        a[i] ^= b[i];
    }
}

std::string Utils::xorSTLString(std::string && a, std::string && b) {
    char ret[std::max(a.size(), b.size()) + 1];

    Utils::xorCString(a.c_str(), b.c_str(), ret);

    return std::string(ret);
}

std::string Utils::xorSTLString(const std::string & a, const std::string & b) {
    return Utils::xorSTLString(std::string(a), std::string(b));
}

void Utils::xorSTLStringWith(std::string & a, std::string && b) {
    std::string::size_type length = a.size();

    for (std::string::size_type i = 0; i < length; ++i) {
        a[i] ^= b[i];
    }
}

void Utils::xorSTLStringWith(std::string & a, const std::string & b) {
    return Utils::xorSTLStringWith(a, std::string(b));
}

std::string Utils::xorShorten(std::string && src, std::string::size_type newLength) {
    std::string::size_type length = src.size();
    std::string ret = src.substr(0, newLength);

    for (std::string::size_type offset = newLength; offset < length; offset += newLength) {
        Utils::xorSTLStringWith(ret, src.substr(offset, newLength));
    }

    return ret;
}

std::string Utils::xorShorten(const std::string & src, std::string::size_type newLength) {
    return Utils::xorShorten(std::string(src), newLength);
}
