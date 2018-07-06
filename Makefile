cc = g++
clang = clang++

objs = ${patsubst %.c, %.o, $(wildcard *.c)}
lls = ${patsubst %.c, %.ll, $(wildcard *.c)}

.PHONY: all
all: sfs sfs.ll

sfs: $(objs)
	$(cc) $(objs) -g -o sfs

$(objs): %.o: %.c %.h structure.h
	$(cc) -c $< -o $@ -g

sfs.ll: $(lls)
	llvm-link -S -o sfs.ll $(lls)

$(lls): %.ll: %.c %.h structure.h
	$(clang) -emit-llvm -S -o $@ $<

.PHONY: clean
clean:
	rm -f *.o *.ll sfs
