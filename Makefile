# Makefile for zxordle

TARGET = zxordle
SRC = zxordle.c

all: $(TARGET).P $(TARGET).O ${TARGET}.tap

$(TARGET).P: $(SRC)
	zcc +zx81 -vn -create-app -startup=2 -m -DAMALLOC -o ${TARGET}.bin ${SRC}
$(TARGET).O: $(SRC)
	zcc +zx80 -vn -create-app -m -DAMALLOC -o ${TARGET}.bin ${SRC}
$(TARGET).tap: $(SRC)
	zcc +zx -vn -lndos -DAMALLOC -startup=1 -pragma-define:CLIB_ZX_CONIO32=1 -pragma-define:CLIB_DEFAULT_SCREEN_MODE=0 -pragma-define:CLIB_CONIO_NATIVE_COLOUR=1 -o ${TARGET}.bin -create-app ${SRC}

clean:
	rm -f $(TARGET).map $(TARGET).bin $(TARGET).P $(TARGET).O ${TARGET}.tap