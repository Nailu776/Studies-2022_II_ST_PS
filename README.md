# 2022_II_ST_PS    

Repository for a project on Network programming (Programowanie sieciowe - PS)

## Authors
Julian Helwig - https://julian.helwig.tech/#/ https://github.com/Nailu776

Seweryn Kopeć - https://github.com/SewerynKopec

## Project Description

Game that works in any wireless mobile ad-hoc networks.

A game of Tic-tac-toe. Two players send each other messages containing a board updated with their most recent move.

At first the application scans for an existing game in the network. After 10 seconds of trying, the game is started anew and the player waits for a second player.

The main feature of the game search is that it doesn't require an IP of any of the players. 

When 2 players finally join the match. The game chooses who starts at random.

X always starts first, O is always second.


## Source files  

*tictactoe*  
Files that match ticatactoe.* implement the rules of the game as well as displaying the boards and making moves.  
Compilation:  
```
gcc -Wall ./game_confs/tictactoe.c -c -fcommon  
```  

*receiver*  
Files that match receiver.* contain socket settings that are responsible for receiveing frames and parsing their contents.
Compilation:  
``` 
gcc -Wall ./game_confs/receiver.c -c -fcommon  
```  

*sender*  
Files that match sender.* contain socket settings responsible for sending and constructing frames.
Compilation:  
```
gcc -Wall ./game_confs/sender.c -c -fcommon  
```  

*game.c*  
File with a name game.c contains the main function.
There, sockets, roles and I/O event loops are implemented
Compilation:  
```
gcc -Wall ./game.c -c -fcommon  
gcc -Wall -o ./game ./game.o ./tictactoe.o ./receiver.o ./sender.o -fcommon  
```  

## How to run
The project compiles using the 'make' command. It runs all the commands contained in Makefile.

A compiled program is run by the following command:

```
sudo ./game INTERFACE_NAME  
```
INTERFACE_NAME is the name of the current network interface

# Important!!!
The program requires root privilages.
