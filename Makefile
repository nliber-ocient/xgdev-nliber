########################################################################
# Smart pointer exercise makefile
########################################################################
# Build the source four ways...with and without -DUSE_STD and with and
# without -DDEBUG
########################################################################

CXXFLAGS = -std=c++14 -Wall -g  -fsanitize=address

PROGRAMS = thing_std_debug thing_std thing_debug thing

all: $(PROGRAMS)

thing_std_debug: main.cpp debug.h
	$(CXX) $(CXXFLAGS) -DUSE_STD -DDEBUG -o $@ $<

thing_std: main.cpp debug.h
	$(CXX) $(CXXFLAGS) -DUSE_STD -o $@ $<


thing_debug: main.cpp debug.h smart_pointers.h
	$(CXX) $(CXXFLAGS) -DDEBUG -o $@ $<

thing: main.cpp debug.h smart_pointers.h
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm $(PROGRAMS)






