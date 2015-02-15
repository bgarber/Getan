MAKE=make
DIRS=tui

all:
	(for d in $(DIRS); do \
	    $(MAKE) -C $d)
	@echo "Alles fertig (i.e. \"everything done\")!"

clean:
	(for d in $(DIRS); do \
	    $(MAKE) -C $d clean)
	@echo "Alles fertig (i.e. \"everything done\")!"

.PHONY: all clean
