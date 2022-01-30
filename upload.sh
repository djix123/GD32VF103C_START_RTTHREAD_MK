#!/bin/bash

~/tools/openocd-gd/bin/openocd -f interface/gd-link.cfg -f target/gd32vf103.cfg -c "init; halt;" -c "program ./.build/GD32VF103C_START_RTTHREAD_MK.elf verify; reset; exit;"
