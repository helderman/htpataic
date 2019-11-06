# Please build with GNU Make on Ubuntu, with the following packages installed.
# sudo apt install expect gcc graphviz wdiff zip

.PHONY: all clean code??

# 'make' builds both the HTML documentation and the code samples.
# For HTML, the existence of a source file htpataic??.txt is leading.
all: code?? $(patsubst %.txt,%.html,$(wildcard htpataic??.txt))

# To build sample code, we recursively call make for each subdirectory.
code??:
	$(MAKE) --no-print-directory -C $@

# Always rebuild HTML file if dependency file is missing.
htpataic%.html: htpataic%.d

# Build both the HTML file and the dependency file.
htpataic%.d: htpataic%.txt
	tools/compile.sh "$*"

# Include the dependency files.
-include $(patsubst %.txt,%.d,$(wildcard htpataic??.txt))

# Delete targets and intermediate files; also in the subdirectories.
clean:
	$(RM) htpataic??.html htpataic??.d
	for d in code??; do $(MAKE) --no-print-directory -C $$d clean; done
