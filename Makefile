RPI_VERSION ?= 4

BOOTMNT ?= /media/andre/boot

ARMGNU ?= aarch64-linux-gnu

# -g enables debugging
COPS = -DRPI_VERSION=$(RPI_VERSION) -Wall -nostdlib -nostartfiles -ffreestanding \
	   -Iinclude -mgeneral-regs-only -g -Wextra

ASMOPS = -Iinclude

ARMSTUB_BUILD_DIR = armstub/build
BUILD_DIR = build
SRC_DIR = src

all : kernel8.img

clean : 
	rm -rf $(BUILD_DIR) *.img *.bin

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	@echo "Building for RPI $(value RPI_VERSION)"
	@echo "Deploy to $(value BOOTMNT)"
	@echo ""
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img

ifeq ($(RPI_VERSION), 4)
	cp kernel8.img $(BOOTMNT)/kernel8-rpi4.img
else
	cp kernel8.img $(BOOTMNT)/
endif
	cp config.txt $(BOOTMNT)/
	sync


$(ARMSTUB_BUILD_DIR)/armstub_s.o: armstub/src/armstub.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

armstub: $(ARMSTUB_BUILD_DIR)/armstub_s.o
	$(ARMGNU)-ld --section-start=.text=0 -o $(ARMSTUB_BUILD_DIR)/armstub.elf $(ARMSTUB_BUILD_DIR)/armstub_s.o
	$(ARMGNU)-objcopy $(ARMSTUB_BUILD_DIR)/armstub.elf -O binary armstub-new.bin
	cp armstub-new.bin $(BOOTMNT)/
	sync