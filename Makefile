TARGETS := $(patsubst %.c, %, $(wildcard *.c))

PERF := ../perf
CFLAGS := -O2 -g -fno-asynchronous-unwind-tables -fno-unwind-tables

all: $(TARGETS)

test: $(TARGETS)
	@for T in $(filter flex_array%, $(TARGETS)); do \
		echo testing $$T; \
		$(PERF) mem record -- taskset -c 1 ./$$T 2>/dev/null; \
		$(PERF) report -s type,typeoff -Hn | grep flex_array; \
	done

clean:
	rm -f $(TARGETS) perf.data*

