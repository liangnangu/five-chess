# t his is five chess
#注意学习makefile 的编写
src=main.c init_fo.c basic_shape.c print_chess_board.c mous_op.c chess_op.c
para= -g -o main.exe -Wall
main:$(src)
	gcc $(src) $(para)

clean:
	rm -rf main
	rm -rf *.o
	rm -rf ~*
	rm -rf *.swp
