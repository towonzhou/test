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
NACL_SDK_ROOT?=$(abspath $(dir $(THIS_MAKEFILE))../..)
CHROME_PATH?=Undefined

#
# Defaults
#
NACL_WARNINGS:=-Wno-long-long


#
# Compute path to requested NaCl Toolchain
#
OSNAME:=$(shell python $(NACL_SDK_ROOT)/tools/getos.py)
TC_PATH:=$(abspath $(NACL_SDK_ROOT)/toolchain)


#
# Project Settings
#
VALID_TOOLCHAINS:=linux
TOOLCHAIN?=linux



#
# Project Targets
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
$(error Can not use TOOLCHAIN=$(TOOLCHAIN) on this library.)
endif


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

LINUX_WARNINGS?=-Wno-long-long
LINUX_CC?=gcc -c
LINUX_CXX?=g++ -c
LINUX_LINK?=g++
LINUX_LIB?=ar r
LINUX_CCFLAGS=-MMD -pthread $(LINUX_WARNINGS) -I$(NACL_SDK_ROOT)/include -I$(NACL_SDK_ROOT)/include/linux


#
# Per target object lists
#
PPAPI_GLES2_OBJS:=gl2ext_ppapi gles2

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

linux/Debug/gl2ext_ppapi_.o : gl2ext_ppapi.c $(THIS_MAKE) | linux/Debug
	$(LINUX_CC) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_GLES2_CCFLAGS)  

linux/Debug/gles2_.o : gles2.c $(THIS_MAKE) | linux/Debug
	$(LINUX_CC) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_GLES2_CCFLAGS)  


PPAPI_GLES2_LINUX_DEBUG__O:=$(patsubst %,linux/Debug/%_.o,$(PPAPI_GLES2_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/linux_host/Debug/libppapi_gles2.a
$(NACL_SDK_ROOT)/lib/linux_host/Debug/libppapi_gles2.a : $(PPAPI_GLES2_LINUX_DEBUG__O)
	$(MKDIR) -p $(dir $@)
	$(LINUX_LIB) $@ $^

linux/Release/gl2ext_ppapi_.o : gl2ext_ppapi.c $(THIS_MAKE) | linux/Release
	$(LINUX_CC) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_GLES2_CCFLAGS)  

linux/Release/gles2_.o : gles2.c $(THIS_MAKE) | linux/Release
	$(LINUX_CC) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_GLES2_CCFLAGS)  


PPAPI_GLES2_LINUX_RELEASE__O:=$(patsubst %,linux/Release/%_.o,$(PPAPI_GLES2_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/linux_host/Release/libppapi_gles2.a
$(NACL_SDK_ROOT)/lib/linux_host/Release/libppapi_gles2.a : $(PPAPI_GLES2_LINUX_RELEASE__O)
	$(MKDIR) -p $(dir $@)
	$(LINUX_LIB) $@ $^

#
# Target to remove temporary files
#
.PHONY: clean
clean:
	$(RM) -fr linux/Debug
	$(RM) -fr linux/Release


all: $(ALL_TARGETS)


