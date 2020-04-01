# Wirtualny Ekosystem

Wirtualny Ekosystem to biocybernetyczny symulator rozwoju ekosystemu, który tworzą różne gatunki organizmów.

![Zrzut ekranu](https://i.imgur.com/q8KLwFf.png)
*Przykładowy ekosystem*

# Organizmy
Każdy organizm prowadzi różne funkcje życiowe podczas kroków symulacji.
- Żywienie się - jeśli stworzenie nie rozmnaża się w danym kroku, próbuje spożyć jeden posiłek. Każdy gatunek robi to na własny sposób.
- Rozmnażanie się - zakładając, że w sąsiedztwie są niezajęte przez jakikolwiek organizm nisze, to jeśli najedzenie danego organizmu przekroczy koszt narodzenia potomka, rozmnoży się on. Spowoduje to odjęcie z punktów najedzenia kosztu potomka.
- Starzenie się - każdy żywy organizm zwiększa swój wiek o 1 w każdym kroku symulacji. Jeśli wiek przekroczy maksymalny wiek, organizm umiera i staje się pożywieniem dla grzybów, jednak dopóki nie zostanie wchłonięty, nadal zajmuje swoją niszę.
### Glony
Są pasywnymi stworzeniami. Odżywiają się poprzez fotosyntezę i rozmnażają się względnie szybko.
Przyjmują znak zielonej gwiazdki (*).
### Grzyby
Organizmy oczyszczające ekosystem z trupów, którymi się pożywiają. Są względnie wytrzymałe.
Reprezentowane są przez niebieskie krzyżyki (#).
### Bakterie
Bakterie to gatunek agresywny. Atakują glony, a jeśli nie znajdą ich w sąsiedztwie, wchłaniają inne bakterie. Są organizmami żyjącymi bardzo krótko, jednak nadrabiają to względnie szybkim rozmnażaniem się.
Po wchłonięciu glonu lub innej bakterii, zajmuje niszę wchłoniętego organizmu. W przypadku wchłonięcia glonu zwiększa to szanse przetrwania bakterii, ponieważ najprawdopodobniej znajdzie się ona wtedy obok kolejnego glonu, który będzie mogła wchłonąć w następnym kroku symulacji.
Wyświetlane są w kolorze czerwonym jako (@).

# Obsługa aplikacji
Po uruchomieniu aplikacji, automatycznie rozpocznie się proces tworzenia nowego wirtualnego ekosystemu. Należy podać rozmiar środowiska oraz początkową liczebność każdego gatunku organizmów.
Po utworzeniu środowiska zostanie ono wyświetlone wraz z instrukcjami jego obsługi.
### Dostępne polecenia
Instrukcje znajdują się również wewnątrz aplikacji.
##### Wciśnięcie enter bez wpisywania czegokolwiek
Powoduje wykonanie kroku symulacji, podczas którego organizmy wykonają swoje czynności życiowe.

##### `b`
Wyświetla środowisko, jednak nie wykonuje kroku symulacji.

##### `s[ile = 20]`
Wyświetla statystyki dla ostatnich `ile` kroków (domyślnie 20).
![Przykładowe użycie polecenia s7](https://i.imgur.com/LyoFEr2.png)

##### `w`
Rysuje wykres liczebności gatunków podczas ostatnich 120 kroków.
![Przykładowe użycie polecenia w](https://i.imgur.com/IE10cLD.png)

##### `se`
Eksportuje do pliku .csv o podanej nazwie następujące dane o ekosystemie:
- szerokość środowiska
- wysokość środowiska
- długość życia poszczególnych gatunków organizmów
- ich maksymalne najedzenie
- ich koszt narodzin
- statystyki liczebności poszczególnych organizmów podczas wszystkich kroków
- statystyki najedzeń
- statystyki rozmnażania się

Z wyeksportowanych danych można np. tworzyć wykresy w Excelu:
![Wykres liczebności gatunków w Excelu](https://i.imgur.com/zjrKlfR.png)  
~~*Dostałem zbyt dużo czasu na wykonanie tego projektu.*~~

##### `e`
Opuszcza obecne środowisko, następnie pozwala utworzyć nowe, lub wyjść z programu.

##### `u`
Wyświetla obecne ustawienia wyświetlania, oraz informacje o tym, jak je zmienić.
![Wyświetlone ustawienia](https://i.imgur.com/CkW8VQB.png)

# Używane biblioteki
Aplikacja używa nagłówkowej biblioteki open-source [Termcolor](https://github.com/ikalnytskyi/termcolor). Ułatwia ona kolorowanie tekstu konsoli na różnych systemach.

# Uruchomienie

Skompilowane pliki aplikacji znajdują się pod tym linkiem: https://github.com/HoutarouOreki/wirtualnyEkosystem/releases.
##### Windows
Pobierz `wirtualnyEkosystem.exe` i dwukrotnie kliknij.
##### Linux
Pobierz `wirtualnyEkosystem.AppImage`.
Następnie zmień właściwości pliku, aby można było go uruchamiać. Można to zrobić albo we właściwościach pliku, albo za pomocą terminala:
```sh
$ cd <ścieżka folderu, do którego został pobrany plik>
$ chmod a+x wirtualnyEkosystem.AppImage
```
Uruchom plik albo klikając go dwukrotnie, albo z terminala, wpisując będąc w folderze pliku:
```sh
./wirtualnyEkosystem.AppImage
```

---

Projekt został napisany przy użyciu Qt Creatora w ramach Programowania Obiektowego w C++ na Politechnice Lubelskiej.
