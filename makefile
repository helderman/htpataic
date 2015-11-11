# Phony targets (GNU Make).
# Typically, you should do 'make code' followed by 'make html'.
# I haven't found a way to combine this into a single make
# without forcing a rebuild of all .html files.
.PHONY: html code code??

# 'make html' will make every htpataic??.html
# (following the existence of htpataic??.txt)
html: $(patsubst %.txt,%.html,$(wildcard htpataic??.txt))

# Each .html will be rebuilt upon modification of its .txt
# and/or its sample code (based on build target code??/test.out)
htpataic%.html: htpataic%.txt code%/test.out
	tools/compile.sh $< > $@

# Prevent error in case the sample code has not been built successfully yet
.SECONDARY: code%/test.out

# 'make code' will make all sample code (i.e. every subdirectory code??)
code: code??

# To make sample code, we recursively call make within the subdirectory
code??:
	$(MAKE) -C $@
