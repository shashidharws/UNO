APP=uno

objs = main.o actions.o
CFLAGS= -I $(PWD)/../inc

$(APP): $(objs)
	cc -o $(APP) $(objs)

main.o:
actions.o: actions.c
	cc -c actions.c $(CFLAGS)

.PHONY : clean
clean:
	rm $(APP) $(objs)
