tpl:hash.o tpl.o
	gcc -o tpl hash.o tpl.o

hash.o:hash.c
	gcc -c -Wall -g -O2 hash.c -o hash.o

#mix_val.o:mix_val.c
#	gcc -c -Wall -g -O2 mix_val.c -o mix_val.o

tpl.o:tpl.c
	gcc -c -Wall -g -O2 tpl.c -o tpl.o

clean:
	@rm -f *.o
	@rm -f tpl
