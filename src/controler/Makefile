APP_SERV=server
APP_CLI=client

objs = connection.o

$(APP_SERV): connection.o
	gcc -o $(APP_SERV) $(objs)

$(APP_CLI): connection.o
	gcc -o $(APP_CLI) $(objs)


connection.o:

.PHONY=clean
clean:
	rm *.o $(APP_SERV) $(APP_CLI)
