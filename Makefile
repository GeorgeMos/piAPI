CFILES = $(wildcard *.c include/*.c kernel/*.c)
SFILES = $(wildcard boot/*.S include/*.S kernel/*.S)
OFILES = $(CFILES:.c=.o) $(SFILES:.S=.o)
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
GCCPATH = /home/george/Documents/gcc-arm-11.2-2022.02-x86_64-aarch64-none-elf/bin


all: clean kernel8.img

%.o: %.c
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

%.o: %.S
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: $(OFILES)
	$(GCCPATH)/aarch64-none-elf-ld -nostdlib $(OFILES) -T boot/link.ld -o kernel8.elf
	$(GCCPATH)/aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm kernel8.elf */*.o *.img > /dev/null 2> /dev/null || true