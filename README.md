# 2022_II_ST_PS  
Repozytorium github przeznaczone na przedmiot Programowanie Sieciowe (PS) na drugim stopniu studiów.

## Opis projektu  
Gra dla mobilnych bezprzewodowych sieci ad-hoc.  
Gra Kółko i krzyżyk polegająca na turowym wysyłaniu między graczami planszy z wykonanym ruchem.  
Po uruchomieniu gry następuje próba dołączenia do istniejącej rozgrywki,
a po 10 sekundach od braku odpowiedzi startuje nowa rozgrywka i następuje oczekiwanie na drugiego gracza.  
Gracze nie muszą znać swoich adresów, muszą jedynie znajdowac się w tej samej sieci, gdyż plansza jest wysyłana rozgłoszeniowo.  
Po dołączeniu do rozgrywki, losowane są znaki, którymi będą posługiwac się gracze.  
Znak X oznacza gracza pierwszego, który zawsze zaczyna rozgrywkę, a znak O gracza drugiego.  

## Pliki źródłowe  

*tictactoe*  
Pliki tictactoe odpowiedzialne są za implementację zasad gry, wyświetlanie plansz oraz ruchy graczy.  
Kompilacja:  
```
gcc -Wall ./game_confs/tictactoe.c -c -fcommon  
```  

*receiver*  
Pliki receiver zawierają ustawienia gniazda dotyczące odbierania ramek oraz interpretowania ich zawratości.  
Kompilacja:  
``` 
gcc -Wall ./game_confs/receiver.c -c -fcommon  
```  

*sender*  
Pliki sender zawierają ustawienia gniazda dotyczące wysyłania ramek oraz budowania ich.  
Kompilacja:  
```
gcc -Wall ./game_confs/sender.c -c -fcommon  
```  

*game.c*  
Plik game.c jest plikiem główym programu.  
Inicjowane jest w nim gniazdo komunikacji, wybór graczy oraz pętle graczy.  
Kompilacja:  
```
gcc -Wall ./game.c -c -fcommon  
gcc -Wall -o ./game ./game.o ./tictactoe.o ./receiver.o ./sender.o -fcommon  
```  

## Sposób uruchomienia
Projekt kompiluje się poleceniem 'make', dzięki przygotowanemu pliku Makefile.  
Skompilowany program uruchamia się nastepujacym poleceniem:  
```
sudo ./game INTERFACE_NAME  
```
Argument INTERFACE_NAME jest nazwą używanego interfejsu sieciowego.  
Program wymaga uprawnień roota.
