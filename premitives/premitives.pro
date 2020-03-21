TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QT += opengl

LIBS += -lopengl32

SOURCES += \
        main.cpp \
    settings/classes/resource_manager.cpp \
    settings/classes/shader.cpp \
    settings/objects/circle.cpp \
    settings/objects/line.cpp \
    settings/objects/point.cpp \
    settings/objects/triangle.cpp \
    settings/objects/commet.cpp \
    settings/tools/main_tool.cpp

win32: LIBS += -L$$PWD/../GLFW/lib-mingw/ -lglfw3

INCLUDEPATH += $$PWD/../GLFW/lib-mingw
DEPENDPATH += $$PWD/../GLFW/lib-mingw

win32: LIBS += -L$$PWD/../GLFW/lib-mingw/ -lglfw3dll

INCLUDEPATH += $$PWD/../GLFW/lib-mingw
DEPENDPATH += $$PWD/../GLFW/lib-mingw


INCLUDEPATH += $$PWD/../GLFW/include/GLFW/

win32: LIBS += -LE:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/lib/ -lgdi32

INCLUDEPATH += E:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/include
DEPENDPATH += E:/Programs/qt/Tools/mingw530_32/i686-w64-mingw32/include


HEADERS += \
    ../GLFW/include/GLFW/glfw3.h \
    ../GLFW/include/GLFW/glfw3native.h \
    settings/classes/resource_manager.h \
    settings/classes/shader.h \
    settings/objects/circle.h \
    settings/objects/line.h \
    settings/objects/point.h \
    settings/objects/triangle.h \
    settings/objects/commet.h \
    settings/tools/main_tool.h

DISTFILES += \
    settings/shaders/circle/circle.frag \
    settings/shaders/circle/circle.vert \
    settings/shaders/line/line.frag \
    settings/shaders/line/line.vert \
    settings/shaders/point/point.frag \
    settings/shaders/point/point.vert \
    settings/shaders/triangle/triangle.frag \
    settings/shaders/triangle/triangle.vert \
    settings/vertices/spruce \
    settings/vertices/stone

