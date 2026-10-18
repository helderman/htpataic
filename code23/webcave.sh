#!/bin/bash

# Play Little Cave Adventure in a web browser.
# Needs websockify to be installed (e.g. Ubuntu: sudo apt install websockify)

LILCAVE_DIR="${0%/*}"

# ---- Approach 1: websockify connects to lilcave - play on http://localhost:18811

# "$LILCAVE_DIR/lilcave" <<<quit &
# websockify --web "$LILCAVE_DIR/www" 18812 localhost:18811

# ---- Approach 2: websockify wraps lilcave - play on http://localhost:18812

websockify --web "$LILCAVE_DIR/www" 18811 -- ../lilcave <<<quit
