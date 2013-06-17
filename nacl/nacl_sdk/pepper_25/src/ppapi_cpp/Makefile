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
PPAPI_CPP_OBJS:=ppp_entrypoints array_output audio audio_config core file_io
PPAPI_CPP_OBJS+=file_ref file_system fullscreen graphics_2d graphics_3d
PPAPI_CPP_OBJS+=graphics_3d_client image_data input_event instance
PPAPI_CPP_OBJS+=instance_handle lock module mouse_cursor mouse_lock rect
PPAPI_CPP_OBJS+=resource url_loader url_request_info url_response_info var
PPAPI_CPP_OBJS+=var_array_buffer view websocket paint_aggregator paint_manager
PPAPI_CPP_OBJS+=simple_thread websocket_api

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

linux/Debug/ppp_entrypoints_.o : ppp_entrypoints.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/array_output_.o : array_output.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/audio_.o : audio.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/audio_config_.o : audio_config.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/core_.o : core.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/file_io_.o : file_io.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/file_ref_.o : file_ref.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/file_system_.o : file_system.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/fullscreen_.o : fullscreen.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/graphics_2d_.o : graphics_2d.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/graphics_3d_.o : graphics_3d.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/graphics_3d_client_.o : graphics_3d_client.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/image_data_.o : image_data.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/input_event_.o : input_event.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/instance_.o : instance.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/instance_handle_.o : instance_handle.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/lock_.o : lock.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/module_.o : module.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/mouse_cursor_.o : mouse_cursor.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/mouse_lock_.o : mouse_lock.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/rect_.o : rect.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/resource_.o : resource.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/url_loader_.o : url_loader.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/url_request_info_.o : url_request_info.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/url_response_info_.o : url_response_info.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/var_.o : var.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/var_array_buffer_.o : var_array_buffer.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/view_.o : view.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/websocket_.o : websocket.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/paint_aggregator_.o : paint_aggregator.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/paint_manager_.o : paint_manager.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/simple_thread_.o : simple_thread.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Debug/websocket_api_.o : websocket_api.cc $(THIS_MAKE) | linux/Debug
	$(LINUX_CXX) -o $@ $< -g -O0  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  


PPAPI_CPP_LINUX_DEBUG__O:=$(patsubst %,linux/Debug/%_.o,$(PPAPI_CPP_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/linux_host/Debug/libppapi_cpp.a
$(NACL_SDK_ROOT)/lib/linux_host/Debug/libppapi_cpp.a : $(PPAPI_CPP_LINUX_DEBUG__O)
	$(MKDIR) -p $(dir $@)
	$(LINUX_LIB) $@ $^

linux/Release/ppp_entrypoints_.o : ppp_entrypoints.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/array_output_.o : array_output.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/audio_.o : audio.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/audio_config_.o : audio_config.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/core_.o : core.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/file_io_.o : file_io.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/file_ref_.o : file_ref.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/file_system_.o : file_system.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/fullscreen_.o : fullscreen.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/graphics_2d_.o : graphics_2d.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/graphics_3d_.o : graphics_3d.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/graphics_3d_client_.o : graphics_3d_client.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/image_data_.o : image_data.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/input_event_.o : input_event.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/instance_.o : instance.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/instance_handle_.o : instance_handle.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/lock_.o : lock.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/module_.o : module.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/mouse_cursor_.o : mouse_cursor.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/mouse_lock_.o : mouse_lock.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/rect_.o : rect.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/resource_.o : resource.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/url_loader_.o : url_loader.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/url_request_info_.o : url_request_info.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/url_response_info_.o : url_response_info.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/var_.o : var.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/var_array_buffer_.o : var_array_buffer.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/view_.o : view.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/websocket_.o : websocket.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/paint_aggregator_.o : paint_aggregator.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/paint_manager_.o : paint_manager.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/simple_thread_.o : simple_thread.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  

linux/Release/websocket_api_.o : websocket_api.cc $(THIS_MAKE) | linux/Release
	$(LINUX_CXX) -o $@ $< -O2  -fPIC $(LINUX_CCFLAGS) $(PPAPI_CPP_CXXFLAGS)  


PPAPI_CPP_LINUX_RELEASE__O:=$(patsubst %,linux/Release/%_.o,$(PPAPI_CPP_OBJS))
ALL_TARGETS+=$(NACL_SDK_ROOT)/lib/linux_host/Release/libppapi_cpp.a
$(NACL_SDK_ROOT)/lib/linux_host/Release/libppapi_cpp.a : $(PPAPI_CPP_LINUX_RELEASE__O)
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


