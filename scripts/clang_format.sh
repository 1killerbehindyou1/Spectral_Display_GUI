#!/usr/bin/env bash
set -euo pipefail

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo_root=$(cd "${script_dir}/.." && pwd)

mode="apply"
show_help=false

declare -a input_paths=()

while [[ $# -gt 0 ]]; do
    case "$1" in
        --check)
            mode="check"
            shift
            ;;
        --apply)
            mode="apply"
            shift
            ;;
        -h|--help)
            show_help=true
            shift
            ;;
        *)
            input_paths+=("$1")
            shift
            ;;
    esac
done

if [[ "${show_help}" == true ]]; then
    cat <<'EOF'
Usage:
  ./scripts/format.sh [--apply|--check] [path ...]

Options:
  --apply   Format files in place (default)
  --check   Check formatting only (non-zero exit if formatting is needed)
  -h, --help  Show this help

Notes:
  - Uses repository .clang-format style.
  - If no paths are provided, searches: main tests utils
  - Excludes: build/ and depend/
EOF
    exit 0
fi

if ! command -v clang-format >/dev/null 2>&1; then
    echo "Error: clang-format is not installed or not in PATH." >&2
    exit 127
fi

if [[ ${#input_paths[@]} -eq 0 ]]; then
    input_paths=(main tests utils)
fi

declare -a search_paths=()
for p in "${input_paths[@]}"; do
    if [[ "$p" = /* ]]; then
        search_paths+=("$p")
    else
        search_paths+=("${repo_root}/$p")
    fi
done

declare -a files=()
while IFS= read -r -d '' file; do
    files+=("$file")
done < <(
    find "${search_paths[@]}" -type f \( \
        -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.cxx" -o \
        -name "*.h" -o -name "*.hh" -o -name "*.hpp" -o -name "*.hxx" \) \
        ! -path "${repo_root}/build/*" \
        ! -path "${repo_root}/depend/*" \
        ! -path "${repo_root}/.git/*" \
        -print0
)

if [[ ${#files[@]} -eq 0 ]]; then
    echo "No C/C++ source files found in selected paths."
    exit 0
fi

if [[ "$mode" == "check" ]]; then
    echo "Checking formatting for ${#files[@]} files..."
    clang-format -style=file -n --Werror "${files[@]}"
    echo "Formatting check passed."
else
    echo "Formatting ${#files[@]} files..."
    clang-format -style=file -i "${files[@]}"
    echo "Formatting complete."
fi
