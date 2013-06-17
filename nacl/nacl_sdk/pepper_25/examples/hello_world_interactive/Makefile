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
VALID_TOOLCHAINS:=newlib glibc linux pnacl
TOOLCHAIN?=newlib



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

GLIBC_CC?=$(TC_PATH)/$(OSNAME)_x86_glibc/bin/i686-nacl-gcc -c
GLIBC_CXX?=$(TC_PATH)/$(OSNAME)_x86_glibc/bin/i686-nacl-g++ -c
GLIBC_LINK?=$(TC_PATH)/$(OSNAME)_x86_glibc/bin/i686-nacl-g++ -Wl,-as-needed
GLIBC_LIB?=$(TC_PATH)/$(OSNAME)_x86_glibc/bin/i686-nacl-ar r
GLIBC_DUMP?=$(TC_PATH)/$(OSNAME)_x86_glibc/x86_64-nacl/bin/objdump
GLIBC_PATHS:=-L $(TC_PATH)/$(OSNAME)_x86_glibc/x86_64-nacl/lib32
GLIBC_PATHS+=-L $(TC_PATH)/$(OSNAME)_x86_glibc/x86_64-nacl/lib
GLIBC_CCFLAGS?=-MMD -pthread $(NACL_WARNINGS) -idirafter $(NACL_SDK_ROOT)/include
GLIBC_LDFLAGS?=-pthread

LINUX_WARNINGS?=-Wno-long-long
LINUX_CC?=gcc -c
LINUX_CXX?=g++ -c
LINUX_LINK?=g++
LINUX_LIB?=ar r
LINUX_CCFLAGS=-MMD -pthread $(LINUX_WARNINGS) -I$(NACL_SDK_ROOT)/include -I$(NACL_SDK_ROOT)/include/linux

PNACL_CC?=$(TC_PATH)/$(OSNAME)_x86_pnacl/newlib/bin/pnacl-clang -c
PNACL_CXX?=$(TC_PATH)/$(OSNAME)_x86_pnacl/newlib/bin/pnacl-clang++ -c
PNACL_LINK?=$(TC_PATH)/$(OSNAME)_x86_pnacl/newlib/bin/pnacl-clang++
PNACL_LIB?=$(TC_PATH)/$(OSNAME)_x86_pnacl/newlib/bin/pnacl-ar r
PNACL_CCFLAGS?=-MMD -pthread $(NACL_WARNINGS) -idirafter $(NACL_SDK_ROOT)/include
PNACL_LDFLAGS?=-pthread
TRANSLATE:=$(TC_PATH)/$(OSNAME)_x86_pnacl/newlib/bin/pnacl-translate



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
HELLO_WORLD_INTERACTIVE_OBJS:=hello_world helper_functions

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

newlib/Debug/hello_world_x86_32.o : hello_world.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

newlib/Debug/helper_functions_x86_32.o : helper_functions.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_NEWLIB_DEBUG_x86_32_O:=$(patsubst %,newlib/Debug/%_x86_32.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
newlib/Debug/hello_world_interactive_x86_32.nexe : $(HELLO_WORLD_INTERACTIVE_NEWLIB_DEBUG_x86_32_O)
	$(NEWLIB_LINK) -o $@ $^ -g -m32 $(NEWLIB_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_32/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

newlib/Debug/hello_world_x86_64.o : hello_world.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

newlib/Debug/helper_functions_x86_64.o : helper_functions.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_NEWLIB_DEBUG_x86_64_O:=$(patsubst %,newlib/Debug/%_x86_64.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
newlib/Debug/hello_world_interactive_x86_64.nexe : $(HELLO_WORLD_INTERACTIVE_NEWLIB_DEBUG_x86_64_O)
	$(NEWLIB_LINK) -o $@ $^ -g -m64 $(NEWLIB_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_64/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

newlib/Debug/hello_world_arm.o : hello_world.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

newlib/Debug/helper_functions_arm.o : helper_functions.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_NEWLIB_DEBUG_arm_O:=$(patsubst %,newlib/Debug/%_arm.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
newlib/Debug/hello_world_interactive_arm.nexe : $(HELLO_WORLD_INTERACTIVE_NEWLIB_DEBUG_arm_O)
	$(ARM_LINK) -o $@ $^ -g  $(NEWLIB_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_arm/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=newlib/Debug/hello_world_interactive.nmf
newlib/Debug/hello_world_interactive.nmf : newlib/Debug/hello_world_interactive_x86_32.nexe newlib/Debug/hello_world_interactive_x86_64.nexe newlib/Debug/hello_world_interactive_arm.nexe
	$(NMF) -o $@ $^ -s newlib/Debug

newlib/Release/hello_world_x86_32.o : hello_world.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

newlib/Release/helper_functions_x86_32.o : helper_functions.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_NEWLIB_RELEASE_x86_32_O:=$(patsubst %,newlib/Release/%_x86_32.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
newlib/Release/hello_world_interactive_x86_32.nexe : $(HELLO_WORLD_INTERACTIVE_NEWLIB_RELEASE_x86_32_O)
	$(NEWLIB_LINK) -o $@ $^ -m32 $(NEWLIB_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_32/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

newlib/Release/hello_world_x86_64.o : hello_world.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

newlib/Release/helper_functions_x86_64.o : helper_functions.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_NEWLIB_RELEASE_x86_64_O:=$(patsubst %,newlib/Release/%_x86_64.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
newlib/Release/hello_world_interactive_x86_64.nexe : $(HELLO_WORLD_INTERACTIVE_NEWLIB_RELEASE_x86_64_O)
	$(NEWLIB_LINK) -o $@ $^ -m64 $(NEWLIB_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_64/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

newlib/Release/hello_world_arm.o : hello_world.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

newlib/Release/helper_functions_arm.o : helper_functions.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_NEWLIB_RELEASE_arm_O:=$(patsubst %,newlib/Release/%_arm.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
newlib/Release/hello_world_interactive_arm.nexe : $(HELLO_WORLD_INTERACTIVE_NEWLIB_RELEASE_arm_O)
	$(ARM_LINK) -o $@ $^  $(NEWLIB_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_arm/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=newlib/Release/hello_world_interactive.nmf
newlib/Release/hello_world_interactive.nmf : newlib/Release/hello_world_interactive_x86_32.nexe newlib/Release/hello_world_interactive_x86_64.nexe newlib/Release/hello_world_interactive_arm.nexe
	$(NMF) -o $@ $^ -s newlib/Release


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

glibc/Debug/hello_world_x86_32.o : hello_world.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

glibc/Debug/helper_functions_x86_32.o : helper_functions.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_GLIBC_DEBUG_x86_32_O:=$(patsubst %,glibc/Debug/%_x86_32.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
glibc/Debug/hello_world_interactive_x86_32.nexe : $(HELLO_WORLD_INTERACTIVE_GLIBC_DEBUG_x86_32_O)
	$(GLIBC_LINK) -o $@ $^ -g -m32 $(GLIBC_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_32/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

glibc/Debug/hello_world_x86_64.o : hello_world.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

glibc/Debug/helper_functions_x86_64.o : helper_functions.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_GLIBC_DEBUG_x86_64_O:=$(patsubst %,glibc/Debug/%_x86_64.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
glibc/Debug/hello_world_interactive_x86_64.nexe : $(HELLO_WORLD_INTERACTIVE_GLIBC_DEBUG_x86_64_O)
	$(GLIBC_LINK) -o $@ $^ -g -m64 $(GLIBC_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_64/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=glibc/Debug/hello_world_interactive.nmf
glibc/Debug/hello_world_interactive.nmf : glibc/Debug/hello_world_interactive_x86_32.nexe glibc/Debug/hello_world_interactive_x86_64.nexe
	$(NMF) -D $(GLIBC_DUMP) -o $@ $(GLIBC_PATHS) $^ -s glibc/Debug $(GLIBC_REMAP)

glibc/Release/hello_world_x86_32.o : hello_world.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

glibc/Release/helper_functions_x86_32.o : helper_functions.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_GLIBC_RELEASE_x86_32_O:=$(patsubst %,glibc/Release/%_x86_32.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
glibc/Release/hello_world_interactive_x86_32.nexe : $(HELLO_WORLD_INTERACTIVE_GLIBC_RELEASE_x86_32_O)
	$(GLIBC_LINK) -o $@ $^ -m32 $(GLIBC_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_32/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

glibc/Release/hello_world_x86_64.o : hello_world.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

glibc/Release/helper_functions_x86_64.o : helper_functions.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_GLIBC_RELEASE_x86_64_O:=$(patsubst %,glibc/Release/%_x86_64.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
glibc/Release/hello_world_interactive_x86_64.nexe : $(HELLO_WORLD_INTERACTIVE_GLIBC_RELEASE_x86_64_O)
	$(GLIBC_LINK) -o $@ $^ -m64 $(GLIBC_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_64/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=glibc/Release/hello_world_interactive.nmf
glibc/Release/hello_world_interactive.nmf : glibc/Release/hello_world_interactive_x86_32.nexe glibc/Release/hello_world_interactive_x86_64.nexe
	$(NMF) -D $(GLIBC_DUMP) -o $@ $(GLIBC_PATHS) $^ -s glibc/Release $(GLIBC_REMAP)


#
# Rules for linux toolchain
#
linux:
	$(MKDIR) linux
linux/Debug: | linux
	$(MKDIR) linux/Debug
linux/Release: | linux
	$(MKDIR) linux/Release

# Include header dependency files.
-include linux/Debug/*.d
-include linux/Release/*.d

PPAPI_DEBUG:=$(abspath linux/Debug/libhello_world_interactive.so);application/x-ppapi-debug
linux/Debug/hello_world_.o : hello_world.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

linux/Debug/helper_functions_.o : helper_functions.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_LINUX_DEBUG__O:=$(patsubst %,linux/Debug/%_.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
linux/Debug/libhello_world_interactive.so : $(HELLO_WORLD_INTERACTIVE_LINUX_DEBUG__O)
	$(LINUX_LINK) -o $@ $^ -g  -shared $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/$(OSNAME)_host/Debug -Wl,--whole-archive -lppapi_cpp -lppapi -lpthread -Wl,--no-whole-archive


ALL_TARGETS+=linux/Debug/hello_world_interactive.nmf
linux/Debug/hello_world_interactive.nmf : linux/Debug/libhello_world_interactive.so | linux/Debug
	echo {} > $@

PPAPI_RELEASE:=$(abspath linux/Release/libhello_world_interactive.so);application/x-ppapi-release
linux/Release/hello_world_.o : hello_world.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

linux/Release/helper_functions_.o : helper_functions.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_LINUX_RELEASE__O:=$(patsubst %,linux/Release/%_.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
linux/Release/libhello_world_interactive.so : $(HELLO_WORLD_INTERACTIVE_LINUX_RELEASE__O)
	$(LINUX_LINK) -o $@ $^  -shared $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/$(OSNAME)_host/Release -Wl,--whole-archive -lppapi_cpp -lppapi -lpthread -Wl,--no-whole-archive


ALL_TARGETS+=linux/Release/hello_world_interactive.nmf
linux/Release/hello_world_interactive.nmf : linux/Release/libhello_world_interactive.so | linux/Release
	echo {} > $@


#
# Rules for pnacl toolchain
#
pnacl:
	$(MKDIR) pnacl
pnacl/Debug: | pnacl
	$(MKDIR) pnacl/Debug
pnacl/Release: | pnacl
	$(MKDIR) pnacl/Release

# Include header dependency files.
-include pnacl/Debug/*.d
-include pnacl/Release/*.d

pnacl/Debug/hello_world.o : hello_world.cc $(THIS_MAKE) | pnacl/Debug
	$(PNACL_CXX) -o $@ $< -g -O0  $(PNACL_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

pnacl/Debug/helper_functions.o : helper_functions.cc $(THIS_MAKE) | pnacl/Debug
	$(PNACL_CXX) -o $@ $< -g -O0  $(PNACL_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_PNACL_DEBUG_O:=$(patsubst %,pnacl/Debug/%.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
pnacl/Debug/hello_world_interactive.pexe : $(HELLO_WORLD_INTERACTIVE_PNACL_DEBUG_O)
	$(PNACL_LINK) -o $@ $^ -g $(PNACL_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/pnacl/Debug -lppapi_cpp -lppapi -lpthread

pnacl/Debug/hello_world_interactive_x86_32.nexe : pnacl/Debug/hello_world_interactive.pexe
	$(TRANSLATE) -arch x86-32 $< -o $@

pnacl/Debug/hello_world_interactive_x86_64.nexe : pnacl/Debug/hello_world_interactive.pexe
	$(TRANSLATE) -arch x86-64 $< -o $@

pnacl/Debug/hello_world_interactive_arm.nexe : pnacl/Debug/hello_world_interactive.pexe
	$(TRANSLATE) -arch arm $< -o $@


ALL_TARGETS+=pnacl/Debug/hello_world_interactive.nmf
pnacl/Debug/hello_world_interactive.nmf : pnacl/Debug/hello_world_interactive_x86_32.nexe pnacl/Debug/hello_world_interactive_x86_64.nexe pnacl/Debug/hello_world_interactive_arm.nexe
	$(NMF) -o $@ $^ -s pnacl/Debug

pnacl/Release/hello_world.o : hello_world.cc $(THIS_MAKE) | pnacl/Release
	$(PNACL_CXX) -o $@ $< -O2  $(PNACL_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  

pnacl/Release/helper_functions.o : helper_functions.cc $(THIS_MAKE) | pnacl/Release
	$(PNACL_CXX) -o $@ $< -O2  $(PNACL_CCFLAGS) $(HELLO_WORLD_INTERACTIVE_CXXFLAGS)  


HELLO_WORLD_INTERACTIVE_PNACL_RELEASE_O:=$(patsubst %,pnacl/Release/%.o,$(HELLO_WORLD_INTERACTIVE_OBJS))
pnacl/Release/hello_world_interactive.pexe : $(HELLO_WORLD_INTERACTIVE_PNACL_RELEASE_O)
	$(PNACL_LINK) -o $@ $^ $(PNACL_LDFLAGS) $(HELLO_WORLD_INTERACTIVE_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/pnacl/Release -lppapi_cpp -lppapi -lpthread

pnacl/Release/hello_world_interactive_x86_32.nexe : pnacl/Release/hello_world_interactive.pexe
	$(TRANSLATE) -arch x86-32 $< -o $@

pnacl/Release/hello_world_interactive_x86_64.nexe : pnacl/Release/hello_world_interactive.pexe
	$(TRANSLATE) -arch x86-64 $< -o $@

pnacl/Release/hello_world_interactive_arm.nexe : pnacl/Release/hello_world_interactive.pexe
	$(TRANSLATE) -arch arm $< -o $@


ALL_TARGETS+=pnacl/Release/hello_world_interactive.nmf
pnacl/Release/hello_world_interactive.nmf : pnacl/Release/hello_world_interactive_x86_32.nexe pnacl/Release/hello_world_interactive_x86_64.nexe pnacl/Release/hello_world_interactive_arm.nexe
	$(NMF) -o $@ $^ -s pnacl/Release

#
# Target to remove temporary files
#
.PHONY: clean
clean:
	$(RM) -fr newlib/Debug
	$(RM) -fr newlib/Release
	$(RM) -fr glibc/Debug
	$(RM) -fr glibc/Release
	$(RM) -fr linux/Debug
	$(RM) -fr linux/Release
	$(RM) -fr pnacl/Debug
	$(RM) -fr pnacl/Release


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


