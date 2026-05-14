BAUDRATE=115200
BIN=build
SRC=src
INC=include
SOURCES=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(BIN)/%.o, $(SOURCES))
CFLAGS=-mcpu=cortex-m0plus -O3 -ffreestanding -Iinclude
LDFLAGS=-T ldscript.ld -nostdlib

CC=arm-none-eabi-gcc
OBJCPY=arm-none-eabi-objcopy


all: bin

$(BIN):
	mkdir -p $(BIN)

$(BIN)/%.o: $(SRC)/%.c $(BIN)
	$(CC) $(CFLAGS) $< -c -o $@

elf: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN)/firmware.elf

bin: elf
	$(OBJCPY) -O binary $(BIN)/firmware.elf $(BIN)/firmware.bin

flash-erase:
	st-flash erase

flash: bin flash-erase
	st-flash --reset  write $(BIN)/firmware.bin 0x8000000


clean:
	rm -rf $(BIN)/*

