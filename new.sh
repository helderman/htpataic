#!/bin/bash
awk '{print"[new]"$0"[old]"}' $2
