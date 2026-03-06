#!/usr/bin/env bash
set -euo pipefail

script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo_root=$(cd "${script_dir}/.." && pwd)
install_root="${repo_root}/build/install"
app_path="${install_root}/bin/BasicGUI"

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then
  cat <<'EOF'
Usage:
  ./scripts/run_portable.sh [-- <app args...>]

Runs the installed portable app from build/install with local Qt runtime paths.
Expected install layout:
  build/install/bin/BasicGUI
  build/install/lib
  build/install/plugins
  build/install/qml
EOF
  exit 0
fi

if [[ ! -x "${app_path}" ]]; then
  echo "Error: ${app_path} not found or not executable." >&2
  echo "Build and install first:" >&2
  echo "  cmake --preset install && cmake --build --preset install && cmake --build --preset install --target install" >&2
  exit 1
fi

prepend_path_var() {
  local var_name="$1"
  local new_path="$2"
  local current_value="${!var_name:-}"
  if [[ -z "${current_value}" ]]; then
    printf -v "${var_name}" '%s' "${new_path}"
  else
    printf -v "${var_name}" '%s:%s' "${new_path}" "${current_value}"
  fi
  export "${var_name}"
}

prepend_path_var LD_LIBRARY_PATH "${install_root}/lib"
prepend_path_var QT_PLUGIN_PATH "${install_root}/plugins"
prepend_path_var QML2_IMPORT_PATH "${install_root}/qml"
prepend_path_var QML_IMPORT_PATH "${install_root}/qml"

export QT_QPA_PLATFORM_PLUGIN_PATH="${install_root}/plugins/platforms"

if [[ "${1:-}" == "--" ]]; then
  shift
fi

exec "${app_path}" "$@"
