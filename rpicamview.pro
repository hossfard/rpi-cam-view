TARGET = rpicamview

QT += qml quick

QMAKE_CXXFLAGS += -std=c++11

HEADERS += RemoteImage.h

SOURCES += main.cpp \
           RemoteImage.cpp

RESOURCES += resources.qrc

MOC_DIR = moc
OBJECTS_DIR = obj

# DESTPATH == $${

qml.files = *.qml

# INSTALLS += target
