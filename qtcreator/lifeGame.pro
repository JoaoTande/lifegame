TEMPLATE += app
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++14 -Wall -Werror -Wextra -Wunused -Wno-switch



unix: {
    #INCLUDEPATH += /usr/include
    #INCLUDEPATH += -L/usr/include/c++/10
    LIBS += -L/usr/lib64
    LIBS += -lallegro -lallegro_primitives  -lallegro_font -lallegro_ttf -lallegro_image -lallegro_dialog

    debug: {
        DEFINES += GAME_DEBUG
    }

}

win32: {
    INCLUDEPATH += D:\libs\allegro_x86_64\include
    INCLUDEPATH += D:\projetos\libs\allegro-x86_64\allegro\include
    INCLUDEPATH += include

    LIBS += -LD:\libs\allegro_x86_64\lib
    LIBS += -LD:\projetos\libs\allegro-x86_64\allegro\lib



LIBS += -lallegro_monolith.dll
}

SOURCES += \
    ../Menu.cpp \
    ../bigTextLabel.cpp \
    ../button.cpp \
    ../config.cpp \
    ../gameScreenContext.cpp \
    ../hall.cpp \
    ../informationPanel.cpp \
    ../main.cpp

HEADERS += \
    ../Menu.h \
    ../bigTextLabel.h \
    ../button.h \
    ../config.h \
    ../gameScreenContext.h \
    ../hall.h \
    ../informationPanel.h \
    ../interfaceComponent.h \
    ../main.h \
    ../myButtonCallback.h
