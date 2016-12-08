PROGS=main1 main2
include ../../XX/Makefile.rules


test1: main1 ../test.txt
	@echo "expected result: easter"
	@./main1 < ../test.txt

puzzle1: main1 ../puzzle.txt
	@echo "puzzle result:"
	@./main1 < ../puzzle.txt


test2: main2 ../test.txt
	@echo "expected result: advent"
	@./main2 < ../test.txt
	
puzzle2: main2 ../puzzle.txt
	@echo "puzzle result:"
	@./main2 < ../puzzle.txt
