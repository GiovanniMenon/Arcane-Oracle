#!/bin/bash

sudo apt-update

sudo apt-get install libjsoncpp-dev
sudo apt-get install libcurl4-openssl-dev

qmake
make
