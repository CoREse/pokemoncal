PKC_OBJS=pokemoncal.o
CRELIB=crelib/libcre.a
CRELIB_OBJS=crelib/*.o
WCCPP=x86_64-w64-mingw32-g++

all: pkc

win: pkc.exe

pkc: $(PKC_OBJS) $(CRELIB)
	$(LINK.cpp) $^ -o $@

$(CRELIB): $(CRELIB_OBJS)
	cd crelib && make

pkc.exe: pokemoncal.wo crelib/crelib.wo
	$(WCCPP) -o $@ $^

pokemoncal.wo:pokemoncal.cpp
	$(WCCPP) -o $@ -c $^

crelib/crelib.wo:crelib/crelib.cpp
	$(WCCPP) -o $@ -c $^

clean:
	rm *.o pkc *.wo pkc.exe
