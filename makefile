SHELL := /bin/bash

GREEN := \033[0;32m
YELLOW := \033[1;33m
NC := \033[0m

C_SRCS   := $(wildcard */*.c)
CPP_SRCS := $(wildcard */*.cpp)

C_OUTS   := $(patsubst %.c,%.out,$(C_SRCS))
CPP_OUTS := $(patsubst %.cpp,%.out,$(CPP_SRCS))
ALL_OUTS := $(C_OUTS) $(CPP_OUTS)

.PHONY: all clean

all: $(ALL_OUTS)
	@echo "done"

%.out: %.c
	@printf "$(GREEN)compile $< -> $@$(NC)\n"
	gcc -o $@ $<
	@echo "  success"

%.out: %.cpp
	@printf "$(GREEN)compile $< -> $@$(NC)\n"
	g++ -o $@ $<
	@echo "  success"

clean:
	rm -f $(ALL_OUTS)