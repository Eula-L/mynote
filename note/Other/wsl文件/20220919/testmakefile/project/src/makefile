#version 1.0

TARGET=app#目标
CC=gcc#编译器命令
INCLUDE_PATH=../include#头文件路径
LIBRARY_PATH=../lib#库文件路径
INSTALL_PATH=/usr/bin#安装路径
CFLAGS=-I${INCLUDE_PATH} -g -Wall#编译参数
CPPFLAGS=-D

SOURCEFILE=$(wildcard *.c)
DFILE=$(patsubst %.c,%.o,$(SOURCEFILE))

${TARGET}:${DFILE}
	${CC} $^ -o $@

%.o:%.c
	${CC} $< -c ${CFLAGS} 

clean:
	rm -f ${DFILE} ${TARGET}

output:
	echo ${INSTALL_PATH}/${TARGET}

install:
	sudo cp ${TARGET} ${INSTALL_PATH}

disclean:
	sudo rm -rf ${INSTALL_PATH}/${TARGET}
#main.o:main.c
#	gcc $< -c -I../include 

#add.o:add.c
#	gcc $< -c -I../include 

#sub.o:sub.c
#	gcc $< -c -I../include

#mul.o:mul.c
#	gcc $< -c -I../include 
	
#des.o:des.c
#	gcc $< -c -I../include  
	
	
