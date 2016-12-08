PROGS=main1
include ../../XX/Makefile.rules

test1: main1 ../test.txt
	@./main1 7 3 < ../test.txt

puzzle1: main1 ../puzzle.txt
	@echo "puzzle result:"
	@./main1 50 6 < ../puzzle.txt
