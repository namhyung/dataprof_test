set quiet

default: build test

c_targets := shell('basename -s .c *.c | tr "\n" " "')
cpp_targets := shell('basename -s .cpp *.cpp | tr "\n" " "')

CC := 'gcc'
CXX := 'g++'
PERF := 'perf'
CFLAGS := "-O2 -g -fno-asynchronous-unwind-tables -fno-unwind-tables"
CPPFLAGS := ( "-O2 -g -fno-asynchronous-unwind-tables -fno-unwind-tables "
            + "-Wno-volatile -Wno-unknown-warning-option" )

build:
  for file in {{c_targets}}; do \
    echo {{CC}} {{CFLAGS}} -o $file $file.c; \
    {{CC}} {{CFLAGS}} -o $file $file.c; \
  done
  for file in {{cpp_targets}}; do \
    echo {{CXX}} {{CPPFLAGS}} -o $file $file.cpp; \
    {{CXX}} {{CPPFLAGS}} -o $file $file.cpp; \
  done

test: test-c test-cpp

test-c:
  for test in {{c_targets}}; do \
    echo testing $test; \
    {{PERF}} mem record --all-user -- taskset -c 1 ./$test 2>/dev/null; \
    {{PERF}} report -s typeoff -n | grep ok; \
  done

test-cpp:
  for test in {{cpp_targets}}; do \
    echo testing $test; \
    {{PERF}} mem record --all-user -- taskset -c 1 ./$test 2>/dev/null; \
    {{PERF}} report -s typeoff -n | grep ok; \
  done

clean:
  rm -f {{c_targets}} {{cpp_targets}}
  rm -f perf.data*
