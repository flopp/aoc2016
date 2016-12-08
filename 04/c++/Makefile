PROGS=main1 main2
include ../../XX/Makefile.rules


test1: main1 ../test.txt
	@echo "expected: 1514"
	@./main1 < ../test.txt

puzzle1: main1 ../puzzle.txt
	@echo "puzzle result:"
	@./main1 < ../puzzle.txt


puzzle2: main2 ../puzzle.txt
	@echo "puzzle result:"
	@./main2 < ../puzzle.txt



