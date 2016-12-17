PKC_OBJS=pokemoncal.o
PKC_WOBJS=pokemoncal.wo crelib/crelib.wo
CRELIB=crelib/libcre.a
CRELIB_OBJS=crelib/*.o
WCCPP=x86_64-w64-mingw32-g++

all: pkc

win: pkc.exe

pkc: $(PKC_OBJS) $(CRELIB)
	$(LINK.cpp) $^ -o $@

$(CRELIB): $(CRELIB_OBJS)
	cd crelib && make

pkc.exe: $(PKC_WOBJS)
	$(WCCPP) -o $@ $^

%.wo:%.cpp
	$(WCCPP) -o $@ -c $<

clean:
	rm *.o pkc $(PKC_WOBJS) pkc.exe
