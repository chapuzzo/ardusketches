#include <stdio.h>
#include "botonera.h"

#ifdef ARDUINO
#include "UTFT.h"
extern UTFT myGLCD;
#endif

botonera Bo1;
botonera Bo2;


void inicializa(botonera *b, int x0, int y0, int x1, int y1, int nx, int ny, int color ){
    int ancho = x1 - x0;
    int alto = y1 - y0;
    int i,j;
    int anchob = ancho / nx - MARGEN;
    int altob = alto / ny - MARGEN;
    b->color = color;
    b->id=1;
    b->nx = nx;
    b->ny = ny;
    boton *B;
    b->botones = (boton *)calloc(nx*ny, sizeof(boton));
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            B = &b->botones[ny*i+j];
            B->id = ny*i+j;
            B->valor = 0;
            B->color = color;
            //B->vora = ~color;
            B->x0 = x0 + (i+0.5)*MARGEN + i*anchob;
            B->y0 = y0 + (j+0.5)*MARGEN + j*altob;
            B->x1 = B->x0 + anchob;
            B->y1 = B->y0 + altob;
            B->funcion = NULL;
        }
    }
}


void reinicia(botonera *b){
    int i,j;
    boton *B;
    for (i = 0; i < b->nx; i++){
        for (j = 0; j < b->ny; j++){
            B = &b->botones[b->ny*i+j];
            //~ B->id = b->ny*i+j;
            B->valor = 0;
            //~ B->color = b->color;
        }
    }

}

#ifndef ARDUINO
void imprime(botonera *b){
    int i,j;
    boton *B;
    for (i = 0; i < b->nx; i++){
            for (j = 0; j < b->ny; j++){
                B = &b->botones[b->ny*i+j];
                printf("boton #%d: (x0=%d, y0=%d); (x1=%d, y1=%d)\n",
                        B->id, B->x0, B->y0, B->x1, B->y1);
            }
        }
}
#endif


#ifdef ARDUINO
void dibuja_botonera(botonera *b){
    int x = b->nx * b->ny - 1;
    while (x >= 0){
        dibuja_boton(&b->botones[x]);
        x--;
    }
}

void dibuja_boton(boton *B){
    colorea(B->color);
    myGLCD.fillRoundRect(B->x0, B->y0, B->x1, B->y1);
    colorea(~B->color);
    myGLCD.drawRoundRect(B->x0, B->y0, B->x1, B->y1);
}

void pulsa_boton(boton *B){
    //B->vora = B->vora << 12|B->vora >> 4;
    //B->vora %= 0xFFFF;
    //~ colorea(~B->vora);
    //~ myGLCD.drawRoundRect(B->x0, B->y0, B->x1, B->y1);
    B->valor ^= 1;
    if (B->valor)
        colorea(~B->color);
    else
        colorea(B->color);
    myGLCD.fillRoundRect(B->x0, B->y0, B->x1, B->y1);
}

void suelta_boton(boton *B){
    //B->vora = B->vora << 12|B->vora >> 4;
    //B->vora %= 0xFFFF;
    colorea(~B->color);
    myGLCD.drawRoundRect(B->x0, B->y0, B->x1, B->y1);
    //dibuja_boton(B);
}

void colorea(unsigned int color){
    myGLCD.setColor((color & 0xF800)>>8,(color & 0x07E0)>>2,(color & 0x001F)<<3);
}

int limpia(void){
    reinicia(&Bo1);
    dibuja_botonera(&Bo1);
    redibujaB2();
}

int redibujaB2(void){
    reinicia(&Bo2);
    dibuja_botonera(&Bo2);
}

#endif

void valor(botonera *b,char *res){
    //~ *res = (char*)calloc(b->nx*b->ny,sizeof(char));
    int n = b->nx * b->ny;
    res[n--] = 0;
    while (n >= 0){
        res[n] = b->botones[n].valor?'A':'B';
        n--;
    }
}

boton *parse_b(botonera *b, int x, int y){
    int n = b->nx * b->ny - 1 ;
    while (n >= 0){
        if (x >= b->botones[n].x0 && x <= b->botones[n].x1 &&
            y >= b->botones[n].y0 && y <= b->botones[n].y1)
        {
            return &b->botones[n];
        }
        n--;
    }
    return NULL;
}

#ifndef ARDUINO
int parse(botonera *b, int x, int y){
    int n = b->nx * b->ny - 1 ;
    while (n >= 0){
        if (x >= b->botones[n].x0 && x <= b->botones[n].x1 &&
            y >= b->botones[n].y0 && y <= b->botones[n].y1)
            {
                return b->botones[n].id;
            }
        n--;
    }
    return -1;
}
#endif


void bind(boton *b, int (*f)(void)){
    b->funcion = f;
}

#ifndef ARDUINO
int main(int argc, char *argv[]){
    inicializa(&Bo1,0,0,240,240,5,5,0xAAAA);
    imprime(&Bo1);
    inicializa(&Bo2,0,240,32,320,2,2,0xAAAA);
    imprime(&Bo2);
    //~ printf("%d\n",parse(&botonera,200,110));
    //~ printf("%d,%d,%d,%d\n", 0xFFFF, (0xFFFF & 0xF800) >> 11, (0xFFFF & 0x07E0) >> 5, 0xFFFF & 0x001F);
}
#endif
