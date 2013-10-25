RUSTC				=	rustc
AS					=	nasm
LD					=	ld

HOST_ARCH			:=	$(shell uname -m)
ARCH				?=	$(HOST_ARCH)

TARGET				:=	$(ARCH)-elf-linux

RUSTCFLAGS			:=	--lib --target $(TARGET)
ASFLAGS				:=	-felf64
LDFLAGS				:=	-nodefaultlibs -Tsrc/linker.ld

KERNEL				:=	kiwios.bin
KERNEL_SRCS			:=	src/entry.rs
KERNEL_SRCS			+=	$(shell find arch/$(ARCH) -type f -name '*.S')
KERNEL_OBJS			:=	$(foreach src,$(KERNEL_SRCS),build/$(src).o)

all:				build $(KERNEL)

$(KERNEL):			$(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

build:
	mkdir build

build/%.rs.o:		%.rs
	@mkdir -p $(dir $@)
	$(RUSTC) $(RUSTCFLAGS) -c -o $@ $^

build/%.S.o:		%.S
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $^

clean:
	rm -rf build $(KERNEL)

.PHONY:				all clean
