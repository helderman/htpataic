#!/bin/sh
read -p 'Enter chapter number (1-19): ' ch && cd "code$(printf '%02d' $ch)" && make lilcave && echo && ./lilcave
