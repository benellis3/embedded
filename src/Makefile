EXE = hash-table
SRC = $(wildcard *.c)
OBJS = $(addprefix build/,$(SRC:.c=.o))

all: $(EXE)

$(EXE): $(OBJS)
		gcc -o $(EXE) $(OBJS)

build/%.o: %.c
		gcc -O3 -Wall -c -o "$@" "$<"

clean:
	rm -f build/*.o $(EXE)*
