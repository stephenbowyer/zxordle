# Makefile for zxordle

TARGET = zxordle
SRC = zxordle.c

all: $(TARGET).P $(TARGET).O

$(TARGET).P: $(SRC)
	zcc +zx81 -vn -create-app -startup=2 -m -DAMALLOC -o ${TARGET}.bin ${SRC}
$(TARGET).O: $(SRC)
	zcc +zx80 -vn -create-app -m -DAMALLOC -o ${TARGET}.bin ${SRC}

clean:
	rm -f $(TARGET).map $(TARGET).bin $(TARGET).P $(TARGET).O