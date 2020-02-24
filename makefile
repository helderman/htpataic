# Please build with GNU Make on Ubuntu, with the following packages installed.
# sudo apt install expect gcc graphviz wdiff zip

# Directories
SRC = src
CODE = code??
DEPS = deps
HTML = .

# $(CODE) is added here to force its recipe to be executed
.PHONY: all clean $(CODE)

# 'make' builds both the HTML documentation and the code samples.
# For HTML, the existence of a source file htpataic??.txt is leading.
all: $(CODE) $(patsubst $(SRC)/%.txt,$(HTML)/%.html,$(wildcard $(SRC)/htpataic??.txt))

# To build sample code, we recursively call make for each subdirectory.
$(CODE):
	$(MAKE) --no-print-directory -C $@

# Always rebuild HTML file if dependency file is missing.
$(HTML)/htpataic%.html: $(DEPS)/htpataic%.d

# HTML file and dependency file are built simultaneously.
$(HTML)/htpataic%.html: $(SRC)/htpataic%.txt | $(DEPS)
	tools/compile.sh "$(*F)" "$(DEPS)/htpataic$(*F).d" "$(SRC)" "$(HTML)"

# Create directory for dependency files if it does not already exist.
$(DEPS):
	mkdir $@

# Include the dependency files.
-include $(patsubst $(SRC)/%.txt,$(DEPS)/%.d,$(wildcard $(SRC)/htpataic??.txt))

# Delete targets and intermediate files; also in the subdirectories.
clean:
	$(RM) $(HTML)/htpataic??.html $(DEPS)/htpataic??.d
	for d in $(CODE); do $(MAKE) --no-print-directory -C $$d clean; done
