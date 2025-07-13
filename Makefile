# Makefile for zxordle

TARGET = zxordle
SRC = zxordle.c

all: $(TARGET).P

$(TARGET).P: $(SRC)
	zcc +zx81 -vn -create-app -lm81_tiny -m -DAMALLOC -o ${TARGET}.bin ${SRC}

clean:
	rm -f $(TARGET).map $(TARGET).bin $(TARGET).P