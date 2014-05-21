#ifndef _SGLEO_H_
#define _SGLEO_H_

#include "Arduino.h"

void rejilla(uint8_t dx, uint8_t dy);
void drawHouse();

#ifdef __cplusplus
extern "C" {
#endif

  typedef struct{
    uint16_t x;
    uint16_t y;
  } pos_;

  union u{
    pos_ p;
    uint16_t xy[2];
  } touch;

#ifdef __cplusplus
}
#endif

#endif

