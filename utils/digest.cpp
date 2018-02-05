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

#include "digest.h"

#include <openssl/evp.h>

bool Utils::digestLowlevel(const EVP_MD * digestType, const char * msg, size_t msgLen, unsigned char * dst, unsigned int * dstLen) {
    if (digestType == nullptr) {
        return false;
    }

    static EVP_MD_CTX * mdContext = EVP_MD_CTX_create();

    if (!EVP_DigestInit_ex(mdContext, digestType, nullptr)) return false;
    if (!EVP_DigestUpdate(mdContext, msg, msgLen)) return false;
    if (!EVP_DigestFinal_ex(mdContext, dst, dstLen)) return false;

    return true;
}

std::string Utils::digest(std::string && digestName, std::string && msg) {
    OpenSSL_add_all_digests();

    static const EVP_MD * digestType;
    digestType = EVP_get_digestbyname(digestName.c_str());

    if (digestType == nullptr) {
        throw false;
    }

    static unsigned char hash[EVP_MAX_MD_SIZE];
    static unsigned int hashLen;

    if (!Utils::digestLowlevel(digestType, msg.c_str(), msg.size(), hash, & hashLen)) {
        throw false;
    }

    return std::string((char *) hash, (std::string::size_type) hashLen);
}

std::string Utils::digest(
        const std::string & digestName,
        const std::string & msg
) {
    return Utils::digest(std::string(digestName), std::string(msg));
}

std::string Utils::doubleDigest(
        std::string && msg,
        std::pair <std::string, std::string> && digestNames
) {
    std::string _msg(msg);
    std::string ret(Utils::digest(digestNames.first, _msg));
    ret.append(Utils::digest(digestNames.second, std::move(_msg)));
    return ret;
}

std::string Utils::doubleDigest(
        const std::string & msg,
        const std::pair <std::string, std::string> & digestNames
) {
    return Utils::doubleDigest(
            std::string(msg),
            std::pair <std::string, std::string> (digestNames)
    );
}
