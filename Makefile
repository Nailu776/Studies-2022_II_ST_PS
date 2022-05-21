# Makefile file
all:
	gcc -Wall ./game_confs/tictactoe.c -c 
	gcc -Wall ./game_confs/receiver.c -c 
	gcc -Wall ./game_confs/sender.c -c 
	gcc -Wall ./game.c -c 
	gcc -Wall -o ./game ./game.o ./tictactoe.o ./receiver.o ./sender.o

clean:
	rm game *.o 

 
# Usage example:

# P1:
# make
# sudo ./game enp0s8 08:00:27:2a:77:6f X
# *playing*
# make clean

# P2:
# make
# sudo ./game enp0s8 08:00:27:44:b9:60 O
# *playing*
# make clean

# end of Makefile file
