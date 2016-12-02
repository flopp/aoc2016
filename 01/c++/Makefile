PROGS=main1 main2
include ../../XX/c++/Makefile

test1: main1 ../test1.txt ../test2.txt ../test3.txt
	@echo "expected: 5"
	@./main1 < ../test1.txt
	@echo "expected: 2"
	@./main1 < ../test2.txt
	@echo "expected: 12"
	@./main1 < ../test3.txt

puzzle1: main1 ../puzzle.txt
	@echo "puzzle result:"
	@./main1 < ../puzzle.txt


test2: main2 ../test4.txt
	@echo "expected: 4"
	@./main2 < ../test4.txt

puzzle2: main2 ../puzzle.txt
	@echo "puzzle result:"
	@./main2 < ../puzzle.txt



