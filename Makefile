BUILD_TYPE=Release
JOBS=2

.PHONY: test
test: build
	build/tests/egraph-test

.PHONY: build
build:
	mkdir -p build
	cd build && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) .. && make -j$(JOBS)

.PHONY: clean
clean:
	rm -rf build
