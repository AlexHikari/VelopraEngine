#!/bin/bash
set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
VCPKG_DIR="$PROJECT_DIR/vcpkg"

if [ ! -d "$VCPKG_DIR" ]; then
    echo "Cloning vcpkg into $VCPKG_DIR"
    git clone https://github.com/Microsoft/vcpkg.git "$VCPKG_DIR"
    "$VCPKG_DIR/bootstrap-vcpkg.sh"
else
    echo "vcpkg already installed"
fi

echo "Installing dependencies"

# List of dependencies
dependencies=(opengl glew assimp glm qt5 spdlog)

# Install each dependency one by one
for dep in "${dependencies[@]}"; do
    echo "Installing $dep..."
    "$VCPKG_DIR/vcpkg" install "$dep"
done

echo "Setup completed successfully"
