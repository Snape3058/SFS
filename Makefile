cc = g++

objs = ${patsubst %.c, %.o, $(wildcard *.c)}

sfs: $(objs)
	$(cc) $(objs) -g -o sfs

$(objs): %.o: %.c %.h structure.h
	$(cc) -c $< -o $@ -g

.PHONY: clean
clean: 
	rm *.o

.PHONY: rebuild
rebuild:
	rm *.o sfs; make

echo:
	@echo $(objs)
