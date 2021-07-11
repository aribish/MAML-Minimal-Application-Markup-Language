maml: main lexObj lexer errFormatter graphics actionParser utils
	g++ objects/lexObj.o objects/main.o objects/lexer.o objects/errFormatter.o objects/actionParser.o objects/graphics.o objects/utils.o -o maml -lsfml-system -lsfml-window -lsfml-graphics

main: src/main.cpp
	g++ src/main.cpp -o objects/main.o -c
lexObj: src/lexObj.cpp
	g++ src/lexObj.cpp -o objects/lexObj.o -c
lexer: src/lexer.cpp
	g++ src/lexer.cpp -o objects/lexer.o -c
errFormatter: src/errFormatter.cpp
	g++ src/errFormatter.cpp -o objects/errFormatter.o -c
actionParser: src/actionParser.cpp
	g++ src/actionParser.cpp -o objects/actionParser.o -c
graphics: src/graphics.cpp
	g++ src/graphics.cpp -o objects/graphics.o -c
utils: src/utils.cpp
	g++ src/utils.cpp -o objects/utils.o -c
