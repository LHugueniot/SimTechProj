TARGET=TestCloth
SOURCES+= main.cpp
INCLUDEPATH+=/usr/local/include
LIBS+= -L/usr/local/lib -L../ClothLib -lgtest -lClothSimLib
CONFIG+=c++11

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ClothLib/release/ -lClothSimLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ClothLib/debug/ -lClothSimLib
else:unix: LIBS += -L$$OUT_PWD/../ClothLib/ -lClothSimLib

INCLUDEPATH += $$PWD/../ClothLib
DEPENDPATH += $$PWD/../ClothLib
