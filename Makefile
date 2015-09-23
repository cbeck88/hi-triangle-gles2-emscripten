CXXFLAGS := -std=c++11

select_gcc =

INCLUDES += -I.

ifeq ($(CXX),g++)
CXXFLAGS += $(shell pkg-config --cflags gl)
LIBS += $(shell pkg-config --libs gl)
#CXXFLAGS += $(shell pkg-config --cflags glesv2)
#LIBS += $(shell pkg-config --libs glesv2)
CXXFLAGS += $(shell pkg-config --cflags sdl2)
LIBS += $(shell pkg-config --libs sdl2)

#LIBS += -lglut
#LDFLAGS += 
#CXXFLAGS += -Ifreeglut-native-gles/include/
#LIBS += -Lfreeglut-native-gles/lib/
#LIBS += -lfreeglut-gles -lGLESv2
else
endif

LD = $(CXX)

game.o: game.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

main.o: main.cpp
	echo $(CXX)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

main.html: main.o game.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

main: main.o game.o
	$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f game.o
	rm -f main.o
	rm -f main.js
	rm -f main.html
	rm -f main
