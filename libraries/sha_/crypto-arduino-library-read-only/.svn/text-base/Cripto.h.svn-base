/*
*/

#ifndef Cripto_h
#define Cripto_h

#define	MD5_HA	1
#define	SHA1_HA	2
#define	AES_EA	3

// Longitu del hash generado (en bytes)
#define	HASH_LENGTH	(128/8)
#define	HASH_IV	0x9e, 0x37, 0x79, 0xb9, 0x9e, 0x37, 0x79, 0xb9, \
		0x9e, 0x37, 0x79, 0xb9, 0x9e, 0x37, 0x79, 0xb9

// Tamaño del bloque del cifrador XXTEA (en bytes)
#define	BLOCK_SIZE	(128/8)
#define	KEY_SIZE	(128/8)

#include <inttypes.h>

class Cripto
{
public:
	Cripto();
	bool setAlgorithm(int algorithm);  // set the cryptographyc (hash, encryption) algorithm to use
	void setDebugging(bool flag);
	//void calculateHash(void);
	void calculateHash(unsigned char *inputText, unsigned int len, unsigned char *hash);
	void calculateHash2(unsigned char *inputText, unsigned int len, unsigned char *hash);
	void calculateHMAC(unsigned char *inputText, unsigned int inputTextLength, uint32_t *k, unsigned char *hash);
	void calculateHMAC2(unsigned char *inputText, unsigned int inputTextLength, uint32_t *k, unsigned char *hash);

	int encrypt(unsigned char *inputText, unsigned int inputTextLength, uint32_t *k);
	int decrypt(unsigned char *inputText, unsigned int inputTextLength, uint32_t *k);
private:
	uint8_t hash_algorithm;               // index into the channel data for this servo
	uint8_t encryption_algorithm;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH    
	bool debug;
};

#endif
