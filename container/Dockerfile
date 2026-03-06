FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    gpg \
    lsb-release \
    && mkdir -p /etc/apt/keyrings \
    && curl -fsSL https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor -o /etc/apt/keyrings/kitware.gpg \
    && echo "deb [signed-by=/etc/apt/keyrings/kitware.gpg] https://apt.kitware.com/ubuntu/ $(. /etc/os-release && echo ${VERSION_CODENAME}) main" > /etc/apt/sources.list.d/kitware.list \
    && apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    git \
    pkg-config \
    qtbase5-dev \
    qtdeclarative5-dev \
    qtquickcontrols2-5-dev \
    qml-module-qtquick-window2 \
    qml-module-qtquick-controls \
    qml-module-qtquick-controls2 \
    qml-module-qtquick-dialogs \
    qml-module-qtquick-layouts \
    qml-module-qtgraphicaleffects \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libxkbcommon-x11-0 \
    libxcb-xinerama0 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["bash"]
