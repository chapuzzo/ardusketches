/*
 
 */

#include <WProgram.h> 

#include "Cripto.h"

#define DELTA 0x9e3779b9
#define MX ((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (k[(p&3)^e] ^ z));

/************ static functions common to all instances ***********************/

//static inline void handle_interrupts(timer16_Sequence_t timer, volatile uint16_t *TCNTn, volatile uint16_t* OCRnA)
//{
//}


/****************** end of static functions ******************************/

Cripto::Cripto()
{
  this->hash_algorithm = 0;
  this->encryption_algorithm = 0;
  this->debug = false;
}

void Cripto::setDebugging(bool flag)
{
	this->debug = flag;
}

bool Cripto::setAlgorithm(int algorithm)
{
	bool flag = true;

	switch(algorithm){
	case MD5_HA:
		this->hash_algorithm = algorithm;
		break;
	case SHA1_HA:
		this->hash_algorithm = algorithm;		
		break;
	case AES_EA:
		this->encryption_algorithm = algorithm;
		break;
	default:
		flag = false;
	}

	return flag;
}
 
/* Esta función cifra un sólo bloque de n*32 bits!!!
btea will encode or decode n words as a single block where n > 1
    * v is the n word data vector
    * k is the 4 word key
    * n is negative for decoding
    * if n is zero result is 1 and no coding or decoding takes place, otherwise the result is zero
    * assumes 32 bit ‘long’ and same endian coding and decoding
*/

void btea(uint32_t *v, int n, uint32_t *k) {
    uint32_t y, z, sum;
    unsigned p, rounds, e;
    if (n > 1) {          /* Coding Part */
      rounds = 6 + 52/n;
      sum = 0;
      z = v[n-1];
      do {
        sum += DELTA;
        e = (sum >> 2) & 3;
        for (p=0; p<n-1; p++)
          y = v[p+1], z = v[p] += MX;
        y = v[0];
        z = v[n-1] += MX;
      } while (--rounds);
    } else if (n < -1) {  /* Decoding Part */
      n = -n;
      rounds = 6 + 52/n;
      sum = rounds*DELTA;
      y = v[0];
      do {
        e = (sum >> 2) & 3;
        for (p=n-1; p>0; p--)
          z = v[p-1], y = v[p] -= MX;
        z = v[n-1];
        y = v[0] -= MX;
      } while ((sum -= DELTA) != 0);
    }
  }

/* NOMBRE: calculateHash
 * FUNCIÓN: Calcula el hash de un texto de entrada utilizando un cifrador en bloque subyacente.
 * Utiliza el enfoque Davies-Meyer.
 * ARGS:
 *	- inputText : puntero al texto de entrada
 *	- inputTextLength : longitud del texto de entrada (en bytes)
 */
void Cripto::calculateHash(unsigned char *inputText, unsigned int inputTextLength, unsigned char *hash)
{
  unsigned int numBlocks = (inputTextLength <= HASH_LENGTH ? 1 : inputTextLength/HASH_LENGTH), i,j;
  unsigned char H[HASH_LENGTH]={HASH_IV};
  unsigned char tempBuffer[BLOCK_SIZE];

  for (i=0; i<numBlocks;i++){
     memcpy(&tempBuffer,inputText,BLOCK_SIZE);
     encrypt((unsigned char *)&tempBuffer,KEY_SIZE,(uint32_t *)&H);

     // Se actualiza el puntero de la entrada, x_i
     for (j=0; j<HASH_LENGTH;j++)
    	 H[j]=tempBuffer[j]^(*inputText++);
  }

  memcpy(hash,&H,HASH_LENGTH);

}

void Cripto::calculateHMAC2(unsigned char *inputText, unsigned int inputTextLength, uint32_t *k, unsigned char *hash)
{
  unsigned char tempHash[HASH_LENGTH];
  unsigned char tempBuffer[inputTextLength + KEY_SIZE];
  
  memcpy((void *)&tempBuffer,(void *)k,KEY_SIZE);
  memcpy((unsigned char *)&tempBuffer+KEY_SIZE, inputText,inputTextLength);
  calculateHash((unsigned char *) &tempBuffer, inputTextLength + KEY_SIZE, (unsigned char *) &tempHash);

  memcpy(&tempBuffer,k,KEY_SIZE);
  memcpy((unsigned char *)&tempBuffer + KEY_SIZE, &tempHash, HASH_LENGTH);
  calculateHash((unsigned char *)&tempBuffer, HASH_LENGTH + KEY_SIZE, (unsigned char *)hash);
}

/* FUNCIÓN: encrypt
 * ARGS:
 *	- inputText : puntero al texto en claro
 *	- inputTextLength : longitud del texto en claro (en bytes)
 *	- k[4] : clave de cifrado, en forma de array de cuatro elementos de 32 bits = clave de 128 bits.
 * SALIDA: número de bloques cifrados, -1 en caso de error
 */
int Cripto::encrypt(unsigned char *inputText, unsigned int inputTextLength, uint32_t *k)
{  
  unsigned int numBlocks = (inputTextLength <= BLOCK_SIZE ? 1 : inputTextLength/BLOCK_SIZE);
  unsigned int offset, i;

  // Padding if necessary till a full block size
  if ((offset = inputTextLength % BLOCK_SIZE) != 0)
	  memset(inputText+inputTextLength, 0x00, BLOCK_SIZE - offset);

  for (i=0; i<numBlocks;i++){
     btea((uint32_t *)inputText, BLOCK_SIZE/4,k);
     inputText+=BLOCK_SIZE;
  }

  return numBlocks;
}

/* FUNCIÓN: decrypt
 * ARGS:
 *	- inputText : puntero al texto en claro
 *	- inputTextLength : longitud del texto en claro (en bytes)
 *	- k[4] : clave de cifrado, en forma de array de cuatro elementos de 32 bits = clave de 128 bits.
 * SALIDA: número de bloques cifrados, -1 en caso de error
 */
int Cripto::decrypt(unsigned char *inputText, unsigned int inputTextLength, uint32_t *k)
{
  unsigned int numBlocks = (inputTextLength <= BLOCK_SIZE ? 1 : inputTextLength/BLOCK_SIZE), i;

  for (i=0; i<numBlocks;i++){
     btea((uint32_t *)inputText, BLOCK_SIZE/4*(-1),k);
     inputText+=BLOCK_SIZE;
  }

  return numBlocks;
}
