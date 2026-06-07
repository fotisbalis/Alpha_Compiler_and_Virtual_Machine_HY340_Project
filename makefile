# Balis Fotios Marios csd4958

.PHONY: all compiler vm run clean clean_compiler clean_vm

all: compiler vm

compiler:
	$(MAKE) -C Compiler

vm:
	$(MAKE) -C VM

run:
ifndef TEST
	$(error Use 'make run TEST=[input file]')
endif
	rm -f alpha.abc
	./alpha_compiler $(TEST)
	@if [ -f alpha.abc ]; then \
		./alpha_vm alpha.abc; \
	fi

clean: clean_compiler clean_vm

clean_compiler:
	$(MAKE) -C Compiler clean

clean_vm:
	$(MAKE) -C VM clean
