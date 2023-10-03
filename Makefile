CXX := g++-11
TIDY := clang-tidy
CXX_STANDARD := 17

BINARIES := test-suite

all: ${BINARIES}

library.o: library.cpp library.h
	${CXX} -O2 -std=c++${CXX_STANDARD} -c $< -o $@ -Wall -Wextra -Wpedantic


%.o: %.cpp %.h
	${CXX} -std=c++${CXX_STANDARD} -c $< -o $@ -w

%.o: %.cpp
	${CXX} -std=c++${CXX_STANDARD} -c $< -o $@ -w

test-suite: catch.o library.o test-suite.o
	${CXX} -std=c++${CXX_STANDARD} $^ -o $@ -Wall -Wextra -Wpedantic

analyze:
	@${CXX} -O3 -std=c++${CXX_STANDARD} -c library.cpp -Wall -Wextra -fanalyzer -Wno-analyzer-possible-null-argument -Wno-analyzer-possible-null-dereference

guidelines:
	@${TIDY} -checks=cppcoreguidelines-*,clang-analyzer-* library.cpp -- -O2 -std=c++${CXX_STANDARD}

test: test-suite
	@./test-suite

clean:
	rm -rf *.o ${BINARIES} *~
