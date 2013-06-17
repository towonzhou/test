# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

#
# GNU Make based build file.  For details on GNU Make see:
#   http://www.gnu.org/software/make/manual/make.html
#

#
# Get pepper directory for toolchain and includes.
#
# If NACL_SDK_ROOT is not set, then assume it can be found a two directories up,
# from the default example directory location.
#
THIS_MAKEFILE:=$(abspath $(lastword $(MAKEFILE_LIST)))
THIS_DIR:=$(abspath $(dir $(THIS_MAKEFILE)))
NACL_SDK_ROOT?=$(abspath $(dir $(THIS_MAKEFILE))../..)
CHROME_PATH?=Undefined

#
# Defaults
#
NACL_WARNINGS:=-Wno-long-long -Wall -Wswitch-enum -Werror -pedantic

#
# Project Settings
#
VALID_TOOLCHAINS:=glibc
TOOLCHAIN?=glibc

LIBEIGHTBALL_CXXFLAGS:=-fPIC


#
# Default target
#
all:

#
# Alias for standard commands
#
CP:=python $(NACL_SDK_ROOT)/tools/oshelpers.py cp
MKDIR:=python $(NACL_SDK_ROOT)/tools/oshelpers.py mkdir
MV:=python $(NACL_SDK_ROOT)/tools/oshelpers.py mv
RM:=python $(NACL_SDK_ROOT)/tools/oshelpers.py rm


#
# Verify we selected a valid toolchain for this example
#
ifeq (,$(findstring $(TOOLCHAIN),$(VALID_TOOLCHAINS)))
$(warning Availbile choices are: $(VALID_TOOLCHAINS))
$(error Can not use TOOLCHAIN=$(TOOLCHAIN) on this example.)
endif


#
# Compute path to requested NaCl Toolchain
#
OSNAME:=$(shell python $(NACL_SDK_ROOT)/tools/getos.py)
TC_PATH:=$(abspath $(NACL_SDK_ROOT)/toolchain)


#
# Verify we have a valid NACL_SDK_ROOT by looking for the toolchain directory
#
ifeq (,$(wildcard $(TC_PATH)))
$(warning No valid NACL_SDK_ROOT at $(NACL_SDK_ROOT))
ifeq ($(origin NACL_SDK_ROOT), 'file')
$(error Override the default value via enviornment variable, or command-line.)
else
$(error Fix the NACL_SDK_ROOT specified in the environment or command-line.)
endif
endif


#
# Disable DOS PATH warning when using Cygwin based NaCl tools on Windows
#
CYGWIN ?= nodosfilewarning
export CYGWIN


#
# Defaults for TOOLS
#

GLIBC_CC?=$(TC_PATH)/$(OSNAME)_x86_glibc/bin/i686-nacl-gcc -c
GLIBC_CXX?=$(TC_PATH)/$(OSNAME)_x86_glibc/bin/i686-nacl-g++ -c
GLIBC_LINK?=$(TC_PATH)/$(OSNAME)_x86_glibc/bin/i686-nacl-g++ -Wl,-as-needed
GLIBC_LIB?=$(TC_PATH)/$(OSNAME)_x86_glibc/bin/i686-nacl-ar r
GLIBC_DUMP?=$(TC_PATH)/$(OSNAME)_x86_glibc/x86_64-nacl/bin/objdump
GLIBC_PATHS:=-L $(TC_PATH)/$(OSNAME)_x86_glibc/x86_64-nacl/lib32
GLIBC_PATHS+=-L $(TC_PATH)/$(OSNAME)_x86_glibc/x86_64-nacl/lib
GLIBC_CCFLAGS?=-MMD -pthread $(NACL_WARNINGS) -idirafter $(NACL_SDK_ROOT)/include
GLIBC_LDFLAGS?=-pthread



#
# NMF Manifiest generation
#
# Use the python script create_nmf to scan the binaries for dependencies using
# objdump.  Pass in the (-L) paths to the default library toolchains so that we
# can find those libraries and have it automatically copy the files (-s) to
# the target directory for us.
NMF:=python $(NACL_SDK_ROOT)/tools/create_nmf.py


#
# Verify we can find the Chrome executable if we need to launch it.
#
.PHONY: CHECK_FOR_CHROME RUN LAUNCH
CHECK_FOR_CHROME:
ifeq (,$(wildcard $(CHROME_PATH)))
	$(warning No valid Chrome found at CHROME_PATH=$(CHROME_PATH))
	$(error Set CHROME_PATH via an environment variable, or command-line.)
else
	$(warning Using chrome at: $(CHROME_PATH))
endif

#
# Per target object lists
#
DLOPEN_OBJS:=dlopen
LIBEIGHTBALL_OBJS:=eightball
GLIBC_REMAP:=-n libeightball_x86_32.so,libeightball.so
GLIBC_REMAP+=-n libeightball_x86_64.so,libeightball.so

#
# Rules for glibc toolchain
#
glibc:
	$(MKDIR) glibc
glibc/Debug: | glibc
	$(MKDIR) glibc/Debug
glibc/Release: | glibc
	$(MKDIR) glibc/Release

# Include header dependency files.
-include glibc/Debug/*.d
-include glibc/Release/*.d

glibc/Debug/dlopen_x86_32.o : dlopen.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(DLOPEN_CXXFLAGS)  


DLOPEN_GLIBC_DEBUG_x86_32_O:=$(patsubst %,glibc/Debug/%_x86_32.o,$(DLOPEN_OBJS))
glibc/Debug/dlopen_x86_32.nexe : $(DLOPEN_GLIBC_DEBUG_x86_32_O)
	$(GLIBC_LINK) -o $@ $^ -g -m32 $(GLIBC_LDFLAGS) $(DLOPEN_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_32/Debug -Wl,--start-group -ldl -lppapi_cpp -lppapi -lpthread -Wl,--end-group

glibc/Debug/dlopen_x86_64.o : dlopen.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(DLOPEN_CXXFLAGS)  


DLOPEN_GLIBC_DEBUG_x86_64_O:=$(patsubst %,glibc/Debug/%_x86_64.o,$(DLOPEN_OBJS))
glibc/Debug/dlopen_x86_64.nexe : $(DLOPEN_GLIBC_DEBUG_x86_64_O)
	$(GLIBC_LINK) -o $@ $^ -g -m64 $(GLIBC_LDFLAGS) $(DLOPEN_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_64/Debug -Wl,--start-group -ldl -lppapi_cpp -lppapi -lpthread -Wl,--end-group

glibc/Debug/eightball_x86_32.o : eightball.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(LIBEIGHTBALL_CXXFLAGS)  


LIBEIGHTBALL_GLIBC_DEBUG_x86_32_O:=$(patsubst %,glibc/Debug/%_x86_32.o,$(LIBEIGHTBALL_OBJS))
glibc/Debug/libeightball_x86_32.so : $(LIBEIGHTBALL_GLIBC_DEBUG_x86_32_O)
	$(GLIBC_LINK) -o $@ $^ -g -m32 -shared $(LIBEIGHTBALL_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_32/Debug

glibc/Debug/eightball_x86_64.o : eightball.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(LIBEIGHTBALL_CXXFLAGS)  


LIBEIGHTBALL_GLIBC_DEBUG_x86_64_O:=$(patsubst %,glibc/Debug/%_x86_64.o,$(LIBEIGHTBALL_OBJS))
glibc/Debug/libeightball_x86_64.so : $(LIBEIGHTBALL_GLIBC_DEBUG_x86_64_O)
	$(GLIBC_LINK) -o $@ $^ -g -m64 -shared $(LIBEIGHTBALL_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_64/Debug


ALL_TARGETS+=glibc/Debug/dlopen.nmf
glibc/Debug/dlopen.nmf : glibc/Debug/libeightball_x86_32.so glibc/Debug/dlopen_x86_32.nexe glibc/Debug/libeightball_x86_64.so glibc/Debug/dlopen_x86_64.nexe
	$(NMF) -D $(GLIBC_DUMP) -o $@ $(GLIBC_PATHS) $^ -s glibc/Debug $(GLIBC_REMAP)

glibc/Release/dlopen_x86_32.o : dlopen.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(DLOPEN_CXXFLAGS)  


DLOPEN_GLIBC_RELEASE_x86_32_O:=$(patsubst %,glibc/Release/%_x86_32.o,$(DLOPEN_OBJS))
glibc/Release/dlopen_x86_32.nexe : $(DLOPEN_GLIBC_RELEASE_x86_32_O)
	$(GLIBC_LINK) -o $@ $^ -m32 $(GLIBC_LDFLAGS) $(DLOPEN_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_32/Release  -Wl,--start-group -ldl -lppapi_cpp -lppapi -lpthread -Wl,--end-group

glibc/Release/dlopen_x86_64.o : dlopen.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(DLOPEN_CXXFLAGS)  


DLOPEN_GLIBC_RELEASE_x86_64_O:=$(patsubst %,glibc/Release/%_x86_64.o,$(DLOPEN_OBJS))
glibc/Release/dlopen_x86_64.nexe : $(DLOPEN_GLIBC_RELEASE_x86_64_O)
	$(GLIBC_LINK) -o $@ $^ -m64 $(GLIBC_LDFLAGS) $(DLOPEN_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_64/Release  -Wl,--start-group -ldl -lppapi_cpp -lppapi -lpthread -Wl,--end-group

glibc/Release/eightball_x86_32.o : eightball.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(LIBEIGHTBALL_CXXFLAGS)  


LIBEIGHTBALL_GLIBC_RELEASE_x86_32_O:=$(patsubst %,glibc/Release/%_x86_32.o,$(LIBEIGHTBALL_OBJS))
glibc/Release/libeightball_x86_32.so : $(LIBEIGHTBALL_GLIBC_RELEASE_x86_32_O)
	$(GLIBC_LINK) -o $@ $^ -m32 -shared $(LIBEIGHTBALL_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_32/Release

glibc/Release/eightball_x86_64.o : eightball.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(LIBEIGHTBALL_CXXFLAGS)  


LIBEIGHTBALL_GLIBC_RELEASE_x86_64_O:=$(patsubst %,glibc/Release/%_x86_64.o,$(LIBEIGHTBALL_OBJS))
glibc/Release/libeightball_x86_64.so : $(LIBEIGHTBALL_GLIBC_RELEASE_x86_64_O)
	$(GLIBC_LINK) -o $@ $^ -m64 -shared $(LIBEIGHTBALL_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_64/Release


ALL_TARGETS+=glibc/Release/dlopen.nmf
glibc/Release/dlopen.nmf : glibc/Release/libeightball_x86_32.so glibc/Release/dlopen_x86_32.nexe glibc/Release/libeightball_x86_64.so glibc/Release/dlopen_x86_64.nexe
	$(NMF) -D $(GLIBC_DUMP) -o $@ $(GLIBC_PATHS) $^ -s glibc/Release $(GLIBC_REMAP)

#
# Target to remove temporary files
#
.PHONY: clean
clean:
	$(RM) -fr glibc/Debug
	$(RM) -fr glibc/Release


all: $(ALL_TARGETS)




#
# Variables for running examples with Chrome.
#
RUN_PY:=python $(NACL_SDK_ROOT)/tools/run.py

# Add this to launch Chrome with additional environment variables defined.
# Each element should be specified as KEY=VALUE, with whitespace separating
# key-value pairs. e.g.
# CHROME_ENV=FOO=1 BAR=2 BAZ=3
CHROME_ENV?=

# Additional arguments to pass to Chrome.
CHROME_ARGS+=--enable-nacl --incognito


CONFIG?=Debug
PAGE?=index_$(TOOLCHAIN)_$(CONFIG).html

RUN: LAUNCH
LAUNCH: CHECK_FOR_CHROME all
ifeq (,$(wildcard $(PAGE)))
	$(warning No valid HTML page found at $(PAGE))
	$(error Make sure TOOLCHAIN and CONFIG are properly set)
endif
	$(RUN_PY) -C $(THIS_DIR) -P $(PAGE) $(addprefix -E ,$(CHROME_ENV)) -- \
	    $(CHROME_PATH) $(CHROME_ARGS) \
	    --register-pepper-plugins="$(PPAPI_DEBUG),$(PPAPI_RELEASE)"


