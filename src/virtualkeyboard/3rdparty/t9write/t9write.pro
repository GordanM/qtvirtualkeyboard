TEMPLATE = aux

T9WRITE_QRC = $$OUT_PWD/t9write_db.qrc
T9WRITE_RCC = $$OUT_PWD/t9write_db.rcc

build_pass {
    CONFIG(debug, debug|release): SUBPATH = debug
    else: SUBPATH = release
} else {
    debug_and_release: CONFIG += build_all
}

DESTDIR = $$SUBPATH

XT9_LDBS     += $$files(databases/XT9_LDBs/*.ldb)
T9WRITE_DATABASES += $$files(databases/Alphabetic/LatinCG/*.bin)
T9WRITE_DATABASES += $$files(databases/Alphabetic/Arabic/*.bin)
T9WRITE_DATABASES += $$files(databases/Cursive/Arabic/*.bin)

T9WRITE_DATABASES += $$files(databases/CJK/HK/*.hdb)
T9WRITE_DATABASES += $$files(databases/CJK/J/*.hdb)
T9WRITE_DATABASES += $$files(databases/CJK/K/*.hdb)
T9WRITE_DATABASES += $$files(databases/CJK/S/*.hdb)
T9WRITE_DATABASES += $$files(databases/CJK/T/*.hdb)

T9WRITE_RESOURCE_FILES = \
    $$T9WRITE_DATABASES \
    $$XT9_LDBS \

include(../../generateresource.pri)

$$generate_resource(t9write_db.qrc, $$T9WRITE_RESOURCE_FILES)

exists($$T9WRITE_QRC) {
    system(rcc -binary -no-compress $$T9WRITE_QRC -o $$T9WRITE_RCC)
}

!exists($$T9WRITE_RCC) {
    error("The T9WRITE language database wasn't created.")
}

t9write.files = $$T9WRITE_RCC
t9write.path = $$[QT_INSTALL_DATA]/qtvirtualkeyboard/t9write

INSTALLS += t9write
!prefix_build: COPIES += t9write
