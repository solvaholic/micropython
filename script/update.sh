#!/bin/bash

# * Instruct script/bootstrap.sh if config file doesn't exist
# * Update and upgrade cores, libraries, and packages
# * TODO: Update config with the latest `additional_urls`
# * Overwrite global Arduino15 configuration file

# Instruct script/bootstrap.sh if config file doesn't exist
_config_file="$(git rev-parse --show-toplevel)/arduino-cli.yaml"
if [ ! -r "$_config_file" ]; then
  echo "ERROR: Configuration file not found. Run script/bootstrap.sh first."
  exit 1
fi

# Update and upgrade cores, libraries, and packages
arduino-cli --config-file "$_config_file" update
arduino-cli --config-file "$_config_file" upgrade

# * TODO: Update config with the latest `additional_urls`

# Overwrite global Arduino15 configuration file
if [ -d "$HOME/Library/Arduino15" ]; then
  cp -f "$_config_file" "$HOME/Library/Arduino15/arduino-cli.yaml"
fi





