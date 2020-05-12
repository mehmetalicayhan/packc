DIR := ${CURDIR}
PROJECT_NAME := mac
all:
	mkdir -p build
	cmake -S ${DIR} -B ${DIR}/build
	cd build && make

clean:
	rm -rf build

run:
	cd build && ./${PROJECT_NAME}
