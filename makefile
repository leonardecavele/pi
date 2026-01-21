# structure
NAME = kernel
BUILD = build
SRCS = srcs
OUT = boot
INCLUDES = includes

# flags
CC = aarch64-none-elf-gcc
LD = aarch64-none-elf-ld
OBJCOPY = aarch64-none-elf-objcopy

C_FLAGS = -I $(INCLUDES) \
		  -ffreestanding -nostdlib -nostartfiles \
		  -fno-omit-frame-pointer -fno-unwind-tables \
		  -fno-asynchronous-unwind-tables
S_FLAGS = -march=armv8-a
LD_FLAGS = -z max-page-size=4096 -Map $(MAP)

# files
S_SRCS = \
		 boot.s

C_SRCS = \
		 kmain.c \
		 uart.c \
		 pcie_scan.c

LD_SCRIPT = kernel.ld
IMG = $(OUT)/$(NAME).img
TMP = $(IMG).tmp
MAP = $(NAME).map
ELF = $(BUILD)/$(NAME).elf

S_OBJS = $(S_SRCS:%.s=$(BUILD)/%.o)
C_OBJS = $(C_SRCS:%.c=$(BUILD)/%.o)

# rules
all: $(IMG)

$(IMG): $(C_OBJS) $(S_OBJS) $(LD_SCRIPT)
	$(LD) -T $(LD_SCRIPT) -o $(ELF) $(S_OBJS) $(C_OBJS) $(LD_FLAGS)
	$(OBJCOPY) $(ELF) -O binary $(IMG)
	dd if=$(IMG) of=$(TMP) bs=512 conv=sync && mv $(TMP) $(IMG)

$(BUILD)/%.o: $(SRCS)/%.s
	mkdir -p $(BUILD)
	$(CC) -c $< -o $@ $(S_FLAGS)

$(BUILD)/%.o: $(SRCS)/%.c
	mkdir -p $(BUILD)
	$(CC) -c $< -o $@ $(C_FLAGS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(IMG) $(MAP)

re: fclean all

# miscellaneous
.PHONY: all clean fclean re
