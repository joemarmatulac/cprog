subtractor.o: subtractor.h subtractor.c
	gcc -c subtractor.c
summation.o: summation.h summation.c
	gcc -c summation.c
simpleCalculator.o: subtractor.h summation.h simpleCalculator.c
	gcc -c simpleCalculator.c
launcher: subtractor.o simpleCalculator.o
	gcc simpleCalculator.o subtractor.o -o launcher
