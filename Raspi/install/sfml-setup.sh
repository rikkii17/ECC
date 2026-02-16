#!/bin/bash

# 1. パッケージリストの更新
echo "Updating package lists..."
sudo apt update -y

# 2. OpenGL関連のベースライブラリ
echo "Installing OpenGL and Mesa utils..."
sudo apt install -y mesa-utils libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev

# 3. SFML本体と依存関係 (X11, Freetype, OpenAL等)
echo "Installing SFML and dependencies..."
sudo apt install -y libsfml-dev libx11-dev libxrandr-dev libfreetype6-dev libudev-dev libopenal-dev libvorbis-dev libflac-dev

# 4. ビルドツール (CMake含む)
echo "Installing build tools..."
sudo apt install -y build-essential cmake

echo "---------------------------------------"
echo "Setup Complete! Please reboot your Raspi."
echo "---------------------------------------"