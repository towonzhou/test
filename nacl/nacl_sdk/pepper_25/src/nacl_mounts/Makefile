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
VALID_TOOLCHAINS:=newlib glibc
TOOLCHAIN?=newlib



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


#
# Per target object lists
#
NACL_MOUNTS_OBJS:=kernel_handle kernel_intercept kernel_object kernel_proxy
NACL_MOUNTS_OBJS+=kernel_wrap mount mount_dev mount_html5fs mount_mem
NACL_MOUNTS_OBJS+=mount_node mount_node_dir mount_node_html5fs mount_node_mem
NACL_MOUNTS_OBJS+=nacl_mounts path pepper_interface real_pepper_interface

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

newlib/Debug/kernel_handle_x86_32.o : kernel_handle.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_intercept_x86_32.o : kernel_intercept.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_object_x86_32.o : kernel_object.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_proxy_x86_32.o : kernel_proxy.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_wrap_x86_32.o : kernel_wrap.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_x86_32.o : mount.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_dev_x86_32.o : mount_dev.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_html5fs_x86_32.o : mount_html5fs.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_mem_x86_32.o : mount_mem.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_x86_32.o : mount_node.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_dir_x86_32.o : mount_node_dir.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_html5fs_x86_32.o : mount_node_html5fs.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_mem_x86_32.o : mount_node_mem.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/nacl_mounts_x86_32.o : nacl_mounts.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/path_x86_32.o : path.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/pepper_interface_x86_32.o : pepper_interface.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/real_pepper_interface_x86_32.o : real_pepper_interface.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_NEWLIB_DEBUG_x86_32_O:=$(patsubst %,newlib/Debug/%_x86_32.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/newlib_x86_32/Debug/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/newlib_x86_32/Debug/libnacl_mounts.a : $(NACL_MOUNTS_NEWLIB_DEBUG_x86_32_O)
	$(MKDIR) -p $(dir $@)
	$(NEWLIB_LIB) $@ $^

newlib/Debug/kernel_handle_x86_64.o : kernel_handle.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_intercept_x86_64.o : kernel_intercept.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_object_x86_64.o : kernel_object.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_proxy_x86_64.o : kernel_proxy.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_wrap_x86_64.o : kernel_wrap.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_x86_64.o : mount.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_dev_x86_64.o : mount_dev.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_html5fs_x86_64.o : mount_html5fs.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_mem_x86_64.o : mount_mem.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_x86_64.o : mount_node.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_dir_x86_64.o : mount_node_dir.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_html5fs_x86_64.o : mount_node_html5fs.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_mem_x86_64.o : mount_node_mem.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/nacl_mounts_x86_64.o : nacl_mounts.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/path_x86_64.o : path.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/pepper_interface_x86_64.o : pepper_interface.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/real_pepper_interface_x86_64.o : real_pepper_interface.cc $(THIS_MAKE) | newlib/Debug
	$(NEWLIB_CXX) -o $@ $< -g -O0 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_NEWLIB_DEBUG_x86_64_O:=$(patsubst %,newlib/Debug/%_x86_64.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/newlib_x86_64/Debug/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/newlib_x86_64/Debug/libnacl_mounts.a : $(NACL_MOUNTS_NEWLIB_DEBUG_x86_64_O)
	$(MKDIR) -p $(dir $@)
	$(NEWLIB_LIB) $@ $^

newlib/Debug/kernel_handle_arm.o : kernel_handle.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_intercept_arm.o : kernel_intercept.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_object_arm.o : kernel_object.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_proxy_arm.o : kernel_proxy.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/kernel_wrap_arm.o : kernel_wrap.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_arm.o : mount.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_dev_arm.o : mount_dev.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_html5fs_arm.o : mount_html5fs.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_mem_arm.o : mount_mem.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_arm.o : mount_node.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_dir_arm.o : mount_node_dir.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_html5fs_arm.o : mount_node_html5fs.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/mount_node_mem_arm.o : mount_node_mem.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/nacl_mounts_arm.o : nacl_mounts.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/path_arm.o : path.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/pepper_interface_arm.o : pepper_interface.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Debug/real_pepper_interface_arm.o : real_pepper_interface.cc $(THIS_MAKE) | newlib/Debug
	$(ARM_CXX) -o $@ $< -g -O0  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_NEWLIB_DEBUG_arm_O:=$(patsubst %,newlib/Debug/%_arm.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/newlib_arm/Debug/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/newlib_arm/Debug/libnacl_mounts.a : $(NACL_MOUNTS_NEWLIB_DEBUG_arm_O)
	$(MKDIR) -p $(dir $@)
	$(ARM_LIB) $@ $^

newlib/Release/kernel_handle_x86_32.o : kernel_handle.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_intercept_x86_32.o : kernel_intercept.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_object_x86_32.o : kernel_object.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_proxy_x86_32.o : kernel_proxy.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_wrap_x86_32.o : kernel_wrap.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_x86_32.o : mount.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_dev_x86_32.o : mount_dev.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_html5fs_x86_32.o : mount_html5fs.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_mem_x86_32.o : mount_mem.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_x86_32.o : mount_node.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_dir_x86_32.o : mount_node_dir.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_html5fs_x86_32.o : mount_node_html5fs.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_mem_x86_32.o : mount_node_mem.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/nacl_mounts_x86_32.o : nacl_mounts.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/path_x86_32.o : path.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/pepper_interface_x86_32.o : pepper_interface.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/real_pepper_interface_x86_32.o : real_pepper_interface.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m32 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_NEWLIB_RELEASE_x86_32_O:=$(patsubst %,newlib/Release/%_x86_32.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/newlib_x86_32/Release/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/newlib_x86_32/Release/libnacl_mounts.a : $(NACL_MOUNTS_NEWLIB_RELEASE_x86_32_O)
	$(MKDIR) -p $(dir $@)
	$(NEWLIB_LIB) $@ $^

newlib/Release/kernel_handle_x86_64.o : kernel_handle.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_intercept_x86_64.o : kernel_intercept.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_object_x86_64.o : kernel_object.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_proxy_x86_64.o : kernel_proxy.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_wrap_x86_64.o : kernel_wrap.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_x86_64.o : mount.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_dev_x86_64.o : mount_dev.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_html5fs_x86_64.o : mount_html5fs.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_mem_x86_64.o : mount_mem.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_x86_64.o : mount_node.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_dir_x86_64.o : mount_node_dir.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_html5fs_x86_64.o : mount_node_html5fs.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_mem_x86_64.o : mount_node_mem.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/nacl_mounts_x86_64.o : nacl_mounts.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/path_x86_64.o : path.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/pepper_interface_x86_64.o : pepper_interface.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/real_pepper_interface_x86_64.o : real_pepper_interface.cc $(THIS_MAKE) | newlib/Release
	$(NEWLIB_CXX) -o $@ $< -O2 -m64 $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_NEWLIB_RELEASE_x86_64_O:=$(patsubst %,newlib/Release/%_x86_64.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/newlib_x86_64/Release/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/newlib_x86_64/Release/libnacl_mounts.a : $(NACL_MOUNTS_NEWLIB_RELEASE_x86_64_O)
	$(MKDIR) -p $(dir $@)
	$(NEWLIB_LIB) $@ $^

newlib/Release/kernel_handle_arm.o : kernel_handle.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_intercept_arm.o : kernel_intercept.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_object_arm.o : kernel_object.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_proxy_arm.o : kernel_proxy.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/kernel_wrap_arm.o : kernel_wrap.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_arm.o : mount.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_dev_arm.o : mount_dev.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_html5fs_arm.o : mount_html5fs.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_mem_arm.o : mount_mem.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_arm.o : mount_node.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_dir_arm.o : mount_node_dir.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_html5fs_arm.o : mount_node_html5fs.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/mount_node_mem_arm.o : mount_node_mem.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/nacl_mounts_arm.o : nacl_mounts.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/path_arm.o : path.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/pepper_interface_arm.o : pepper_interface.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

newlib/Release/real_pepper_interface_arm.o : real_pepper_interface.cc $(THIS_MAKE) | newlib/Release
	$(ARM_CXX) -o $@ $< -O2  $(NEWLIB_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_NEWLIB_RELEASE_arm_O:=$(patsubst %,newlib/Release/%_arm.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/newlib_arm/Release/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/newlib_arm/Release/libnacl_mounts.a : $(NACL_MOUNTS_NEWLIB_RELEASE_arm_O)
	$(MKDIR) -p $(dir $@)
	$(ARM_LIB) $@ $^


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

glibc/Debug/kernel_handle_x86_32.o : kernel_handle.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/kernel_intercept_x86_32.o : kernel_intercept.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/kernel_object_x86_32.o : kernel_object.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/kernel_proxy_x86_32.o : kernel_proxy.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/kernel_wrap_x86_32.o : kernel_wrap.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_x86_32.o : mount.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_dev_x86_32.o : mount_dev.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_html5fs_x86_32.o : mount_html5fs.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_mem_x86_32.o : mount_mem.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_node_x86_32.o : mount_node.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_node_dir_x86_32.o : mount_node_dir.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_node_html5fs_x86_32.o : mount_node_html5fs.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_node_mem_x86_32.o : mount_node_mem.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/nacl_mounts_x86_32.o : nacl_mounts.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/path_x86_32.o : path.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/pepper_interface_x86_32.o : pepper_interface.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/real_pepper_interface_x86_32.o : real_pepper_interface.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_GLIBC_DEBUG_x86_32_O:=$(patsubst %,glibc/Debug/%_x86_32.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/glibc_x86_32/Debug/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/glibc_x86_32/Debug/libnacl_mounts.a : $(NACL_MOUNTS_GLIBC_DEBUG_x86_32_O)
	$(MKDIR) -p $(dir $@)
	$(GLIBC_LIB) $@ $^

glibc/Debug/kernel_handle_x86_64.o : kernel_handle.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/kernel_intercept_x86_64.o : kernel_intercept.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/kernel_object_x86_64.o : kernel_object.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/kernel_proxy_x86_64.o : kernel_proxy.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/kernel_wrap_x86_64.o : kernel_wrap.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_x86_64.o : mount.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_dev_x86_64.o : mount_dev.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_html5fs_x86_64.o : mount_html5fs.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_mem_x86_64.o : mount_mem.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_node_x86_64.o : mount_node.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_node_dir_x86_64.o : mount_node_dir.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_node_html5fs_x86_64.o : mount_node_html5fs.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/mount_node_mem_x86_64.o : mount_node_mem.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/nacl_mounts_x86_64.o : nacl_mounts.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/path_x86_64.o : path.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/pepper_interface_x86_64.o : pepper_interface.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Debug/real_pepper_interface_x86_64.o : real_pepper_interface.cc $(THIS_MAKE) | glibc/Debug
	$(GLIBC_CXX) -o $@ $< -g -O0 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_GLIBC_DEBUG_x86_64_O:=$(patsubst %,glibc/Debug/%_x86_64.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/glibc_x86_64/Debug/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/glibc_x86_64/Debug/libnacl_mounts.a : $(NACL_MOUNTS_GLIBC_DEBUG_x86_64_O)
	$(MKDIR) -p $(dir $@)
	$(GLIBC_LIB) $@ $^

glibc/Release/kernel_handle_x86_32.o : kernel_handle.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/kernel_intercept_x86_32.o : kernel_intercept.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/kernel_object_x86_32.o : kernel_object.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/kernel_proxy_x86_32.o : kernel_proxy.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/kernel_wrap_x86_32.o : kernel_wrap.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_x86_32.o : mount.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_dev_x86_32.o : mount_dev.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_html5fs_x86_32.o : mount_html5fs.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_mem_x86_32.o : mount_mem.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_node_x86_32.o : mount_node.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_node_dir_x86_32.o : mount_node_dir.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_node_html5fs_x86_32.o : mount_node_html5fs.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_node_mem_x86_32.o : mount_node_mem.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/nacl_mounts_x86_32.o : nacl_mounts.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/path_x86_32.o : path.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/pepper_interface_x86_32.o : pepper_interface.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/real_pepper_interface_x86_32.o : real_pepper_interface.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m32 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_GLIBC_RELEASE_x86_32_O:=$(patsubst %,glibc/Release/%_x86_32.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/glibc_x86_32/Release/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/glibc_x86_32/Release/libnacl_mounts.a : $(NACL_MOUNTS_GLIBC_RELEASE_x86_32_O)
	$(MKDIR) -p $(dir $@)
	$(GLIBC_LIB) $@ $^

glibc/Release/kernel_handle_x86_64.o : kernel_handle.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/kernel_intercept_x86_64.o : kernel_intercept.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/kernel_object_x86_64.o : kernel_object.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/kernel_proxy_x86_64.o : kernel_proxy.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/kernel_wrap_x86_64.o : kernel_wrap.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_x86_64.o : mount.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_dev_x86_64.o : mount_dev.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_html5fs_x86_64.o : mount_html5fs.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_mem_x86_64.o : mount_mem.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_node_x86_64.o : mount_node.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_node_dir_x86_64.o : mount_node_dir.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_node_html5fs_x86_64.o : mount_node_html5fs.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/mount_node_mem_x86_64.o : mount_node_mem.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/nacl_mounts_x86_64.o : nacl_mounts.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/path_x86_64.o : path.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/pepper_interface_x86_64.o : pepper_interface.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  

glibc/Release/real_pepper_interface_x86_64.o : real_pepper_interface.cc $(THIS_MAKE) | glibc/Release
	$(GLIBC_CXX) -o $@ $< -O2 -m64 $(GLIBC_CCFLAGS) $(NACL_MOUNTS_CXXFLAGS)  


NACL_MOUNTS_GLIBC_RELEASE_x86_64_O:=$(patsubst %,glibc/Release/%_x86_64.o,$(NACL_MOUNTS_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/glibc_x86_64/Release/libnacl_mounts.a
$(NACL_SDK_ROOT)/lib/glibc_x86_64/Release/libnacl_mounts.a : $(NACL_MOUNTS_GLIBC_RELEASE_x86_64_O)
	$(MKDIR) -p $(dir $@)
	$(GLIBC_LIB) $@ $^

#
# Target to remove temporary files
#
.PHONY: clean
clean:
	$(RM) -fr newlib/Debug
	$(RM) -fr newlib/Release
	$(RM) -fr glibc/Debug
	$(RM) -fr glibc/Release


all: $(ALL_TARGETS)


