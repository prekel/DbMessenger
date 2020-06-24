ECPG = ecpg
CC = gcc

CFLAGS = -O0 -Wall -std=gnu11 -DHAVE_LONG_LONG_INT_64
LDFLAGS = -L$(shell pg_config --libdir) -lecpg -lpgtypes
INC = -I.. -I$(shell pg_config --includedir)

PGCS = Accounts.pgc Context.pgc Dialogs.pgc Locks.pgc Messages.pgc
GENSOURCES = $(PGCS:.pgc=.c)
SOURCES = main.c IO.c
OBJECTS = $(GENSOURCES:.c=.o) $(SOURCES:.c=.o)

OUTFILE = DbMessenger

all: $(SOURCES) $(GENSOURCES) $(OBJECTS) $(OUTFILE)

%.c: %.pgc
	$(ECPG) $<

%.o: %.c
	$(CC) -c $(INC) $(CFLAGS) $< -o $@

$(OUTFILE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(GENSOURCES) $(OBJECTS) $(OUTFILE)

.PHONY: cleandel
cleandel:
	del $(GENSOURCES)
	del $(OBJECTS)
	del $(OUTFILE).exe

.PHONY: ecpg
ecpg: ${GENSOURCES}
