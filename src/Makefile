EXE = hash-table
SRC = $(wildcard *.c)
OBJS = $(addprefix build/,$(SRC:.c=.o))

all: $(EXE)

$(EXE): $(OBJS)
		gcc -g -O3 -o $(EXE) $(OBJS)

build/%.o: %.c
		gcc -g -O3 -Wall -c -o "$@" "$<"

clean:
	rm -f build/*.o $(EXE)*
