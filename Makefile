SRC_DIR   = src
BUILD_DIR = bin

MKDIR     = mkdir -p
CD        = cd
CMAKE		  = cmake
RM			  = rm -rf

DOT=dot -Nfixedsize=False -Nfontname=Times-Roman -Nshape=rectangle

all: clean run images/await.pdf

${BUILD_DIR}/Makefile: ${BUILD_DIR}
	@(${CD} $<; ${CMAKE} -DCMAKE_BUILD_TYPE=Debug ../${SRC_DIR})

build: ${BUILD_DIR}/Makefile
	@(${CD} ${BUILD_DIR}; ${MAKE})

run: build
	@(${CD} ${BUILD_DIR}; ${MAKE} run)

images/await.pdf: bin/await.dot
	@${MKDIR} images
	@${DOT} -Tpdf -o $@ $<

${BUILD_DIR}:
	@${MKDIR} $@

clean:
	@${RM} ${BUILD_DIR}

.PHONY: all build run clean
