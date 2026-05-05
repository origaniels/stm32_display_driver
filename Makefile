BAUDRATE=115200
BIN=build
SRC=src
OBJS=$(BIN)/main.o $(BIN)/gpio.o $(BIN)/uart.o
CFLAGS=-mcpu=cortex-m0plus -O3 -ffreestanding
LDFLAGS=-T ldscript.ld -nostdlib

CC=arm-none-eabi-gcc
OBJCPY=arm-none-eabi-objcopy

all: bin

$(BIN):
	mkdir $(BIN)

$(BIN)/gpio.o: $(BIN)
	$(CC) $(CFLAGS) $(SRC)/gpio.c -c -o $(BIN)/gpio.o

$(BIN)/uart.o: $(BIN)
	$(CC) $(CFLAGS) $(SRC)/uart.c -c -o $(BIN)/uart.o

$(BIN)/main.o: $(BIN)
	$(CC) $(CFLAGS) $(SRC)/main.c -c -o $(BIN)/main.o

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

