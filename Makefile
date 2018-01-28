EXECNAME?=main

VERSION="1.0"

CC=cc
CFLAGS+=-Wall -Wextra -std=c99 -pedantic -D_PROJECT_VERSION=$(VERSION) -Iinclude

CXX=g++
CXXFLAGS+=-Wall -Wextra -std=gnu++11 -pedantic -D_PROJECT_VERSION=$(VERSION) -Iinclude

LIBS+=
LDFLAGS+=
LD=$(CXX)

RM=rm

OBJS+=src/main.o \
src/vmpage.o \

.PHONY: all clean run ee bee
# Warning: `ee' and `bee' targets are debug ones, do not use on production!

# Production .PHONY targets
all: $(EXECNAME)

clean:
	$(RM) -fv $(OBJS) $(EXECNAME)

run: $(EXECNAME)
	./$(EXECNAME)

# Debug .PHONY targets
ee: clean run
bee: clean all

# Not .PHONY targets
$(EXECNAME): $(OBJS)
	$(LD) $(LDFLAGS) $(LIBS) $(OBJS) -o $(EXECNAME)
