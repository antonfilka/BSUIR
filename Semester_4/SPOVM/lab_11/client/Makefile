client: time makecl
	gcc -o client  client.o time.o -lpthread
	
time:
	gcc -c time.c

makecl:
	gcc -c client.c -lpthread

clean:
	rm client