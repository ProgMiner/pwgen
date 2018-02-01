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
CFLAGS = -Wall -std=c++14 -g #-O2
LDFLAGS = -lcrypto

BUILDPATH = build
SOURCES = utils/digest.cpp utils/getline.cpp utils/shred.cpp utils/strgen.cpp utils/xor.cpp main.cpp
EXECUTABLE = $(BUILDPATH)/pwgen

OBJECTS = $(SOURCES:%.cpp=$(BUILDPATH)/%.o)

__all: __build

ifneq ($(OS), Windows_NT)

__clean:
	rm -rf $(BUILDPATH)

else

__clean:
	del /F $(BUILDPATH)

endif

__run:
	"$(BUILDPATH)/$(EXECUTABLE)" $(ARGS)

__build: $(EXECUTABLE)

$(BUILDPATH):
	mkdir $(BUILDPATH)

%.cpp:

$(BUILDPATH)/%.o: %.cpp $(BUILDPATH)
	mkdir -p `echo '$@' | grep -Eo '^(.*)/'`
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)
