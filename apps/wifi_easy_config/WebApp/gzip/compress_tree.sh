#!/bin/bash

# walk recurdive through all subdirectrories
compress_directory() {
  for file in "$1"/*; do
    if [ -d "$file" ]; then
      compress_directory "$file"
    elif [ -f "$file" ]; then
      gzip "$file" -f 
    fi
  done
}

# check whether a directroy was applied
if [ -d "$1" ]; then
  # if yes, call the function
  compress_directory "$1"
else
  # if no,  output an error message
  echo "Please enter a valid directory"
fi
