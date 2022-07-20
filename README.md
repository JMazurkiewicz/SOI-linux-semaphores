# Prezentacja semaforów w systemie Linux

Autor: Jakub Mazurkiewicz

## Pobieranie i kompilacja

```bash
git clone https://github.com/JMazurkiewicz/SOI-linux-semaphores
cd SOI-linux-semaphores
cmake -B build
cmake --build build
```

## Uruchamianie

```bash
cd build
./semaphores 1>/dev/null & tail -f semaphores.log

# Lub po prostu:
./semaphores
```

## Dodatkowe informacje

### Narzędzia

* `freeshm.sh` - usuwanie semaforów i pamięci współdzielonej z katalogu `/dev/shm`.

### Treść zadania

Założenia:

* W programie będą dwie kolejki FIFO o pewniej długości zdefiniowanej w #define
* Będzie dwóch producentów i dwóch konsumentów
* Producenci na zamianę umieszczają wartości typu `int` do dwóch kolejek
* Na podstawie tych wartości będzie można określić od którego producenta pochodzi
* Sekcja krytyczna będzie chroniona semaforem binarnym (mutexem)
* Będzie dużo wydruków z programu
* Nie można używać aktywnego oczekiwania

### Ocena

* Koncepcja (`docs/concept.pdf`): 2/2
* Program: 6/6

Łącznie: 8/8
