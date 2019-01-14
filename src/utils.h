/**
 * \file utils.h
 * \brief Header de utils
 * \author Laure BEDU,  Vianney TOUCHARD
 */
 
#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int a;
    int b;
} intPair;

int compare_int(const int a , const int b);
int cmp_func(const void *a, const void *b);

char prompt_char();
int clean_stdin();
char char_aleat();
int color_aleat();
int prompt_int();

int colorpair(char c);
char colorchar(int i);
int positive_modulo(int i, int n);