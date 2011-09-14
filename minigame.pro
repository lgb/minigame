#-------------------------------------------------
#
# Project created by QtCreator 2011-09-14T14:31:13
#
#-------------------------------------------------

QT			+= core gui opengl

TARGET		= minigame
TEMPLATE	= app

RESOURCES	= minigame.qrc

SOURCES	+= src/main.cpp\
				src/FakeEngine.cpp

HEADERS	+= src/FakeEngine.h \
				src/MiniGameInterface.h
