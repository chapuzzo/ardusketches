/*
*/

#ifndef SHA1_h
#define SHA1_h

#include <inttypes.h>

// SHA1 related functions

typedef struct
{
    unsigned long total[2];     /*!< number of bytes processed  */
    unsigned long state[5];     /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */

    unsigned char ipad[64];     /*!< HMAC: inner padding        */
    unsigned char opad[64];     /*!< HMAC: outer padding        */
}
sha1_context;

class Sha1
{
public:
	Sha1();
	void sha1( unsigned char *input, int ilen, unsigned char output[20] );
	void sha1_hmac( unsigned char *key, int keylen,
                unsigned char *input, int ilen,
                unsigned char output[20] );

//	friend class Cripto;
private:
	void sha1_starts( sha1_context *ctx );
	void sha1_update( sha1_context *ctx, unsigned char *input, int ilen );
	void sha1_finish( sha1_context *ctx, unsigned char output[20] );
	void sha1_hmac_starts( sha1_context *ctx, unsigned char *key, int keylen );
	void sha1_hmac_update( sha1_context *ctx, unsigned char *input, int ilen );
	void sha1_hmac_finish( sha1_context *ctx, unsigned char output[20] );
};

#endif
