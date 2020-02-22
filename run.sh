#!/bin/sh
read -p 'Enter chapter number (1-18): ' ch && cd "code$(printf '%02d' $ch)" && make lilcave && echo && ./lilcave
