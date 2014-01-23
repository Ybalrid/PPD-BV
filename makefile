CC = g++

SYSARCH       = i386
ifeq ($(shell uname -m),x86_64)
SYSARCH       = x86_64
endif

CFLAGS =
LDFLAGS = -L/usr/local/lib/Annwvyn -L../OculusSDK/LibOVR/Lib/Linux/Release/$(SYSARCH) -L/usr/local/lib -L/usr/local/lib/OGRE/ -lAnnwvyn  -lovr -lOgreMain -lOIS -lopenal -lBulletDynamics -lBulletCollision -lLinearMath -lsndfile -lX11 -lXinerama -ludev -lboost_system -lCEGUIBase-0 -lCEGUIOgreRenderer-0 -lpthread
IFLAGS =-I/usr/include/OGRE  -I/usr/local/include/OGRE  -I../OculusSDK/LibOVR/Include  -I/usr/include/AL -I/usr/include/bullet -I/usr/local/include/bullet  -I/usr/include/OIS -I/usr/include/boost -I/usr/include/cegui-0 -I/usr/local/include/cegui-0 -I./include/ -I/usr/local/include/Annwvyn

all: bin/ppd

bin/ppd: obj/main.o obj/JoystickController.o 
	$(CC) obj/main.o obj/JoystickController.o -o bin/ppd $(LDFLAGS) $(IFLAGS)

obj/main.o: src/main.cpp
	$(CC) src/main.cpp -c -o obj/main.o $(LDFMAGS) $(IFLAGS)

obj/JoystickController.o: src/JoystickController.cpp include/JoystickController.hpp
	$(CC) src/JoystickController.cpp -c -o obj/JoystickController.o $(LDFLAGS) $(IFLAGS)

