#!/usr/bin/env bash
set -euo pipefail

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
cmake_root_dir=$(cd "${script_dir}/.." && pwd)

if [[ $# -lt 1 ]]; then
	echo "Usage: $0 <preset>" >&2
	exit 2
fi

preset="$1"

echo "Project dir: ${cmake_root_dir}"

cd "${cmake_root_dir}" && cmake --preset "${preset}"
cmake --build --preset "${preset}"

case "${preset}" in
	install|install-debug)
		cmake --build --preset "${preset}" --target install
		;;
esac
