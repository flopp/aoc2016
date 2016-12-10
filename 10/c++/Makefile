PROGS=main1
include ../../XX/Makefile.rules


test1: main1 ../test.txt
	@echo "expected result: XXX"
	@./main1 2 5 < ../test.txt

puzzle1: main1 ../puzzle.txt
	@echo "puzzle result:"
	@./main1 17 61 < ../puzzle.txt


puzzle2: main1 ../puzzle.txt
	@echo "puzzle result:"
	@./main1 -1 -1 < ../puzzle.txt
