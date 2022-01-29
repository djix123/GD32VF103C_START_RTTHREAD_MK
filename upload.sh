#!/bin/bash

~/tools/openocd-gd/bin/openocd -f interface/gd-link.cfg -f target/gd32vf103.cfg -c "init; halt;" -c "program ./.build/GD32VF103C_xxSPL.elf verify; reset; exit;"
