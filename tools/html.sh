#!/bin/bash

sed 's/&/\&amp;/g;s/</\&lt;/g;s/>/\&gt;/g;s/$/<br \/>/' "$@"
