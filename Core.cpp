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

Utils::SafeString Core::makeMasterKeyHash(Utils::SafeString && key) {
    return Utils::doubleDigest(key);
}

void Core::setMasterKeyHash(Utils::SafeString && hash) {
    context.masterKeyHash = std::move(hash);
}

void Core::setMasterKey(Utils::SafeString && hash) {
    context.masterKeyHash = makeMasterKeyHash(std::move(hash));
}

Utils::SafeString Core::generate(Utils::SafeString && id) {
    id = Utils::doubleDigest(std::move(id)) + context.masterKeyHash;
    id = Utils::doubleDigest(std::move(id));

    id = Utils::xorShorten(std::move(id), 24);
    return Utils::stringGenerator(id);
}
