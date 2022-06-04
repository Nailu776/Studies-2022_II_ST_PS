# 2022_II_ST_PS  
Repozytorium github przeznaczone na przedmiot  
Programowanie Sieciowe (PS) na drugim stopniu studiów.

## Opis projektu  
Gra dla mobilnych bezprzewodowych sieci ad-hoc.  
Gra Kolko i krzyzyk polegajaca na turowym wysylaniu miedzy graczami planszy z wykonanym ruchem.  
Po uruchomieniu gry nastepuje proba dolaczenia do istniejacej rozgrywki,  
a po 10 sekundach od braku odpowiedzi startuje nowa gra i oczekiwanie na drugiego gracza.  
Gracze nie musza znac swoich adresow, musza jedynie znajdowac sie w tej samej sieci, gdyz plansza jest wysylana rozgloszeniowo.  
Po dolaczeniu do rozgrywki, losowane sa znaki, ktorym beda poslugiwac sie gracze - X zawsze zaczyna pierwszy.  

## Pliki zrodlowe  

*game.c*  
Plik game.c jest plikiem glowym programu.  
Inicjowane jest w nim gniazdo komunikacji,  
wybor graczy oraz petle graczy.
Kompilacja:  
```
gcc -Wall ./game.c -c -fcommon  
gcc -Wall -o ./game ./game.o ./tictactoe.o ./receiver.o ./sender.o -fcommon  
```

*sender*  
Pliki sender zawieraja ustawienia gniazda dotyczace wysylania ramek oraz budowania ich.  
Kompilacja:  
```
gcc -Wall ./game_confs/sender.c -c -fcommon  
```

*receiver*  
Pliki receiver zawieraja ustawienia gniazda dotyczace odbierania ramek oraz interpretowania ich zawratosci.  
Kompilacja:  
``` 
gcc -Wall ./game_confs/receiver.c -c -fcommon  
```

*tictactoe*  
Pliki tictactoe odpowiedzialne sa za implementacje zasad gry, wyswietlanie plansz oraz ruchy graczy.  
Kompilacja:  
```
gcc -Wall ./game_confs/tictactoe.c -c -fcommon  
```

## Sposob uruchomienia
Projekt kompiluje sie poleceniem 'make' dzieki przygotowanemu pliku Makefile.  
Skompilowany program uruchamia sie nastepujacym poleceniem:  
```
./game INTERFACE_NAME  
```
Argument INTERFACE_NAME jest numerem uzywanego interfejsu sieciowego.
