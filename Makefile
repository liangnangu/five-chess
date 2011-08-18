# t his is five chess

src=main.c init_fo.c basic_shape.c print_chess_board.c print_chess.c mous_op.c chess_op.c
para= -g -o main.exe -Wall
main:$(src)
	gcc $(src) $(para)

clean:
	rm -rf main
	rm -rf *.o
	rm -rf ~*
	rm -rf *.swp
