#!/bin/bash

# * Run script/bootstrap.sh first
# * Upgrade Python packages and update requirements.txt
# * TODO: If a board is connected, update its installed packages

# Work in the top level directory of this Git repository
_repo_root="$(git rev-parse --show-toplevel)"
if [ -d "$_repo_root" ]; then
  pushd "$_repo_root" > /dev/null
else
  echo "ERROR: This doesn't look like a Git repo. Something's wrong."
  exit 1
fi

# Run script/bootstrap.sh first
if [ -x "./script/bootstrap.sh" ]; then
  echo "Running script/bootstrap.sh..."
  ./script/bootstrap.sh
else
  echo "ERROR: script/bootstrap.sh not found. Something's wrong."
  exit 1
fi

# Upgrade Python packages and update requirements.txt
if ! sed -i.bak 's/==/>=/g' requirements.txt; then
  echo "ERROR: Something's wrong."
fi
if ! pip install -r requirements.txt --upgrade; then
  echo "ERROR: Failed to update requirements."
  mv requirements.txt.bak requirements.txt
  exit 1
fi
pip freeze > requirements.txt
