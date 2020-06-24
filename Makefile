ECPG = ecpg
CC = gcc

CFLAGS = -O0 -Wall -std=gnu11
LDFLAGS = -L$(shell pg_config --libdir) -lecpg -lpgtypes
INC = -I.. -I$(shell pg_config --includedir)

PGCS = main.pgc Accounts.pgc Context.pgc Dialogs.pgc Locks.pgc Messages.pgc
GENSOURCES = $(PGCS:.pgc=.c)
SOURCES = IO.c
OBJECTS = $(GENSOURCES:.c=.o)

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
