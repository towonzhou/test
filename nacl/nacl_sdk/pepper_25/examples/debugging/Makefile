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
VALID_TOOLCHAINS:=newlib
TOOLCHAIN?=newlib

DEBUGGING_CCFLAGS:=-fno-omit-frame-pointer


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

NEWLIB_CC?=$(TC_PATH)/$(OSNAME)_x86_newlib/bin/i686-nacl-gcc -c
NEWLIB_CXX?=$(TC_PATH)/$(OSNAME)_x86_newlib/bin/i686-nacl-g++ -c
NEWLIB_LINK?=$(TC_PATH)/$(OSNAME)_x86_newlib/bin/i686-nacl-g++ -Wl,-as-needed
NEWLIB_LIB?=$(TC_PATH)/$(OSNAME)_x86_newlib/bin/i686-nacl-ar r
NEWLIB_CCFLAGS?=-MMD -pthread $(NACL_WARNINGS) -idirafter $(NACL_SDK_ROOT)/include
NEWLIB_LDFLAGS?=-pthread

ARM_CC?=$(TC_PATH)/$(OSNAME)_arm_newlib/bin/arm-nacl-gcc -c
ARM_CXX?=$(TC_PATH)/$(OSNAME)_arm_newlib/bin/arm-nacl-g++ -c
ARM_LINK?=$(TC_PATH)/$(OSNAME)_arm_newlib/bin/arm-nacl-g++ -Wl,-as-needed
ARM_LIB?=$(TC_PATH)/$(OSNAME)_arm_newlib/bin/arm-nacl-ar r



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
DEBUGGING_OBJS:=hello_world string_stream untrusted_crash_dump

#
# Rules for newlib toolchain
#
newlib:
	$(MKDIR) newlib
newlib/Debug: | newlib
	$(MKDIR) newlib/Debug
newlib/Release: | newlib
	$(MKDIR) newlib/Release

# Include header dependency files.
-include newlib/Debug/*.d
-include newlib/Release/*.d

newlib/Debug/hello_world_x86_32.o : hello_world.c $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CC) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Debug/string_stream_x86_32.o : string_stream.c $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CC) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Debug/untrusted_crash_dump_x86_32.o : untrusted_crash_dump.c $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CC) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  


DEBUGGING_NEWLIB_DEBUG_x86_32_O:=$(patsubst %,newlib/Debug/%_x86_32.o,$(DEBUGGING_OBJS))
newlib/Debug/debugging_x86_32.nexe : $(DEBUGGING_NEWLIB_DEBUG_x86_32_O)
	$(NEWLIB_LINK) -o $@ $^ -g -m32 $(NEWLIB_LDFLAGS) $(DEBUGGING_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_32/Debug -Wl,--start-group -lppapi -lpthread -Wl,--end-group

newlib/Debug/hello_world_x86_64.o : hello_world.c $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CC) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Debug/string_stream_x86_64.o : string_stream.c $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CC) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Debug/untrusted_crash_dump_x86_64.o : untrusted_crash_dump.c $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CC) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  


DEBUGGING_NEWLIB_DEBUG_x86_64_O:=$(patsubst %,newlib/Debug/%_x86_64.o,$(DEBUGGING_OBJS))
newlib/Debug/debugging_x86_64.nexe : $(DEBUGGING_NEWLIB_DEBUG_x86_64_O)
	$(NEWLIB_LINK) -o $@ $^ -g -m64 $(NEWLIB_LDFLAGS) $(DEBUGGING_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_64/Debug -Wl,--start-group -lppapi -lpthread -Wl,--end-group

newlib/Debug/hello_world_arm.o : hello_world.c $(THIS_MAKE) | newlib/Debug
	$(ARM_CC) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Debug/string_stream_arm.o : string_stream.c $(THIS_MAKE) | newlib/Debug
	$(ARM_CC) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Debug/untrusted_crash_dump_arm.o : untrusted_crash_dump.c $(THIS_MAKE) | newlib/Debug
	$(ARM_CC) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  


DEBUGGING_NEWLIB_DEBUG_arm_O:=$(patsubst %,newlib/Debug/%_arm.o,$(DEBUGGING_OBJS))
newlib/Debug/debugging_arm.nexe : $(DEBUGGING_NEWLIB_DEBUG_arm_O)
	$(ARM_LINK) -o $@ $^ -g  $(NEWLIB_LDFLAGS) $(DEBUGGING_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_arm/Debug -Wl,--start-group -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=newlib/Debug/debugging.nmf
newlib/Debug/debugging.nmf : newlib/Debug/debugging_x86_32.nexe newlib/Debug/debugging_x86_64.nexe newlib/Debug/debugging_arm.nexe
	$(NMF) -o $@ $^ -s newlib/Debug

newlib/Release/hello_world_x86_32.o : hello_world.c $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CC) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Release/string_stream_x86_32.o : string_stream.c $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CC) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Release/untrusted_crash_dump_x86_32.o : untrusted_crash_dump.c $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CC) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  


DEBUGGING_NEWLIB_RELEASE_x86_32_O:=$(patsubst %,newlib/Release/%_x86_32.o,$(DEBUGGING_OBJS))
newlib/Release/debugging_x86_32.nexe : $(DEBUGGING_NEWLIB_RELEASE_x86_32_O)
	$(NEWLIB_LINK) -o $@ $^ -m32 $(NEWLIB_LDFLAGS) $(DEBUGGING_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_32/Release  -Wl,--start-group -lppapi -lpthread -Wl,--end-group

newlib/Release/hello_world_x86_64.o : hello_world.c $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CC) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Release/string_stream_x86_64.o : string_stream.c $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CC) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Release/untrusted_crash_dump_x86_64.o : untrusted_crash_dump.c $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CC) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  


DEBUGGING_NEWLIB_RELEASE_x86_64_O:=$(patsubst %,newlib/Release/%_x86_64.o,$(DEBUGGING_OBJS))
newlib/Release/debugging_x86_64.nexe : $(DEBUGGING_NEWLIB_RELEASE_x86_64_O)
	$(NEWLIB_LINK) -o $@ $^ -m64 $(NEWLIB_LDFLAGS) $(DEBUGGING_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_64/Release  -Wl,--start-group -lppapi -lpthread -Wl,--end-group

newlib/Release/hello_world_arm.o : hello_world.c $(THIS_MAKE) | newlib/Release
	$(ARM_CC) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Release/string_stream_arm.o : string_stream.c $(THIS_MAKE) | newlib/Release
	$(ARM_CC) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  

newlib/Release/untrusted_crash_dump_arm.o : untrusted_crash_dump.c $(THIS_MAKE) | newlib/Release
	$(ARM_CC) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(DEBUGGING_CCFLAGS)  


DEBUGGING_NEWLIB_RELEASE_arm_O:=$(patsubst %,newlib/Release/%_arm.o,$(DEBUGGING_OBJS))
newlib/Release/debugging_arm.nexe : $(DEBUGGING_NEWLIB_RELEASE_arm_O)
	$(ARM_LINK) -o $@ $^  $(NEWLIB_LDFLAGS) $(DEBUGGING_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_arm/Release  -Wl,--start-group -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=newlib/Release/debugging.nmf
newlib/Release/debugging.nmf : newlib/Release/debugging_x86_32.nexe newlib/Release/debugging_x86_64.nexe newlib/Release/debugging_arm.nexe
	$(NMF) -o $@ $^ -s newlib/Release

#
# Target to remove temporary files
#
.PHONY: clean
clean:
	$(RM) -fr newlib/Debug
	$(RM) -fr newlib/Release


all: $(ALL_TARGETS)



CHROME_ARGS+=--no-sandbox
CHROME_ENV:=NACL_DANGEROUS_ENABLE_FILE_ACCESS=1
CHROME_ENV+=NACL_SECURITY_DISABLE=1
CHROME_ENV+=NACL_UNTRUSTED_EXCEPTION_HANDLING=1


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


