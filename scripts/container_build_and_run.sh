#!/usr/bin/env bash
set -euo pipefail

repo_root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
cd "${repo_root}/container"

mode="${1:-gui}"

is_running_in_docker() {
  [[ -f "/.dockerenv" ]] || grep -qaE "docker|containerd" /proc/1/cgroup 2>/dev/null
}

show_help() {
  cat <<'EOF'
Usage:
  ./scripts/container_build_and_run.sh [gui|install]

Modes:
  gui      Build image and run interactive GUI container shell (default)
  install  Build image and run install profile (creates SpectralDisplay)
EOF
}

case "${mode}" in
  -h|--help)
    show_help
    exit 0
    ;;
  gui)
    if ! command -v docker >/dev/null 2>&1; then
      if is_running_in_docker; then
        echo "[container] Docker CLI is not available inside container. Running GUI build directly in this container..."
        exec ./run_in_container.sh
      fi
      echo "[container] Error: docker command not found on host." >&2
      echo "Install Docker Engine and Docker Compose plugin, then re-run this script." >&2
      exit 127
    fi
    echo "[container] Building image..."
    docker compose build
    echo "[container] Starting interactive container shell..."
    echo "If you need X11 access, run on host first: xhost +local:docker"
    docker compose run --rm spectral-display-gui bash
    ;;
  install)
    if ! command -v docker >/dev/null 2>&1; then
      if is_running_in_docker; then
        echo "[container] Docker CLI is not available inside container. Running install profile directly in this container..."
        exec ./run_install_in_container.sh
      fi
      echo "[container] Error: docker command not found on host." >&2
      echo "Install Docker Engine and Docker Compose plugin, then re-run this script." >&2
      exit 127
    fi
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
