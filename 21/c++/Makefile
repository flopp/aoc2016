PROGS=main1 main2
include ../../XX/Makefile.rules


test: main1 ../test.txt
	@./main1 abcde    < ../test.txt

puzzle: main1 ../puzzle.txt
	@./main1 abcdefgh < ../puzzle.txt

puzzle2: main2 ../puzzle.txt
	@./main2 abcdefgh fbgdceah < ../puzzle.txt
