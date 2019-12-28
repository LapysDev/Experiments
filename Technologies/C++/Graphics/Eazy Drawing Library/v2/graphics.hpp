/* ... */
#pragma once

/* Import */
#include <math.h> // Mathematics
#include <stdio.h> // Standard Input-Output
#include <stdlib.h> // Standard Library

/* Namespace */
    /* ... */
    inline namespace {
        /* Function */
            // Absolute
            inline double abs(const double number) { return number < 0 ? -number : number; }
            inline float abs(const float number) { return number < 0 ? -number : number; }
            inline int abs(const int number) { return number < 0 ? -number : number; }
            inline long abs(const long number) { return number < 0 ? -number : number; }
            inline long double abs(const long double number) { return number < 0 ? -number : number; }
            inline long long abs(const long long number) { return number < 0 ? -number : number; }
            inline short abs(const short number) { return number < 0 ? -number : number; }
            inline unsigned int abs(const unsigned int number) { return number < 0 ? -number : number; }
            inline unsigned long abs(const unsigned long number) { return number < 0 ? -number : number; }
            inline unsigned long long abs(const unsigned long long number) { return number < 0 ? -number : number; }
            inline unsigned short abs(const unsigned short number) { return number < 0 ? -number : number; }

            // Align --- CONTINUE (Lapys) --- NOTE (Lapys) -> Aligns the number to a block size (which must be a power of 2).
            inline int align(const int number, const int blockSize) { return (number + ((blockSize) - 1)) & ~((blockSize) - 1); }
            inline int align(const int number, const long blockSize) { return (number + ((blockSize) - 1)) & ~((blockSize) - 1); }
            inline int align(const int number, const long long blockSize) { return (number + ((blockSize) - 1)) & ~((blockSize) - 1); }
            inline int align(const int number, const short blockSize) { return (number + ((blockSize) - 1)) & ~((blockSize) - 1); }

            // Fit To --- NOTE (Lapys) -> Fits the number to a unit size.
            inline int fitTo(const int number, const int unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1 : 0) : 0; } inline int fitTo(const int number, const long unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1 : 0) : 0; } inline int fitTo(const int number, const long long unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1 : 0) : 0; } inline int fitTo(const int number, const short unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1 : 0) : 0; }
            inline long fitTo(const long number, const int unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1L : 0L) : 0L; } inline long fitTo(const long number, const long unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1L : 0L) : 0L; } inline long fitTo(const long number, const long long unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1L : 0L) : 0L; } inline long fitTo(const long number, const short unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1L : 0L) : 0L; }
            inline long long fitTo(const long long number, const int unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1LL : 0LL) : 0LL; } inline long long fitTo(const long long number, const long unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1LL : 0LL) : 0LL; } inline long long fitTo(const long long number, const long long unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1LL : 0LL) : 0LL; } inline long long fitTo(const long long number, const short unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1LL : 0LL) : 0LL; }
            inline short fitTo(const short number, const int unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1 : 0) : 0; } inline short fitTo(const short number, const long unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1 : 0) : 0; } inline short fitTo(const short number, const long long unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1 : 0) : 0; } inline short fitTo(const short number, const short unitSize) { return unitSize ? (number / unitSize) + (number % unitSize ? 1 : 0) : 0; }
    }

    /* Graphics */
    namespace Graphics {}
