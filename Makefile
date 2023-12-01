PARAMS = -g -W -pedantic
 
all: home funcs io
	gcc Obj_files/home.o Obj_files/tables_func.o Obj_files/io_files.o -o dbms $(PARAMS)
home: home.c
	gcc -o Obj_files/home.o home.c -c $(PARAMS)
funcs: tables_func.c
	gcc -o Obj_files/tables_func.o tables_func.c -c $(PARAMS)
io: io_files.c
	gcc -o Obj_files/io_files.o io_files.c -c $(PARAMS)