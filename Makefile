TARGETS := flex_array1 flex_array2 flex_array3 flex_array4 flex_array5 flex_array6 flex_array7 flex_array8

CFLAGS := -O2 -g -fno-asynchronous-unwind-tables -fno-unwind-tables

all: $(TARGETS)

test: $(TARGETS)
	../perf mem record taskset -c 1 ./flex_array1
	../perf report -s type,typeoff,symoff -Hn | grep flex_array
	../perf mem record taskset -c 1 ./flex_array2
	../perf report -s type,typeoff,symoff -Hn | grep flex_array
	../perf mem record taskset -c 1 ./flex_array3
	../perf report -s type,typeoff,symoff -Hn | grep flex_array
	../perf mem record taskset -c 1 ./flex_array4
	../perf report -s type,typeoff,symoff -Hn | grep flex_array
	../perf mem record taskset -c 1 ./flex_array5
	../perf report -s type,typeoff,symoff -Hn | grep flex_array
	../perf mem record taskset -c 1 ./flex_array6
	../perf report -s type,typeoff,symoff -Hn | grep flex_array
	../perf mem record taskset -c 1 ./flex_array7
	../perf report -s type,typeoff,symoff -Hn | grep flex_array
	../perf mem record taskset -c 1 ./flex_array8
	../perf report -s type,typeoff,symoff -Hn | grep flex_array

clean:
	rm -f $(TARGETS) perf.data*

