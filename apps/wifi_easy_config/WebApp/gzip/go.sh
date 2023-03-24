#!/bin/bash

rm -r ./Export/*
cp -R ../Export/* ./Export
./compress_tree.sh Export/ 