CCP = gcc -std=c99
OFLAG = -o
main.exe:miao_hello.o wang_hello.o print_pretty.o main.o
	${CCP} ${OFLAG} main.exe miao_hello.o wang_hello.o print_pretty.o main.o
miao_hello.o:miao_hello.c
	${CCP} ${OFLAG} miao_hello.o -c miao_hello.c
wang_hello.o:wang_hello.c
	${CCP} ${OFLAG} wang_hello.o -c wang_hello.c
print_pretty.o:print_pretty.c
	${CCP} ${OFLAG} print_pretty.o -c print_pretty.c
main.o:main.c
	${CCP} ${OFLAG} main.o -c main.c