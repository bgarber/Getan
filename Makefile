PROGRAM=awte

all:
	make -C src all
	cp src/${PROGRAM} .

.PHONY:
clean:
	make -C src clean
	rm ${PROGRAM}
