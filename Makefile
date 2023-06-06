CC := g++
SRCDIR := src
TSTDIR := tests
OBJDIR := build
BINDIR := bin

MAIN := src/main.cpp

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
MAIN_OBJECTS := $(filter-out $(OBJDIR)/tester.o,$(OBJECTS))
TESTER_OBJECTS := $(filter-out $(OBJDIR)/main.o,$(OBJECTS))
TSTSOURCES := $(shell find $(TSTDIR) -type f -name *.$(SRCEXT))

# -g debug, --coverage cobertura
CFLAGS := -g --coverage -Wall -O3 -std=c++20
LIBS := -lcurl
INC := -I include/

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

main: $(MAIN_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $^ -o $(BINDIR)/main $(LIBS)

tests: $(TESTER_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(INC) $(TSTSOURCES) $^ -o $(BINDIR)/tester $(LIBS)

all: main

clean:
	$(RM) -r $(OBJDIR)/* $(BINDIR)/* coverage/* *.gcda *.gcno

.PHONY: clean