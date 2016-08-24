TEMPLATE = aux

libt9write.path = $$[QT_INSTALL_LIBS]

linux-g++ {
    libt9write.files = i86_linux2_pc_64bit/*.so
}
linux-oe-g++ {
    libt9write.files = i86_linux2_tgt_64bit/*.so
}
win32 {
    libt9write.files = i86_win32/*
}

QMAKE_EXTRA_TARGETS += libt9write
POST_TARGETDEPS += libt9write
INSTALLS += libt9write
!prefix_build: COPIES += libt9write
