LIBS += -LC:/SFML/lib



CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include

SOURCES += \
    main.cpp \
    mainclass.cpp \
    bullet.cpp \
    player.cpp \
    enemy.cpp \
    mycircle.cpp

HEADERS += \
    header.h \
    mainclass.h \
    bullet.h \
    player.h \
    enemy.h \
    mycircle.h
