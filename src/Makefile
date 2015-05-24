MAKE := make

all: getan
	@echo "Alles fertig (i.e. \"everything done\")!"

getan: core
	$(MAKE) -C $@

core:
	$(MAKE) -C $@

clean:
	$(MAKE) -C core clean
	$(MAKE) -C getan clean
	@echo "Alles fertig (i.e. \"everything done\")!"

.PHONY: getan core clean

