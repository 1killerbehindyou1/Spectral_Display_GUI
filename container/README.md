# Container setup (Docker)

Ten katalog zawiera konfigurację kontenera do budowy i uruchamiania aplikacji Qt/QML.

## 1) Build obrazu

```bash
cd container
docker compose build
```

Alternatywnie (z katalogu repo):

```bash
./scripts/container_build_and_run.sh gui
```

## 2) Zezwól kontenerowi na GUI (X11)

Na hoście:

```bash
xhost +local:docker
```

## 3) Uruchom kontener

```bash
cd container
docker compose run --rm spectral-display-gui bash
```

## 4) Build i start aplikacji w kontenerze

W środku kontenera:

```bash
./container/run_in_container.sh
```

## 5) Portable install (`GUI_portable`) przez profil compose

Na hoście:

```bash
cd container
docker compose --profile install run --rm spectral-display-install
```

Alternatywnie (z katalogu repo):

```bash
./scripts/container_build_and_run.sh install
```

Wynik:

- `GUI_portable/` w katalogu głównym repozytorium
- `GUI_portable/spectral_display_portable.tar.gz`

## 6) Cofnięcie uprawnień X11 (opcjonalnie)

Na hoście:

```bash
xhost -local:docker
```

## Uwagi

- Repozytorium jest montowane jako wolumen do `/workspace`.
- GUI jest wyświetlane przez X11 hosta (`DISPLAY`, `/tmp/.X11-unix`).
- Konfiguracja używa istniejących presetów CMake z repo.
