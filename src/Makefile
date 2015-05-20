MAKE := make
DIRS := core getan

all: getan
	@echo "Alles fertig (i.e. \"everything done\")!"

getan: core
	$(MAKE) -C $@

core:
	$(MAKE) -C $@

clean:
	@$(foreach d,$(DIRS),$(shell $(MAKE) -C $d clean))
	@echo "Alles fertig (i.e. \"everything done\")!"

.PHONY: getan core clean

