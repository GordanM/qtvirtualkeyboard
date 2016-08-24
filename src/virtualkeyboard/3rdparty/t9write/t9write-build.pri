#
# Automatically detects the T9Write build directory and sets the following variables:
#
#   T9WRITE_BUILD_DIR: A base directory for the architecture specific build directory
#   T9WRITE_LIBS: Absolute path to the target libraries
#

contains(QT_ARCH, arm) {
    T9WRITE_BUILD_DIR = $$files(build_Android_ARM*)
} else:linux {
    T9WRITE_BUILD_DIR = $$files(build_Android_x86*)
} else:win32 {
    T9WRITE_BUILD_DIR = $$files(build_VC*)
}

T9WRITE_BUILD_DIR = $$PWD

count(T9WRITE_BUILD_DIR, 1) {
    T9WRITE_FOUND = 1
    T9WRITE_INCLUDE_DIRS = $$T9WRITE_BUILD_DIR/api

    linux-g++ {
        T9WRITE_LIBS += $$T9WRITE_BUILD_DIR/t9libraries/i86_linux2_pc_64bit/ -lt9write -lt9write-cjk -lt9write-ucr
    }
    linux-oe-g++ {
        T9WRITE_LIBS += $$T9WRITE_BUILD_DIR/t9libraries/i86_linux2_tgt_64bit/ -lt9write -lt9write-cjk -lt9write-ucr
    }
    win32 {
        T9WRITE_LIBS += $$T9WRITE_BUILD_DIR/t9libraries/i86_win32/ -lt9write -lt9write-cjk -lt9write-ucr
    }
} else {
    T9WRITE_FOUND = 0
}
