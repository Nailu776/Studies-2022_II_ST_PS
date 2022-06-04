# Makefile file
all:
	gcc -Wall ./game_confs/tictactoe.c -c -fcommon
	gcc -Wall ./game_confs/receiver.c -c -fcommon
	gcc -Wall ./game_confs/sender.c -c -fcommon
	gcc -Wall ./game.c -c -fcommon
	gcc -Wall -o ./game ./game.o ./tictactoe.o ./receiver.o ./sender.o -fcommon

clean:
	rm game *.o 

 
# Usage example:

# P1:
# make
# sudo ./game enp0s8
# *playing*
# make clean

# P2:
# make
# sudo ./game enp0s8
# *playing*
# make clean

# end of Makefile file
