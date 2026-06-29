#!/usr/bin/env python3
import os
import re
import argparse

def update_file_header(file_path, dry_run=False):
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    # 提取文件名（不含路径）
    fname = os.path.basename(file_path)

    # 匹配最开头的 /* ... */ 注释块（可能跨多行）
    # 使用非贪婪匹配，但只匹配第一个注释块
    pattern = re.compile(r'(/\*.*?\*/)', re.DOTALL)
    match = pattern.search(content)
    if not match:
        print(f"警告：{file_path} 未找到注释块，跳过")
        return False

    comment_block = match.group(1)
    # 在注释块中寻找 " * File: ..." 行
    # 该行可能以多个空格或制表符开头，但通常有一个空格和星号
    file_line_pattern = re.compile(r'^(\s*\*\s*File:)\s*.*$', re.MULTILINE)
    if not file_line_pattern.search(comment_block):
        print(f"警告：{file_path} 注释块中没有 'File:' 行，跳过")
        return False

    # 替换该行，保留前面的缩进和 "* File:" 部分，只修改文件名部分
    new_comment = file_line_pattern.sub(r'\1 ' + fname, comment_block)

    # 如果注释没有变化，则跳过
    if new_comment == comment_block:
        print(f"跳过：{file_path} 的 File 行已经是正确的")
        return False

    # 替换原文件中的注释块
    new_content = content.replace(comment_block, new_comment)

    if dry_run:
        print(f"[预览] 将更新 {file_path} 的 File 行为: {fname}")
        return True
    else:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        print(f"已更新：{file_path}")
        return True

def main():
    parser = argparse.ArgumentParser(
        description="更新源文件头部注释中的 File: 字段为实际文件名。"
    )
    parser.add_argument(
        "root", nargs="?", default=".",
        help="要扫描的根目录（默认为当前目录）"
    )
    parser.add_argument(
        "--dry-run", "-n", action="store_true",
        help="仅显示将要执行的操作，不实际修改文件"
    )
    args = parser.parse_args()

    # 遍历所有子目录，找 .c 和 .cpp 文件
    for root, dirs, files in os.walk(args.root):
        for fname in files:
            if fname.endswith(('.c', '.cpp')):
                full_path = os.path.join(root, fname)
                update_file_header(full_path, args.dry_run)

if __name__ == "__main__":
    main()