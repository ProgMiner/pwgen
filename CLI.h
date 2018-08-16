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
#include <string>
#include <list>
#include <map>

#include "Context.h"

class CLI {

public:
    class Options {

    public:
        bool menu  = true;
        bool quite = false;
    } options;

    class Parser {

    public:
        bool allowOptions = true;

        Parser(Options & options): options(options) {}

        void parse(const std::list <std::string> & args);
        void parseArgument(const std::string & arg);

    protected:
        class Option {

        public:
            typedef std::function <void(CLI::Parser *, const std::string *)> actionType;

            std::list <std::string> description;
            std::string valueName;
            bool requiresValue;

            actionType action;

            Option(
                    std::list <std::string> && description,
                    std::string && valueName,
                    bool requiresValue,
                    actionType && action
            ):
                description(std::move(description)),
                valueName(std::move(valueName)),
                requiresValue(requiresValue),
                action(std::move(action))
            {}

            Option(const Option & opt):
                description(opt.description),
                valueName(std::move(opt.valueName)),
                requiresValue(opt.requiresValue),
                action(opt.action)
            {}
            Option(Option && opt):
                description(std::move(opt.description)),
                valueName(std::move(opt.valueName)),
                requiresValue(opt.requiresValue),
                action(std::move(opt.action))
            {}

            void operator()(CLI::Parser * parser, const std::string * arg) const {
                action(parser, arg);
            }
        };

        static const std::map <std::string, Option> OPTIONS;
        static const std::map <char, std::string> SHORT_OPTIONS;

        std::list <std::string> optionsBuffer;

        Options & options;

        bool clearOptionsBuffer(const std::string * arg = nullptr);
    } parser = Parser(options);

    CLI();

    void run(const std::list <std::string> & args);
};
