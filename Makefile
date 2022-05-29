BUILD := build
K := kernel

LD_SCRIPT := $K/kernel.ld
OUTPUT_KERNEL := $(BUILD)/kernel
OUTPUT_BIN := $(BUILD)/kernel.bin

CROSS_COMPILE := riscv64-unknown-elf-

GCC := $(CROSS_COMPILE)gcc
GDB := $(CROSS_COMPILE)gdb
AS := $(CROSS_COMPILE)as
LD := $(CROSS_COMPILE)ld
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
NM := $(CROSS_COMPILE)nm

QEMU := qemu-system-riscv64

OBJS := \
	$K/entry.o \
	$K/start.o 

KERNEL_ENTRY_PA := 0x80000000

QEMUOPTS := -machine virt \
	-bios none \
	-m 128M \
	-nographic \
	-device loader,file=$(OUTPUT_BIN),addr=$(KERNEL_ENTRY_PA)

CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb
CFLAGS += -mabi=lp64d -march=rv64gc
CFLAGS += -MD
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
# CFLAGS += --verbose

GDBOPTS := -ex 'file $(OUTPUT_KERNEL)' \
	-ex 'set arch riscv:rv64' \
	-ex 'target remote localhost:1234'

%.o : %.c
	@$(GCC) -c $(CFLAGS) $< -o $@

%.o : %.s
	@$(AS) -mabi=lp64d -march=rv64gc $< -o $@

.PHONY: build
build: $(OBJS)
	@mkdir -p build
	$(LD) -T $(LD_SCRIPT) $(OBJS) -o $(OUTPUT_KERNEL)
	$(OBJCOPY) --strip-all $(OUTPUT_KERNEL) -O binary $(OUTPUT_BIN)

.PHONY: run
run:
	@make build
	$(QEMU) $(QEMUOPTS)

.PHONY: gdbserver
gdbserver:
	@make build
	$(QEMU) $(QEMUOPTS) -s -S

.PHONY: gdbclient
gdbclient:
	$(GDB) $(GDBOPTS)

.PHONY: clean
clean:
	rm -f $K/*.o $(BUILD)/*