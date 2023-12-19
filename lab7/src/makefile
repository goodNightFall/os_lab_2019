CC=gcc
objects = tcp udp

all: $(objects)

tcp:
	$(CC) -o tcpc tcpclient.c -pthread  
	$(CC) -o tcps tcpserver.c -pthread  
	./tcps --bufsize 100 --port 5050 & 
	./tcpc --bufsize 100 --ip 0.0.0.0 --port 5050

udp:
	$(CC) -o udps udpserver.c -pthread  
	$(CC) -o udpc udpclient.c -pthread
	./udps --bufsize 100 --port 5000 &
	./udpc --bufsize 100 --ip 0.0.0.0 --port 5000  

clean : clean_tcp clean_udp

clean_tcp:
	fuser -k 5050/tcp
	rm tcpc tcps

clean_udp:
	fuser -k 5000/udp
	rm udpc udps