# MIT License
#
# Copyright (c) 2018 Eridan Domoratskiy
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

CC = g++
CFLAGS = -Wall -std=c++14 -I. -g #-O2
LDFLAGS = -lboost_program_options

BUILDPATH = build
SOURCES = main.cpp \
		  utils/digest.cpp \
		  utils/string.cpp \
		  utils/xor.cpp \
		  utils/getline.cpp \
		  utils/shred.cpp \
		  utils/menu.cpp \
		  Core.cpp \
		  CLI.cpp \
		  SimpleUI.cpp \
		  Arguments.cpp
HEADERS = main.h \
		  utils/menu.h \
		  utils/digest.h \
		  utils/getline.h \
		  utils/xor.h \
		  utils/shred.h \
		  utils/string.h \
		  utils/SafeString.h \
		  SimpleUI.h \
		  Context.h \
		  CLI.h \
		  Exception.h \
		  UI.h \
		  Core.h \
		  Arguments.h \
		  Arguments.cpp.inc
TARGET = pwgen

OBJECTS = $(SOURCES:%.cpp=$(BUILDPATH)/%.o)

ifneq ($(OS), Windows_NT)
LDFLAGS += -lcrypto
else
CFLAGS += -IC:\OpenSSL-Win32\include
LDFLAGS += -LC:\OpenSSL-Win32\lib -llibeay32 -static-libgcc -static-libstdc++
endif

.PHONY: all build clean

all: build

clean:
ifneq ($(OS), Windows_NT)
	rm -rf $(BUILDPATH)
else
	del /F /S /Q $(BUILDPATH)
endif

build: $(TARGET)

%.cpp:

$(BUILDPATH)/%.o: %.cpp $(HEADERS)
ifneq ($(OS), Windows_NT)
	mkdir -p $(dir $@)
else
	if not exist "$(subst /,\,$(dir $@))" mkdir $(subst /,\,$(dir $@))
endif
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)
