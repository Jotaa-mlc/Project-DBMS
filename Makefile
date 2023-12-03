PARAMS = -g -W -pedantic

all: home tb_in tb_out tb_read io
	gcc Obj_files/home.o Obj_files/tables_in.o Obj_files/tables_out.o Obj_files/tables_read.o Obj_files/io_files.o -o dbms $(PARAMS)
home: home.c
	gcc -o Obj_files/home.o home.c -c $(PARAMS)
tb_in: tables_in.c
	gcc -o Obj_files/tables_in.o tables_in.c -c $(PARAMS)
tb_out: tables_out.c
	gcc -o Obj_files/tables_out.o tables_out.c -c $(PARAMS)
tb_read: tables_read.c
	gcc -o Obj_files/tables_read.o tables_read.c -c $(PARAMS)
io: io_files.c
	gcc -o Obj_files/io_files.o io_files.c -c $(PARAMS)