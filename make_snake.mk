#MACROS
TARGET_C = main.c lcd0.c uart0.c
TARGET_O = main.o lcd0.o uart0.o
TARGET_E = snake.elf
TARGET_H = snake.hex
TARGET_F = flash:w:snake.hex:i

compile:
	rm -f *.o *.elf *.hex
	avr-gcc -g -Os -mmcu=atmega128 -c $(TARGET_C)
	avr-gcc -g -mmcu=atmega128 -o $(TARGET_E) $(TARGET_O)
	avr-objcopy -j .text -j .data -O ihex $(TARGET_E) $(TARGET_H)
	cat $(TARGET_H)
	echo "$(tput setaf 2)Compiled OK"

flash:
	sudo avrdude -p m128 -c jtagmkI -P /dev/ttyUSB0 -U $(TARGET_F)


	
