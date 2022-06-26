BUILD := build
K := kernel
U := user


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
QEMU_LINUX := qemu-riscv64

OBJS := \
	$K/entry.o \
	$K/start.o \
	$K/link_app.o \
	$K/main.o \
	$K/log.o \
	$K/trap.o \
	$K/printf.o \
	$K/uart.o \
	$K/string.o \
	$K/math.o \
	$K/console.o \
	$K/pretrap.o \
	$K/batch.o \
	$K/syscall.o


BIN_OBJS := \
	$U/power3.o \
	$U/power5.o \
	$U/power7.o \
	$U/sleep.o

BIN_REQUIRED_OBJS := \
	$U/start.o \
	$U/string.o \
	$U/printf.o \
	$U/syscall.o \
	$U/start_globl.o

KERNEL_ENTRY_PA := 0x80000000

QEMUOPTS := -machine virt \
	-bios none \
	-m 128M \
	-nographic \
	-device loader,file=$(OUTPUT_BIN),addr=$(KERNEL_ENTRY_PA)

CFLAGS = -O -fno-omit-frame-pointer -ggdb
CFLAGS += -mabi=lp64d -march=rv64gc
CFLAGS += -MD
CFLAGS += -mcmodel=medany
CFLAGS += -ffreestanding -fno-common -nostdlib -mno-relax
# CFLAGS += --verbose

GDBOPTS := -ex 'file $(OUTPUT_KERNEL)' \
	-ex 'set arch riscv:rv64' \
	-ex 'target remote localhost:1234'

%.o : %.c
	@$(GCC) -Wall -Werror -c $(CFLAGS) $< -o $@

%.o : %.s
	@$(AS) -mabi=lp64d -march=rv64gc $< -o $@

user/%.o : user/%.c
	@$(GCC) -c $(CFLAGS) $< -o $@

.PHONY: build
build: $(OBJS)
	@mkdir -p build
	$(LD) -T $(LD_SCRIPT) $(OBJS) -o $(OUTPUT_KERNEL)
	$(OBJCOPY) --strip-all $(OUTPUT_KERNEL) -O binary $(OUTPUT_BIN)

.PHONY: run
run:
	@make build-bin
	@make build
	$(QEMU) $(QEMUOPTS)

.PHONY: gdbserver
gdbserver:
	@make build-bin
	@make build
	$(QEMU) $(QEMUOPTS) -s -S

.PHONY: gdbclient
gdbclient:
	$(GDB) $(GDBOPTS)

.PHONY: clean
clean:
	rm -f $K/*.o $K/*.d $(BUILD)/* $U/*.o $U/*.d *.o *.d *.s

.PHONY: rundemo
rundemo:
	$(GCC) $(CFLAGS) demo/syscall.c -o start
	$(QEMU_LINUX) start

.PHONY: build-bin
build-bin: $(BIN_REQUIRED_OBJS) $(BIN_OBJS)
	go run user/build.go

	$(foreach obj,$(BIN_OBJS),\
		$(OBJCOPY) --strip-all $(patsubst $U/%.o,$(BUILD)/%,$(obj)) -O binary $(patsubst $U/%.o,$(BUILD)/%.bin,$(obj)); \
	)