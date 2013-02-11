#ifndef _botonera_h_
#define _botonera_h_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MARGEN 4

typedef struct{
    int id;
    unsigned char valor;
    int x0,y0,x1,y1;
    unsigned int color;
    //unsigned int vora;
    //char *txt;
    int (*funcion)(void);
} boton;

typedef struct{
    int id;
    int nx,ny;
    int color;
    boton *botones;
} botonera;

extern void SetXY(unsigned int x0, unsigned int x1, unsigned int y0,unsigned int y1);
extern void Write_Data(unsigned int c);
extern void drawRect(int x1, int y1, int x2, int y2);
extern void drawRoundRect(int x1, int y1, int x2, int y2);
extern void fillRect(int x1, int y1, int x2, int y2);
extern void fillRoundRect(int x1, int y1, int x2, int y2);

void inicializa(botonera *b, int x0, int y0, int x1, int y1, int nx, int ny, int color );
void reinicia(botonera *b);

void dibuja_botonera(botonera *b);
void dibuja_boton(boton *B);
void pulsa_boton(boton *B);
void suelta_boton(boton *B);
void colorea(unsigned int color);

int parse(botonera *b, int x, int y);
boton *parse_b(botonera *b, int x, int y);

void bind(boton *b, int (*funcion)(void));
int limpia(void);
int redibujaB2(void);
void valor(botonera *b,char *res);

void imprime(botonera *b);

#ifdef __cplusplus
}
#endif

#endif
