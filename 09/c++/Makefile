PROGS=main1 main2
include ../../XX/Makefile.rules


test1: main1 ../test1.txt
	@echo "expected result: 18"
	@./main1 < ../test1.txt

puzzle1: main1 ../puzzle.txt
	@echo "puzzle result:"
	@./main1 < ../puzzle.txt


test2a: main2 ../test2a.txt
	@echo "expected result: 20"
	@./main2 < ../test2a.txt

test2b: main2 ../test2b.txt
	@echo "expected result: 241920"
	@./main2 < ../test2b.txt

test2c: main2 ../test2c.txt
	@echo "expected result: 445"
	@./main2 < ../test2c.txt

puzzle2: main2 ../puzzle.txt
	@echo "puzzle result:"
	@./main2 < ../puzzle.txt
