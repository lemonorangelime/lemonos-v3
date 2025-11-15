MAKE := make

OUTPUT_IMG := x86-64_lemonos.iso
OUTPUT_IMG := x86_lemonos.iso

QEMU := qemu-system-x86_64
QEMUFLAGS := -cpu host --enable-kvm -vga std -machine acpi=on -boot dca -m 5g -serial stdio

default: default

qemu: qemu_x86_64

qemu_x86:
	$(QEMU) $(QEMUFLAGS) -net nic,model=rtl8139,netdev=rtl8139 -netdev user,id=rtl8139 -drive file=x86_lemonos.iso,index=0,media=disk,format=raw

qemu_x86_64:
	$(QEMU) $(QEMUFLAGS) -net nic,model=rtl8139,netdev=rtl8139 -netdev user,id=rtl8139 -drive file=x86-64_lemonos.iso,index=0,media=disk,format=raw

%:
	make -f Makefile_x86-64 $@
	make -f Makefile_x86 $@
