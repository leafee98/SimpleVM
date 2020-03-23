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
	@echo ""
	@echo "the test follwed can be used directly by assign e1/e2 to test_serial"
	@echo "    test_compile     [test_serial=e1]"
	@echo "    test_decompile   [test_serial=e1]"
	@echo "    test_run         [test_serial=e1]"

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


test_serial?=e1

test_source=example/$(test_serial)/$(test_serial).my_language
test_target=example/$(test_serial)/$(test_serial).my_target
test_decompiled=example/$(test_serial)/$(test_serial).decompiled

.PHONY : test_compile
test_compile : compiler $(test_source)
	./out/compiler $(test_source) $(test_target)

.PHONY : test_decompile
test_decompile : compiler $(test_target)
	./out/compiler -d $(test_decompiled) $(test_target)

.PHONY : test_run
test_run : compiler runner test_compile
	./out/runner $(test_target)
