#!/bin/bash
# Calls 'make clean' in every code folder.
for d in code??; do
	make -C $d clean
done
