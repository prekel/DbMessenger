ECPG = ecpg
CC = gcc

CFLAGS = -O0 -Wall -std=gnu99
LDFLAGS = -L$(shell pg_config --libdir) -lecpg
INC = -I.. -I$(shell pg_config --includedir)

PGCS = main.pgc
SOURCES = $(PGCS:.pgc=.c)
OBJECTS = $(SOURCES:.c=.o)

OUTFILE = DbMessenger

all: $(SOURCES) $(OBJECTS) $(OUTFILE)

%.c: %.pgc
	$(ECPG) $<

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(SOURCES) $(OBJECTS) $(OUTFILE)

.PHONY: cleandel
cleandel:
	del $(SOURCES)
	del $(OBJECTS)
	del $(OUTFILE)

.PHONY: ecpg
ecpg: ${SOURCES}
