ifndef TESTS

TESTS = \
	core \
	format \
	geometry \
	graphics \
	interface \
	manual \
	math \
	parallel \
	platform \
	system

endif

MAKE = make
EXEC = $(TSROOT)/bin/ts_exec.sh

all:
	+@$(EXEC) -s "$(MAKE) -s -C @" $(TESTS)

run:
	+@$(EXEC) -s "$(MAKE) -s -C @ run" $(TESTS)

clean:
	+@$(EXEC) -p "$(MAKE) -s -C @ clean" $(TESTS)
