#ifndef _SERPENT_API_
#define _SERPENT_API_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define     DIR_ENCRYPT     0
#define     DIR_DECRYPT     1
#define     MODE_ECB        1
#define     MODE_CBC        2
#define     MODE_CFB1       3
#define     TRUE            1
#define     FALSE           0

#define     BAD_KEY_DIR        -1
#define     BAD_KEY_MAT        -2
#define     BAD_KEY_INSTANCE   -3
#define     BAD_CIPHER_MODE    -4
#define     BAD_CIPHER_STATE   -5

#define DECRYPTION_MISMATCH -7
#define ENCRYPTION_MISMATCH -8
#define BAD_HEX_DIGIT -9
#define BAD_LENGTH -10
#define BAD_IV -11
#define BAD_NUMBER_OF_BITS_PROCESSED -12
#define BAD_INPUT -13

#define     MAX_KEY_SIZE	64
#define     MAX_IV_SIZE		16

#define MAX_XOR_TAPS_PER_BIT 7

#define r 32
#define phi 0x9e3779b9

#define BITS_PER_BYTE 8
#define BITS_PER_NIBBLE 4
#define BYTES_PER_WORD 4
#define WORDS_PER_BLOCK 4
#define WORDS_PER_KEY 8


#define BITS_PER_HEX_DIGIT BITS_PER_NIBBLE
#define NIBBLES_PER_WORD (BITS_PER_WORD/BITS_PER_NIBBLE)
#define BITS_PER_WORD (BITS_PER_BYTE*BYTES_PER_WORD)
#define BYTES_PER_IV MAX_IV_SIZE
#define BYTES_PER_BLOCK (BITS_PER_BLOCK/BITS_PER_BYTE)
#define BYTES_PER_KEY_SCHEDULE (BYTES_PER_WORD*WORDS_PER_KEY_SCHEDULE)
#define HEX_DIGITS_PER_WORD (BITS_PER_WORD/BITS_PER_HEX_DIGIT)
#define HEX_DIGITS_PER_BLOCK (HEX_DIGITS_PER_WORD*WORDS_PER_BLOCK)
#define HEX_DIGITS_PER_KEY (HEX_DIGITS_PER_WORD*WORDS_PER_KEY)

#define BITS_PER_BLOCK (BITS_PER_WORD*WORDS_PER_BLOCK)
#define WORDS_PER_IV (BYTES_PER_IV/BYTES_PER_WORD)
#define BITS_PER_KEY (BITS_PER_WORD*WORDS_PER_KEY)
#define WORDS_PER_KEY_SCHEDULE ((r+1)*WORDS_PER_BLOCK)



#define BITS_PER_SHORTEST_KEY 128
#define BITS_PER_KEY_STEP 64


#define OUTER_LOOP_MAX 400
#define INNER_LOOP_MAX 10000


#define MAX_CHARS_PER_LINE 80

typedef unsigned char BYTE;
typedef unsigned long WORD;

typedef unsigned char NIBBLE;
typedef unsigned char BIT;

typedef int permutationTable[BITS_PER_BLOCK];
typedef BYTE xorTable[BITS_PER_BLOCK][MAX_XOR_TAPS_PER_BIT+1];

typedef WORD keySchedule[r+1][WORDS_PER_BLOCK];
typedef WORD BLOCK[WORDS_PER_BLOCK];
typedef WORD KEY[WORDS_PER_KEY];


typedef struct {
  BYTE  direction;
  int   keyLen;
  char  keyMaterial[MAX_KEY_SIZE+1];
  KEY userKey;
  keySchedule KHat;
} keyInstance;

typedef struct {
  BYTE  mode;
  BYTE  IV[MAX_IV_SIZE];
  int   blockSize;
} cipherInstance;

int makeKey(keyInstance* key, BYTE direction, int keyLen,
			char* keyMaterial);
int cipherInit(cipherInstance* cipher, BYTE mode, char* IV);
int blockEncrypt(cipherInstance* cipher, keyInstance* key, BYTE* input,
                 int inputLen, BYTE* outBuffer);
int blockDecrypt(cipherInstance* cipher, keyInstance* key, BYTE* input,
                 int inputLen, BYTE* outBuffer);

#define EMBED_RCS(name, id) \
static char* _##name = id; \
static void* f_##name(void) {return (void*) _##name;}

EMBED_RCS(serpent_api_h,
          "$Id: serpent-api.h,v 1.14 1998/06/07 11:47:49 fms Exp $")

#endif
