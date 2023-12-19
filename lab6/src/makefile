CC=gcc

all: server client

server: server.c
	$(CC) -o server server.c -pthread

client: client.c
	$(CC) -o client client.c -pthread

clean:
	fuser -k 5000/tcp  
	fuser -k 4050/tcp  
	rm -f server client

	