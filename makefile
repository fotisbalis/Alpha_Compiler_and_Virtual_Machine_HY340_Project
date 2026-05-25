# Balis Fotios Marios csd4958

.PHONY: all compiler vm clean clean_compiler clean_vm

all: compiler vm

compiler:
	$(MAKE) -C Compiler

vm:
	$(MAKE) -C VM

clean: clean_compiler clean_vm

clean_compiler:
	$(MAKE) -C Compiler clean

clean_vm:
	$(MAKE) -C VM clean
