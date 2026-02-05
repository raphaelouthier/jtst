.PHONY : install build run all

install:
	sudo apt-get install lldb binutils

build:
	g++ main1.cpp main0.cpp -o main.elf -g -O3

run:
	lldb main.elf -o 'b trap' -o 'run' -o 'up'
	
all: 
	make build
	make run


