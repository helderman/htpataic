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
htpataic%.html: deps/htpataic%.d

# HTML file and dependency file are built simultaneously.
deps/htpataic%.d: htpataic%.txt | deps
	tools/compile.sh "$(*F)"

# Create directory for dependency files if it does not already exist.
deps:
	mkdir $@

# Include the dependency files.
-include $(patsubst %.txt,deps/%.d,$(wildcard htpataic??.txt))

# Delete targets and intermediate files; also in the subdirectories.
clean:
	$(RM) htpataic??.html deps/htpataic??.d
	for d in code??; do $(MAKE) --no-print-directory -C $$d clean; done
