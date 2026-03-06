#!/usr/bin/env bash
set -euo pipefail

repo_root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
cd "${repo_root}/container"

mode="${1:-gui}"

show_help() {
  cat <<'EOF'
Usage:
  ./scripts/container_build_and_run.sh [gui|install]

Modes:
  gui      Build image and run interactive GUI container shell (default)
  install  Build image and run install profile (creates GUI_portable)
EOF
}

case "${mode}" in
  -h|--help)
    show_help
    exit 0
    ;;
  gui)
    echo "[container] Building image..."
    docker compose build
    echo "[container] Starting interactive container shell..."
    echo "If you need X11 access, run on host first: xhost +local:docker"
    docker compose run --rm spectral-display-gui bash
    ;;
  install)
    echo "[container] Building image..."
    docker compose build
    echo "[container] Running install profile..."
    docker compose --profile install run --rm spectral-display-install
    ;;
  *)
    echo "Unknown mode: ${mode}" >&2
    show_help >&2
    exit 2
    ;;
esac
