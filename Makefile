calc: front_end.y front_end.l
	bison -d front_end.y
	flex  -o front_end.lex.c front_end.l
	gcc  -o front_end front_end.lex.c front_end.tab.c -lfl -lm
	./front_end

clean:
	rm -rf front_end front_end.tab.c front_end.lex.c front_end.tab.h
