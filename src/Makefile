MAKE := make
DIRS := core getan

all:
	$(foreach d,$(DIRS), $(MAKE) -C $(d))
	@echo "Alles fertig (i.e. \"everything done\")!"

.PHONY:
clean:
	$(foreach d,$(DIRS),$(MAKE) -C $d clean)
	@echo "Alles fertig (i.e. \"everything done\")!"

