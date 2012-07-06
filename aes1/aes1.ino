#include <aes256.h>


void setup() {
 aes256_context ctx; 
 uint8_t key[32];
 uint8_t buf[16], i;

 /* put a test vector */
 for (i = 0; i < sizeof(buf);i++) buf[i] = i * 16 + i;
 for (i = 0; i < sizeof(key);i++) key[i] = i; // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
