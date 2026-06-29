SHELL := /bin/bash

GREEN := \033[0;32m
YELLOW := \033[1;33m
NC := \033[0m

DIRS := $(foreach d,$(patsubst %/,%,$(wildcard */)),$(if $(wildcard $(d)/*.c $(d)/*.cpp),$(d),))
ALL_OUTS := $(foreach dir,$(DIRS),$(dir)/$(notdir $(dir)).out)

.PHONY: all clean

all: $(ALL_OUTS)
	@echo "done"

define compile_rule
$(1)/$(notdir $(1)).out: $$(shell ls -v $(1)/*.c $(1)/*.cpp 2>/dev/null | tail -1)
	@printf "$$(GREEN)compile $$< -> $$@$$(NC)\n"
	$$(if $$(filter %.c,$$<),gcc,g++) -o $$@ $$<
	@echo "  success"
endef

$(foreach dir,$(DIRS),$(eval $(call compile_rule,$(dir))))

clean:
	rm -f $(ALL_OUTS)