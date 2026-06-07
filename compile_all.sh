#!/bin/bash

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"

GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

for dir in "$ROOT_DIR"/*/; do
    [ -d "$dir" ] || continue

    cd "$dir" || continue

    for cfile in *.c; do
        [ -f "$cfile" ] || continue

        base="${cfile%.c}"
        outfile="${base}.out"

        if [ -f "$outfile" ]; then
            echo -e "${YELLOW}overlook $dir$outfile (existed)${NC}"
            continue
        fi

        echo -e "${GREEN}compile $dir$cfile -> $outfile${NC}"
        gcc -o "$outfile" "$cfile"

        if [ $? -eq 0 ]; then
            echo "  success"
        else
            echo "  fail"
        fi
    done

    cd "$ROOT_DIR" || exit
done

echo "done"