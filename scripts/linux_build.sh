#!/usr/bin/env bash
set -euo pipefail

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cmake_root_dir=$(cd "${script_dir}/.." && pwd)

if [[ $# -lt 1 || "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
	echo "Usage: $0 <preset>" >&2
	echo "Available presets: debug, release, ut, benchmark, doxygen, install" >&2
	exit 2
fi

preset="$1"

echo "Project dir: ${cmake_root_dir}"

cd "${cmake_root_dir}" && cmake --preset "${preset}"
cmake --build --preset "${preset}"

case "${preset}" in
	install)
		cmake --build --preset "${preset}" --target install
		;;
esac
