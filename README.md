# Semafory - SOI

Autor: Jakub Mazurkiewicz

Uzyskana ocena: ?/8

## Treść zadania

Założenia:

* W programie będą dwie kolejki FIFO o pewniej długości zdefiniowanej w #define
* Będzie dwóch producentów i dwóch konsumentów
* Producenci na zamianę umieszczają wartości typu `int` do dwóch kolejek
* Na podstawie tych wartości będzie można określić od którego producenta pochodzi
* Sekcja krytyczna będzie chroniona semaforem binarnym (mutexem)
* Będzie dużo wydruków z programu
* Nie można używać aktywnego oczekiwania

## Kompilacja i uruchamianie

```bash
make
./a.out
```

## Ocena

* Koncepcja (`docs/concept.pdf`): 2/2
* Program: ?/6

Łącznie: ?/8

## Dodatkowe narzędzia

* `freeshm.bash` - usuwanie semaforów i pamięci współdzielonej z katalogu `/dev/shm`
