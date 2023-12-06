ROOT=$(realpath $(CURDIR))/

FINAL=$(ROOT)emu-z64

SOURCES=\
main.c\
memory/regions.c\
options/get_options.c\
interpret/interpret.c\
rom/romops.c

INCLUDE=$(ROOT)include
export INCLUDE

OBJECTS=$(SOURCES:.c=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)

CC=gcc
CFLAGS?=-O2
CFLAGS+=-MD -Wall
CPPFLAGS?=
CPPFLAGS+=-I$(INCLUDE)

LD=gcc
LDFLAGS?=
LDFLAGS+=
LDLIBS?=
LDLIBS+=

.PHONY: all build

all: build

build: $(OBJECTS) $(FINAL)

clean: 
	-rm -rf $(FINAL)
	-rm `find | grep "\.o"`
	-rm `find | grep "\.d"`
	-rm `find | grep "\.bin"`

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(CPPFLAGS)

$(FINAL): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^ $(LDLIBS)

-include $(DEPENDENCIES)