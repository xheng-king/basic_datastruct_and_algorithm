# 使用 Bash 作为 Shell，以支持颜色输出
SHELL := /bin/bash

# 定义颜色（与你的脚本保持一致）
GREEN := \033[0;32m
YELLOW := \033[1;33m
NC := \033[0m

# 1. 自动收集所有一级子目录下的 .c 和 .cpp 文件
C_SRCS   := $(wildcard */*.c)
CPP_SRCS := $(wildcard */*.cpp)

# 2. 将源文件路径映射为对应的 .out 目标文件路径
C_OUTS   := $(patsubst %.c,%.out,$(C_SRCS))
CPP_OUTS := $(patsubst %.cpp,%.out,$(CPP_SRCS))
ALL_OUTS := $(C_OUTS) $(CPP_OUTS)

# 3. 声明伪目标（不代表实际文件）
.PHONY: all clean

# 默认目标：编译所有找到的源文件
all: $(ALL_OUTS)
	@echo "done"

# 4. 通用编译规则：如何将任意目录下的 .c 编译为同目录的同名 .out
%.out: %.c
	@printf "$(GREEN)compile $< -> $@$(NC)\n"
	gcc -o $@ $<
	@echo "  success"

# 5. 通用编译规则：如何将任意目录下的 .cpp 编译为同目录的同名 .out
%.out: %.cpp
	@printf "$(GREEN)compile $< -> $@$(NC)\n"
	g++ -o $@ $<
	@echo "  success"

# 6. 清理目标：删除所有编译出的 .out 文件
clean:
	rm -f $(ALL_OUTS)