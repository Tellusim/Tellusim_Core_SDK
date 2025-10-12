TOOLS = \
	blob \
	image \
	mesh \
	noise \
	project \
	shader

MAKE = make
EXEC = $(TSROOT)/bin/ts_exec.sh

all:
	+@$(EXEC) -s "$(MAKE) -s -C @" $(TOOLS)

install:
	+@$(EXEC) "$(MAKE) -s -C @ install" $(TOOLS)

clean:
	+@$(EXEC) -p "$(MAKE) -s -C @ clean" $(TOOLS)
