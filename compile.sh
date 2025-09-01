#!/bin/bash
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script as root privilege (use sudo)."
  exit 1
fi

if command -v apt &> /dev/null; then
  apt update
  apt install -y gcc libqrencode-dev libpng-dev
elif command -v yum &> /dev/null; then
  yum install -y gcc libqrencode-devel libpng-devel
elif command -v pacman &> /dev/null; then
  pacman -Sy --noconfirm gcc libqrencode libpng
else
  echo "Unsupported package manager. Please install dependencies manually. (gcc , libqrencode-dev , libpng-dev"
  exit 1
fi
clear
gcc qr_generator.c -o QR -lqrencode -lpng

if [ $? -eq 0 ]; then
  echo "Compilation successful. Executable 'QR' created."
else
  echo "Compilation failed."
  exit 1
fi
