CC=gcc
CFLAGS=-fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin \
       -O -m32 -I./inc -Wextra -Wall
LDFLAGS=-m elf_i386
LDSCRIPT=link.ld
NASM=nasm
NASMFLAGS=-f elf
SOURCES=kernel.c system.c
OBJECTS=$(SOURCES:.c=.o)
ASM=kernel_start.asm
ASMOBJ=$(ASM:.asm=.o)
BIN=kernel.bin

all: $(ASM) $(SOURCES) $(BIN)

$(BIN): $(ASMOBJ) $(OBJECTS) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -T $(LDSCRIPT) -o $@ $(ASMOBJ) $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ASMOBJ): %.o: %.asm
	$(NASM) $(NASMFLAGS) -o $@ $<

print:
	echo $(ASMOBJ)

clean:
	rm -f *.o $(BIN)
