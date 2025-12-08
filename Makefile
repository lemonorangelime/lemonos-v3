ifeq ($(ARCH),)
	ARCH := x86-64
endif

MAKE := make

QEMUFLAGS := -boot dca -serial stdio

default: default

%:
	@for file in "Makefile_"$(ARCH); do \
		make -f $$file $@; \
	done; \

