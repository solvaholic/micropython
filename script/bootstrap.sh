#!/bin/bash

# * Ensure virtual environment is active
# * Install dependencies
# * TODO: Ensure any other prerequisites are met

# Work in the top level directory of this Git repository
_repo_root="$(git rev-parse --show-toplevel)"
if [ -d "$_repo_root" ]; then
  pushd "$_repo_root" > /dev/null
else
  echo "ERROR: This doesn't look like a Git repo. Something's wrong."
  exit 1
fi

# If virtual environment is not set, and it exists, prompt user to
# activate it
if [ -z "$VIRTUAL_ENV" ] && [ -r "./bin/activate" ]; then
  echo "ERROR: Virtual environment not activated."
  echo "Please activate the virtual environment and try again."
  echo "For example: 'source ./bin/activate'"
  exit 1
# If virtual environment is not set, and it doesn't exist, prompt
# user to create it
elif [ -z "$VIRTUAL_ENV" ] && [ ! -r "./bin/activate" ]; then
  echo "ERROR: Virtual environment not found."
  echo "Please create the virtual environment and try again."
  echo "For example: 'python3 -m venv .; source ./bin/activate'"
  exit 1
fi

# Update pip and install dependencies
pip install --upgrade pip
pip install --upgrade -r requirements.txt
