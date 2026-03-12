#!/usr/bin/env bash
set -euo pipefail

repo_root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
cd "${repo_root}"

cmake --preset install
cmake --build --preset install
cmake --build --preset install --target install

echo "Portable artifacts generated in: ${repo_root}/SpectralDisplay"
