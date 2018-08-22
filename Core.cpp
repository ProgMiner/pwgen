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

#include "Core.h"

#include "utils/getline.h"
#include "utils/digest.h"
#include "utils/string.h"
#include "utils/shred.h"
#include "utils/xor.h"

std::string Core::makeMasterKeyHash(const std::string & key) {
    return Utils::doubleDigest(key);
}

void Core::setMasterKeyHash(const std::string & hash) noexcept {
    context.masterKeyHash = hash;
}

void Core::setMasterKey(const std::string & key) {
    context.masterKeyHash = makeMasterKeyHash(key);
}

std::string Core::generate(std::string && id) {
    id = Utils::doubleDigest(id) + context.masterKeyHash;
    id = Utils::doubleDigest(id);

    id = Utils::xorShorten(id, context.passwordLength);
    return Utils::stringGenerator(id, context.passwordAlphabet);
}

void Core::setPasswordLength(std::string::size_type length) noexcept {
    context.passwordLength = length;
}

void Core::setPasswordAlphabet(const std::string & alphabet) noexcept {
    context.passwordAlphabet = alphabet;
}
