CXXFLAGS=-std=c11 -Wall -I src
CXX=gcc
GR_DIR=src/bison
BISON_GEN_DIR=$(GR_DIR)/gen
SRCS=$(call rwildcard,src,*.c)

all: ./build
	$(CXX) $(CXXFLAGS) \
		-o build/app \
		$(SRCS)

$(BISON_GEN_DIR)/%.lexer.c $(BISON_GEN_DIR)/%.lexer.h: $(GR_DIR)/%.lex $(BISON_GEN_DIR)
	flex $(GR_DIR)/$*.lex
	mv lex.c $(BISON_GEN_DIR)/$*.lexer.c
	mv lex.h $(BISON_GEN_DIR)/$*.lexer.h

$(BISON_GEN_DIR)/%.tab.c $(BISON_GEN_DIR)/%.tab.h: $(GR_DIR)/%.y $(BISON_GEN_DIR)
	bison -d -v $< -o $(BISON_GEN_DIR)/$*.tab.c

$(BISON_GEN_DIR):
	mkdir -p src/bison/gen

build/app: src/main.c $(BISON_GEN_DIR)/Expression.lexer.c $(BISON_GEN_DIR)/Expression.tab.c
	$(CXX) $(CXXFLAGS) -o build/app $^

bison-codegen: $(BISON_GEN_DIR)/Expression.lexer.c $(BISON_GEN_DIR)/Expression.tab.c

compile: ./build build/app

run:
	./build/app

build:
	mkdir -p build

dist:
	mkdir -p dist

clean:
	rm -rf build
	rm -rf dist
	rm -rf $(BISON_GEN_DIR)

release: clean bison-codegen dist
	zip dist/expression_parser.zip -r Makefile src
