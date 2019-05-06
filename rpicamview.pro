TARGET = rpicamview

QT += qml quick websockets

QMAKE_CXXFLAGS += -std=c++11

HEADERS += src/RemoteImage.h \
           src/RemoteSocketImage.h

SOURCES += src/main.cpp \
           src/RemoteImage.cpp \
           src/RemoteSocketImage.cpp

RESOURCES += resources.qrc

MOC_DIR = moc
OBJECTS_DIR = obj

# DESTPATH == $${

qml.files = src/*.qml

# INSTALLS += target
