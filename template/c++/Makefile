PROGS=main1 main2
include ../../XX/c++/Makefile

test1: main1 ../test1.txt
	@echo "expected result: XXX"
	@./main1 < ../test1.txt

puzzle1: main1 ../puzzle.txt
	@echo "puzzle result:"
	@./main1 < ../puzzle.txt


test2: main2 ../test2.txt
	@echo "expected result: XXX"
	@./main2 < ../test2.txt
	
puzzle2: main2 ../puzzle.txt
	@echo "puzzle result:"
	@./main2 < ../puzzle.txt
