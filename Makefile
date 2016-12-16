PKC_OBJS=pokemoncal.o
CRELIB=crelib/libcre.a
CRELIB_OBJS=crelib/*

all: pkc

win: pkc.exe

pkc: $(PKC_OBJS) $(CRELIB)
	$(LINK.cpp) $^ -o $@

$(CRELIB): $(CRELIB_OBJS)
	cd crelib && make

clean:
	rm *.o pkc
