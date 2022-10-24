.PHONY: all
all: install run

.PHONY: run
run:
	cd build && make 3DViewer_v1 && open 3DViewer_v1.app/Contents/MacOS/3DViewer_v1
	cd ..

.PHONY: install
install:
	-mkdir build
	cmake CMakeLists.txt -S . -B ./build


.PHONY: uninstall
uninstall: clean
	-rm -rf build


.PHONY: clean
clean:
	-cd build && make clean && cd ..
	-cd tests && make clean && cd ..


.PHONY: dvi
dvi:
	open ../materials/dvi.pdf


.PHONY: dist
dist: install
	cd build && make dist && cd ..


.PHONY: tests
tests:
	cd tests && make tests && cd ..


.PHONY: gcov_report
gcov_report:
	cd tests && make gcov_report && cd ..

lint:
	clang-format -n $(shell find . -name "*.c" -or -name "*.cpp")

check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(shell find . -name "*.c" -or -name "*.cpp" | grep "./QtGifImage-master/*" -v)