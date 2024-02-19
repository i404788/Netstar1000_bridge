#!/bin/sh

arduino-cli compile -e
sudo ./micronucleus ./build/digistump.avr.digispark-tiny/UPS_bridge.ino.hex
