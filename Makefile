RUSTC				=	rustc
AS					=	nasm
LD					=	ld

HOST_ARCH			:=	$(shell uname -m)
ARCH				?=	$(HOST_ARCH)

TARGET				:=	$(ARCH)-elf-linux

RUSTCFLAGS			:=	--lib --target $(TARGET) --opt-level=3
ASFLAGS				:=	-felf64
LDFLAGS				:=	-nodefaultlibs -Tsrc/linker.ld

KERNEL				:=	kiwios.bin
KERNEL_SRCS			:=	src/entry.rs
KERNEL_SRCS			+=	$(shell find arch/$(ARCH) -type f -name '*.S')
KERNEL_OBJS			:=	$(foreach src,$(KERNEL_SRCS),build/$(src).o)
KERNEL_DEPS			:=	$(shell find src -type f -name '*.rs')

all:				build $(KERNEL)

$(KERNEL):			$(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(KERNEL_OBJS)

build:
	mkdir build

build/%.rs.o:		%.rs $(KERNEL_DEPS)
	@mkdir -p $(dir $@)
	$(RUSTC) $(RUSTCFLAGS) -c -o $@ $<

build/%.S.o:		%.S
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $^

clean:
	rm -rf build $(KERNEL)

.PHONY:				all clean
