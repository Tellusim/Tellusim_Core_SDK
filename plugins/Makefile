ifndef PLUGINS

PLUGINS = \
	binding \
	formats \
	interface \
	network \
	parallel \
	platform \
	system

endif

MAKE = make
EXEC = $(TSROOT)/bin/ts_exec.sh

all:
	+@$(EXEC) -s "$(MAKE) -s -C @" $(PLUGINS)

run:
	+@$(EXEC) -s "$(MAKE) -s -C @ run" $(PLUGINS)

clean:
	+@$(EXEC) -p "$(MAKE) -s -C @ clean" $(PLUGINS)
