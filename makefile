COMPILE_COMMAND=g++ -std=c++17 -Isrc

COMPILER_FILE=\
src/share/bitdef.cpp\
src/compiler/func.cpp\
src/compiler/main.cpp

RUNNER_FILE=\
src/share/bitdef.cpp\
src/runner/func.cpp\
src/runner/main.cpp

help :
	@echo "available targets: "
	@echo "    compiler"
	@echo "    runner"

compiler : out/compiler/compiler
	$(COMPILE_COMMAND) $(COMPILER_FILE) -o $(OUT_PATH)/compiler

runner :
	$(COMPILE_COMMAND) $(RUNNER_FILE) -o $(OUT_PATH)/runner.out