PROGRAM = plagiarismFinder
ARGUMENTS = data/lorem.txt data/lorem2.txt

CXX = g++
CXXFLAGS = -pedantic -Wall -Wextra -std=c++11 -ggdb -Iinclude

LD = g++
LDFLAGS = -lm

CFILES = $(wildcard src/*.cpp)
OFILES = $(CFILES:src/%.cpp=obj/%.o)

all: clean depend $(PROGRAM) run

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(PROGRAM): $(OFILES)
	$(LD) -o $@ $(OFILES) $(LDFLAGS)

.PHONY: all clean

clean:
	rm -f $(OFILES) $(PROGRAMS)

run: $(PROGRAM)
	./$(PROGRAM) $(ARGUMENTS)

debug: $(PROGRAM)
	gdb $(PROGRAM) $(ARGUMENTS)

DEPENDFILE = .depend

depend:
	$(CXX) $(CXXFLAGS) -MM $(CFILES) > $(DEPENDFILE)

-include $(DEPENDFILE)
