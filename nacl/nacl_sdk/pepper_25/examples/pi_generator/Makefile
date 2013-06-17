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
PI_GENERATOR_OBJS:=pi_generator pi_generator_module

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

newlib/Debug/pi_generator_x86_32.o : pi_generator.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

newlib/Debug/pi_generator_module_x86_32.o : pi_generator_module.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_NEWLIB_DEBUG_x86_32_O:=$(patsubst %,newlib/Debug/%_x86_32.o,$(PI_GENERATOR_OBJS))
newlib/Debug/pi_generator_x86_32.nexe : $(PI_GENERATOR_NEWLIB_DEBUG_x86_32_O)
	$(NEWLIB_LINK) -o $@ $^ -g -m32 $(NEWLIB_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_32/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

newlib/Debug/pi_generator_x86_64.o : pi_generator.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

newlib/Debug/pi_generator_module_x86_64.o : pi_generator_module.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_NEWLIB_DEBUG_x86_64_O:=$(patsubst %,newlib/Debug/%_x86_64.o,$(PI_GENERATOR_OBJS))
newlib/Debug/pi_generator_x86_64.nexe : $(PI_GENERATOR_NEWLIB_DEBUG_x86_64_O)
	$(NEWLIB_LINK) -o $@ $^ -g -m64 $(NEWLIB_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_64/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

newlib/Debug/pi_generator_arm.o : pi_generator.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

newlib/Debug/pi_generator_module_arm.o : pi_generator_module.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_NEWLIB_DEBUG_arm_O:=$(patsubst %,newlib/Debug/%_arm.o,$(PI_GENERATOR_OBJS))
newlib/Debug/pi_generator_arm.nexe : $(PI_GENERATOR_NEWLIB_DEBUG_arm_O)
	$(ARM_LINK) -o $@ $^ -g  $(NEWLIB_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_arm/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=newlib/Debug/pi_generator.nmf
newlib/Debug/pi_generator.nmf : newlib/Debug/pi_generator_x86_32.nexe newlib/Debug/pi_generator_x86_64.nexe newlib/Debug/pi_generator_arm.nexe
	$(NMF) -o $@ $^ -s newlib/Debug

newlib/Release/pi_generator_x86_32.o : pi_generator.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

newlib/Release/pi_generator_module_x86_32.o : pi_generator_module.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_NEWLIB_RELEASE_x86_32_O:=$(patsubst %,newlib/Release/%_x86_32.o,$(PI_GENERATOR_OBJS))
newlib/Release/pi_generator_x86_32.nexe : $(PI_GENERATOR_NEWLIB_RELEASE_x86_32_O)
	$(NEWLIB_LINK) -o $@ $^ -m32 $(NEWLIB_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_32/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

newlib/Release/pi_generator_x86_64.o : pi_generator.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

newlib/Release/pi_generator_module_x86_64.o : pi_generator_module.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_NEWLIB_RELEASE_x86_64_O:=$(patsubst %,newlib/Release/%_x86_64.o,$(PI_GENERATOR_OBJS))
newlib/Release/pi_generator_x86_64.nexe : $(PI_GENERATOR_NEWLIB_RELEASE_x86_64_O)
	$(NEWLIB_LINK) -o $@ $^ -m64 $(NEWLIB_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_x86_64/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

newlib/Release/pi_generator_arm.o : pi_generator.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

newlib/Release/pi_generator_module_arm.o : pi_generator_module.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_NEWLIB_RELEASE_arm_O:=$(patsubst %,newlib/Release/%_arm.o,$(PI_GENERATOR_OBJS))
newlib/Release/pi_generator_arm.nexe : $(PI_GENERATOR_NEWLIB_RELEASE_arm_O)
	$(ARM_LINK) -o $@ $^  $(NEWLIB_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/newlib_arm/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=newlib/Release/pi_generator.nmf
newlib/Release/pi_generator.nmf : newlib/Release/pi_generator_x86_32.nexe newlib/Release/pi_generator_x86_64.nexe newlib/Release/pi_generator_arm.nexe
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

glibc/Debug/pi_generator_x86_32.o : pi_generator.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

glibc/Debug/pi_generator_module_x86_32.o : pi_generator_module.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_GLIBC_DEBUG_x86_32_O:=$(patsubst %,glibc/Debug/%_x86_32.o,$(PI_GENERATOR_OBJS))
glibc/Debug/pi_generator_x86_32.nexe : $(PI_GENERATOR_GLIBC_DEBUG_x86_32_O)
	$(GLIBC_LINK) -o $@ $^ -g -m32 $(GLIBC_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_32/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

glibc/Debug/pi_generator_x86_64.o : pi_generator.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

glibc/Debug/pi_generator_module_x86_64.o : pi_generator_module.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_GLIBC_DEBUG_x86_64_O:=$(patsubst %,glibc/Debug/%_x86_64.o,$(PI_GENERATOR_OBJS))
glibc/Debug/pi_generator_x86_64.nexe : $(PI_GENERATOR_GLIBC_DEBUG_x86_64_O)
	$(GLIBC_LINK) -o $@ $^ -g -m64 $(GLIBC_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_64/Debug -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=glibc/Debug/pi_generator.nmf
glibc/Debug/pi_generator.nmf : glibc/Debug/pi_generator_x86_32.nexe glibc/Debug/pi_generator_x86_64.nexe
	$(NMF) -D $(GLIBC_DUMP) -o $@ $(GLIBC_PATHS) $^ -s glibc/Debug $(GLIBC_REMAP)

glibc/Release/pi_generator_x86_32.o : pi_generator.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

glibc/Release/pi_generator_module_x86_32.o : pi_generator_module.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_GLIBC_RELEASE_x86_32_O:=$(patsubst %,glibc/Release/%_x86_32.o,$(PI_GENERATOR_OBJS))
glibc/Release/pi_generator_x86_32.nexe : $(PI_GENERATOR_GLIBC_RELEASE_x86_32_O)
	$(GLIBC_LINK) -o $@ $^ -m32 $(GLIBC_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_32/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group

glibc/Release/pi_generator_x86_64.o : pi_generator.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

glibc/Release/pi_generator_module_x86_64.o : pi_generator_module.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_GLIBC_RELEASE_x86_64_O:=$(patsubst %,glibc/Release/%_x86_64.o,$(PI_GENERATOR_OBJS))
glibc/Release/pi_generator_x86_64.nexe : $(PI_GENERATOR_GLIBC_RELEASE_x86_64_O)
	$(GLIBC_LINK) -o $@ $^ -m64 $(GLIBC_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/glibc_x86_64/Release  -Wl,--start-group -lppapi_cpp -lppapi -lpthread -Wl,--end-group


ALL_TARGETS+=glibc/Release/pi_generator.nmf
glibc/Release/pi_generator.nmf : glibc/Release/pi_generator_x86_32.nexe glibc/Release/pi_generator_x86_64.nexe
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

PPAPI_DEBUG:=$(abspath linux/Debug/libpi_generator.so);application/x-ppapi-debug
linux/Debug/pi_generator_.o : pi_generator.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

linux/Debug/pi_generator_module_.o : pi_generator_module.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_LINUX_DEBUG__O:=$(patsubst %,linux/Debug/%_.o,$(PI_GENERATOR_OBJS))
linux/Debug/libpi_generator.so : $(PI_GENERATOR_LINUX_DEBUG__O)
	$(LINUX_LINK) -o $@ $^ -g  -shared $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/$(OSNAME)_host/Debug -Wl,--whole-archive -lppapi_cpp -lppapi -lpthread -Wl,--no-whole-archive


ALL_TARGETS+=linux/Debug/pi_generator.nmf
linux/Debug/pi_generator.nmf : linux/Debug/libpi_generator.so | linux/Debug
	echo {} > $@

PPAPI_RELEASE:=$(abspath linux/Release/libpi_generator.so);application/x-ppapi-release
linux/Release/pi_generator_.o : pi_generator.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

linux/Release/pi_generator_module_.o : pi_generator_module.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_LINUX_RELEASE__O:=$(patsubst %,linux/Release/%_.o,$(PI_GENERATOR_OBJS))
linux/Release/libpi_generator.so : $(PI_GENERATOR_LINUX_RELEASE__O)
	$(LINUX_LINK) -o $@ $^  -shared $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/$(OSNAME)_host/Release -Wl,--whole-archive -lppapi_cpp -lppapi -lpthread -Wl,--no-whole-archive


ALL_TARGETS+=linux/Release/pi_generator.nmf
linux/Release/pi_generator.nmf : linux/Release/libpi_generator.so | linux/Release
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

pnacl/Debug/pi_generator.o : pi_generator.cc $(THIS_MAKE) | pnacl/Debug
	$(PNACL_CXX) -o $@ $< -g -O0  $(PNACL_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

pnacl/Debug/pi_generator_module.o : pi_generator_module.cc $(THIS_MAKE) | pnacl/Debug
	$(PNACL_CXX) -o $@ $< -g -O0  $(PNACL_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_PNACL_DEBUG_O:=$(patsubst %,pnacl/Debug/%.o,$(PI_GENERATOR_OBJS))
pnacl/Debug/pi_generator.pexe : $(PI_GENERATOR_PNACL_DEBUG_O)
	$(PNACL_LINK) -o $@ $^ -g $(PNACL_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/pnacl/Debug -lppapi_cpp -lppapi -lpthread

pnacl/Debug/pi_generator_x86_32.nexe : pnacl/Debug/pi_generator.pexe
	$(TRANSLATE) -arch x86-32 $< -o $@

pnacl/Debug/pi_generator_x86_64.nexe : pnacl/Debug/pi_generator.pexe
	$(TRANSLATE) -arch x86-64 $< -o $@

pnacl/Debug/pi_generator_arm.nexe : pnacl/Debug/pi_generator.pexe
	$(TRANSLATE) -arch arm $< -o $@


ALL_TARGETS+=pnacl/Debug/pi_generator.nmf
pnacl/Debug/pi_generator.nmf : pnacl/Debug/pi_generator_x86_32.nexe pnacl/Debug/pi_generator_x86_64.nexe pnacl/Debug/pi_generator_arm.nexe
	$(NMF) -o $@ $^ -s pnacl/Debug

pnacl/Release/pi_generator.o : pi_generator.cc $(THIS_MAKE) | pnacl/Release
	$(PNACL_CXX) -o $@ $< -O2  $(PNACL_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  

pnacl/Release/pi_generator_module.o : pi_generator_module.cc $(THIS_MAKE) | pnacl/Release
	$(PNACL_CXX) -o $@ $< -O2  $(PNACL_CCFLAGS) $(PI_GENERATOR_CXXFLAGS)  


PI_GENERATOR_PNACL_RELEASE_O:=$(patsubst %,pnacl/Release/%.o,$(PI_GENERATOR_OBJS))
pnacl/Release/pi_generator.pexe : $(PI_GENERATOR_PNACL_RELEASE_O)
	$(PNACL_LINK) -o $@ $^ $(PNACL_LDFLAGS) $(PI_GENERATOR_LDFLAGS) -L$(NACL_SDK_ROOT)/lib/pnacl/Release -lppapi_cpp -lppapi -lpthread

pnacl/Release/pi_generator_x86_32.nexe : pnacl/Release/pi_generator.pexe
	$(TRANSLATE) -arch x86-32 $< -o $@

pnacl/Release/pi_generator_x86_64.nexe : pnacl/Release/pi_generator.pexe
	$(TRANSLATE) -arch x86-64 $< -o $@

pnacl/Release/pi_generator_arm.nexe : pnacl/Release/pi_generator.pexe
	$(TRANSLATE) -arch arm $< -o $@


ALL_TARGETS+=pnacl/Release/pi_generator.nmf
pnacl/Release/pi_generator.nmf : pnacl/Release/pi_generator_x86_32.nexe pnacl/Release/pi_generator_x86_64.nexe pnacl/Release/pi_generator_arm.nexe
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


