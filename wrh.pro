TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    allpackets.cpp \
    packet.cpp \
    protocol.cpp \
    eth.cpp \
    ipv4.cpp \
    arp.cpp \
    icmp.cpp \
    udp.cpp \
    tcp.cpp \
    other.cpp \
    input.cpp

HEADERS += \
    allpackets.h \
    packet.h \
    protocol.h \
    eth.h \
    ipv4.h \
    arp.h \
    icmp.h \
    udp.h \
    tcp.h \
    other.h

