CC=gcc
CFLAGS=`pkg-config sdl2-config --cflags` -c -Wall -ggdb -std=c89 -pedantic -I /usr/local/include
LDFLAGS=`pkg-config sdl2-config --libs` -lm
HOMEDIR=..
BUILDDIR=$(HOMEDIR)/build
OBJFILES=$(BUILDDIR)/main.o $(BUILDDIR)/jetplane.o $(BUILDDIR)/alien.o $(BUILDDIR)/bullet.o $(BUILDDIR)/dlist.o $(BUILDDIR)/symex_parse.o $(BUILDDIR)/symex_write.o $(BUILDDIR)/symex_list.o

$(BUILDDIR)/game:$(OBJFILES)
	$(CC) $(LDFLAGS) -o $(BUILDDIR)/game $(OBJFILES)

$(BUILDDIR)/main.o:main.c debug.h game.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/main.o main.c

$(BUILDDIR)/bullet.o:bullet.c bullet.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/bullet.o bullet.c

$(BUILDDIR)/jetplane.o:jetplane.c jetplane.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/jetplane.o jetplane.c

$(BUILDDIR)/alien.o:alien.c alien.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/alien.o alien.c

$(BUILDDIR)/dlist.o:dlist.c dlist.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/dlist.o dlist.c

$(BUILDDIR)/symex_parse.o:symex_parse.c symex_parse.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/symex_parse.o symex_parse.c

$(BUILDDIR)/symex_write.o:symex_write.c symex_write.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/symex_write.o symex_write.c

$(BUILDDIR)/symex_list.o:symex_list.c symex_list.h
	$(CC) $(CFLAGS) -o $(BUILDDIR)/symex_list.o symex_list.c

clean:
	rm $(OBJFILES)
	rm $(BUILDDIR)/game

.PHONY:clean
