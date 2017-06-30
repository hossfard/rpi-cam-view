TARGET = rpicamview

QT += qml quick websockets

QMAKE_CXXFLAGS += -std=c++11

HEADERS += RemoteImage.h \
           RemoteSocketImage.h

SOURCES += main.cpp \
           RemoteImage.cpp \
           RemoteSocketImage.cpp

RESOURCES += resources.qrc

MOC_DIR = moc
OBJECTS_DIR = obj

# DESTPATH == $${

qml.files = *.qml

# INSTALLS += target
