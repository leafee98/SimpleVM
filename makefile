CC="g++"
STD="-std=c++17"
OUT_PATH="out"
INCLUDE_PATH="src"

help :
	@echo "available targets: "
	@echo "    compiler"
	@echo "    runner"

compiler :
	$(CC) $(STD) -I $(INCLUDE_PATH) src/share/bitdef.cpp src/compiler/main.cpp -o $(OUT_PATH)/compiler.out

runner :
	$(CC) $(STD) -I $(INCLUDE_PATH) src/share/bitdef.cpp src/runner/main.cpp src/runner/func.cpp -o $(OUT_PATH)/runner.out