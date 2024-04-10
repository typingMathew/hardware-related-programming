# basic Makefile to generate and clear empty txt
# author: typingMathew, inspired by Sachin Patil https://opensource.com/article/18/8/what-how-makefile
.PHONY: all greeting generate clean

all: greeting generate

greeting:
	@echo "Welcome to the making"

generate:
	@echo "Creating empty text files..."
	touch file-{1..10}.txt

clean:
	@echo "Cleaning up..."
	rm *.txt