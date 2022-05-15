all:
	gcc -Wall ./adhoc_game.c -o ./adhoc_game

clean:
	rm adhoc_game

# sudo ./adhoc_game enp0s8 08:00:27:2a:77:6f 1
# sudo ./adhoc_game enp0s8 08:00:27:44:b9:60 0