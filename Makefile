CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGs =
SRCDIR = .
APPNAME = markdown_parser
OBJDIR = ./obj
BINDIR = ./bin

SOURCES := $(shell find $(SRCDIR) -name '*.c')
HEADERS := $(shell find $(SRCDIR) -name '*.h')
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: build

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(BINDIR))

# Build target
build: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(APPNAME) $^

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all build clean
