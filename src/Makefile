SRCMODULES = main.cpp Game.cpp TextureManager.cpp InputHandler.cpp \
GameObject.cpp Player.cpp Ball.cpp
OBJMODULES = $(SRCMODULES:.cpp=.o)
INCLUDEDIRS = include
CXX=c++
CXXFLAGS = -Wall -g `sdl2-config --cflags` $(INCLUDEDIRS:%=-iquote %)
LDFLAGS = -lm `sdl2-config --libs` -lSDL2_image

%.o: %.c $(foreach dir, $(INCLUDEDIRS), $dir/%.h)
	$(CXX) $(CXXFLAGS) -c -o $@ $< 
a.out: $(OBJMODULES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

ifneq (clean, $(MAKECMDGOALS))
-include deps.mk
endif

deps.mk: $(SRCMODULES)
	$(CXX) $(INCLUDEDIRS:%=-iquote %) -MM $^ > $@

clean:
	$(RM) -rf *.o deps.mk a.out
