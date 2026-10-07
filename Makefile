TARGETS := $(patsubst %.c, %, $(wildcard *.c))
TARGETS += $(patsubst %.cpp, %, $(wildcard *.cpp))

PERF := ../perf
CFLAGS := -O2 -g -fno-asynchronous-unwind-tables -fno-unwind-tables
CXXFLAGS := -O2 -g -fno-asynchronous-unwind-tables -fno-unwind-tables -Wno-volatile -Wno-unknown-warning-option

all: $(TARGETS)

test: $(TARGETS)
	@for T in $(filter flex_array%, $(TARGETS)); do \
		echo testing $$T; \
		$(PERF) mem record --all-user -- taskset -c 1 ./$$T 2>/dev/null; \
		$(PERF) report -s type,typeoff -Hn | grep flex_array; \
	done
	@for T in $(filter cplus_%, $(TARGETS)); do \
		echo testing $$T; \
		$(PERF) mem record --all-user -- taskset -c 1 ./$$T 2>/dev/null; \
		$(PERF) report -s type,typeoff -Hn | grep cplus; \
	done

cpp: $(TARGETS)
	@for T in $(filter cplus_%, $(TARGETS)); do \
		echo testing $$T; \
		$(PERF) mem record --all-user -- taskset -c 1 ./$$T 2>/dev/null; \
		$(PERF) report -s type,typeoff -Hn | grep cplus; \
	done

clean:
	rm -f $(TARGETS) perf.data*

