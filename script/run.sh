#!/bin/bash

# Usage: ./script/run.sh <script>

# * Does <script> exist?
# * Is a board connected? Get its port
# * TODO: Validate :hwconfig.py
# * TODO: Enable debugging?
# * Run the script

# Does <script> exist?
if [ -z "$1" ]; then
  echo "ERROR: Script not specified."
  echo "Usage: ./script/build.sh <script>"
  exit 1
elif [ ! -r "$1" ]; then
  echo "ERROR: Script not found: '$1'."
  exit 1
fi

# Is a board connected? Get its port
_tty="$(ls /dev/tty.usb*| head -n 1)"
if [ ! -r "$_tty" ]; then
  echo "ERROR: No board connected."
  echo "Please connect a board and try again."
  exit 1
else
  echo "Board found: $_tty"
fi

# Run the script
if command -v mpremote > /dev/null; then
  echo "Running '$1' on $_tty..."
  mpremote connect "$_tty" run "$1"
else
  echo "ERROR: 'mpremote' not found. Maybe run './script/bootstrap'?"
  exit 1
fi
