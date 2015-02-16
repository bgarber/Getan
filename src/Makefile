MAKE:=make
DIRS:=getan

all:
	$(foreach d,$(DIRS),$(MAKE) -C $d)
	@echo "Alles fertig (i.e. \"everything done\")!"

clean:
	$(foreach d,$(DIRS),$(MAKE) -C $d clean)
	@echo "Alles fertig (i.e. \"everything done\")!"

.PHONY: all clean
