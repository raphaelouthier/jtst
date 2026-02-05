install:
	sudo apt-get install lldb binutils

build:
	g++ main0.cpp main1.cpp -o main.elf -g -O3

run:
	lldb main.elf


