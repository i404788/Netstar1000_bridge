#!/bin/sh

arduino-cli config init --overwrite
arduino-cli config add board_manager.additional_urls http://digistump.com/package_digistump_index.json

arduino-cli core install digistump:avr 
arduino-cli board attach -b digistump:avr:digispark-tiny .
