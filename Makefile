# The name of the binary to be created.
TARGET = hello
# The type of the binary to be created - ps-exe is most common.
TYPE = ps-exe

# The list of sources files to compile within the binary.
SRCS = \
src/main.cpp \
src/FontManager.cpp\
src/StageScene.cpp\
src/assets.cpp\

BUILD=Debug
UNAME_S := $(shell uname -s)
# Setting the minimum version of the C++. C++-20 is the minimum required version by PSYQo.
CXXFLAGS = -std=c++20 -Ithird_party/cxxmidi/include/cxxmidi
# This will activate the PSYQo library and the rest of the toolchain.
include third_party/nugget/psyqo/psyqo.mk
# TODO: build assets binaries at runtime (maybe)
# emu will run depending on os version (since i dev on both macos and linux)
emu: all
	ifeq($(UNAME_S),"Linux")
	/home/un/Downloads/PCSX-Redux-HEAD-x86_64.AppImage -run -exe $(TARGET).$(TYPE) &
	else
		ifeq($(UNAME_S),"Darwin")
		/Applications/PCSX-Redux.app/Contents/MacOS/PCSX-Redux -run -exe $(TARGET).$(TYPE) -debugger -fastboot &
		endif
	endif

