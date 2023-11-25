#!/bin/bash

# Usage: ./script/upload.sh <sketch>

# * Fail if sketch doesn't exist
# * Instruct script/bootstrap.sh if config file doesn't exist
# * Instruct board attach, if $_sketch_name/sketch.yaml not present
# * Run 'arduino-cli upload' to build and upload the sketch

if [ -z "$1" ]; then
  echo "ERROR: Sketch not specified."
  echo "Usage: ./script/build.sh <sketch>"
  exit 1
fi

_config_file="$(git rev-parse --show-toplevel)/arduino-cli.yaml"
_sketch_name="$1"
_sketch_dir="$(git rev-parse --show-toplevel)/$_sketch_name"
_sketch_file="$_sketch_dir/sketch.yaml"

# Fail if sketch doesn't exist
if [ ! -d "$_sketch_dir" ]; then
  echo "ERROR: Sketch not found: '$_sketch_name'."
  exit 1
fi

# Instruct script/bootstrap.sh if config file doesn't exist
if [ ! -r "$_config_file" ]; then
  echo "ERROR: Configuration file not found. Run script/bootstrap.sh first."
  exit 1
fi

# * Instruct board attach, if $_sketch_file not present
if [ ! -r "$_sketch_file" ]; then
  echo "ERROR: $_sketch_file not found. Attach board first. For example:"
  echo '
  cd ~/repos/arduino

  _port=/dev/cu.usbserial-0001
  _board=Heltec-esp32:esp32:wifi_kit_32
  _sketch='"$_sketch_name"'

  arduino-cli --config-file ./arduino-cli.yaml \
  board attach -p $_port -b $_board \
  --board-options "UploadSpeed=115200" \
  $_sketch
  '
  exit 1
fi

# Run 'arduino-cli upload' to build and upload the sketch
arduino-cli --config-file "$_config_file" upload "$_sketch_dir"
