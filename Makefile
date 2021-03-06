# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  FloodIt_config = debug
  Tests_config = debug
endif
ifeq ($(config),release)
  FloodIt_config = release
  Tests_config = release
endif

PROJECTS := FloodIt Tests

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

FloodIt:
ifneq (,$(FloodIt_config))
	@echo "==== Building FloodIt ($(FloodIt_config)) ===="
	@${MAKE} --no-print-directory -C . -f FloodIt.make config=$(FloodIt_config)
endif

Tests:
ifneq (,$(Tests_config))
	@echo "==== Building Tests ($(Tests_config)) ===="
	@${MAKE} --no-print-directory -C . -f Tests.make config=$(Tests_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f FloodIt.make clean
	@${MAKE} --no-print-directory -C . -f Tests.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   FloodIt"
	@echo "   Tests"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"

doxygen:
	doxygen
