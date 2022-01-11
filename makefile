PROG=demo0
SRC=main.c

all: $(PROG)

$(PROG): $(SRC)
	gcc $(SRC) -o $(PROG)
