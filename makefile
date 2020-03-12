COMPILE_COMMAND=g++ -std=c++17 -Isrc

OUT_PATH=out

COMPILER_FILE=\
src/share/bitdef.cpp\
src/compiler/func.cpp\
src/compiler/main.cpp

RUNNER_FILE=\
src/share/bitdef.cpp\
src/runner/func.cpp\
src/runner/main.cpp

.PHONY : help
help :
	@echo "available targets: "
	@echo "    all"
	@echo "    compiler"
	@echo "    runner"
	@echo "    clean"

.PHONY : all
all : compiler runner

.PHONY : compiler
compiler : $(OUT_PATH)/compiler

.PHONY : runner
runner : $(OUT_PATH)/runner

.PHONY : clean
clean :
	rm -r $(OUT_PATH)

$(OUT_PATH)/compiler : $(COMPILER_FILE)
	[ -d $(OUT_PATH) ] || mkdir $(OUT_PATH)
	$(COMPILE_COMMAND) $(COMPILER_FILE) -o $(OUT_PATH)/compiler

$(OUT_PATH)/runner : $(RUNNER_FILE)
	[ -d $(OUT_PATH) ] || mkdir $(OUT_PATH)
	$(COMPILE_COMMAND) $(RUNNER_FILE) -o $(OUT_PATH)/runner
