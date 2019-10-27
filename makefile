# Please build on Ubuntu, with the following packages installed.
# sudo apt install expect graphviz wdiff

# Phony targets (GNU Make).
# Typically, you should do 'make code' followed by 'make html'.
# I haven't found a way to combine this into a single make
# without forcing a rebuild of all .html files.
# Besides, it would be annoying to have an error in code block documentation.
.PHONY: html code code?? clean

# 'make html' will make every htpataic??.html
# (following the existence of htpataic??.txt)
html: $(patsubst %.txt,%.html,$(wildcard htpataic??.txt))

# Each .html will be rebuilt upon modification of its .txt
# and/or its sample code (based on build target code??/success.txt)
htpataic%.html: htpataic%.txt code%/success.txt
	tools/compile.sh $< > $@

htpataic09.html: code09/makefile

# Prevent error in case the sample code has not been built successfully yet
.SECONDARY: code%/success.txt

# 'make code' will make all sample code (i.e. every subdirectory code??)
code: code??

# To make sample code, we recursively call make within the subdirectory
code??:
	$(MAKE) -C $@

# Delete targets from every source folder (code??)
clean:
	tools/clean.sh
