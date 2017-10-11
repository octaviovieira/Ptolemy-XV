
#ifndef _SERPENT_REFERENCE_
#define _SERPENT_REFERENCE_

#include "serpent-api.h"
EMBED_RCS(serpent_reference_h,
          "$Id: serpent-reference.h,v 1.4 1998/06/07 08:07:21 fms Exp $")

int blockEncryptOrDecrypt(cipherInstance* cipher, keyInstance* key,
                          BYTE* input, int inputLen, BYTE* outBuffer);
int makeUserKeyFromKeyMaterial(char* rawHexData, WORD* userKey);
int doOneBlock(BLOCK input, BLOCK output,
               cipherInstance* cipher, keyInstance* key);

void IP(BLOCK input, BLOCK output);
void FP(BLOCK input, BLOCK output);
void IPInverse(BLOCK output, BLOCK input);
void FPInverse(BLOCK output, BLOCK input);
void SHat(int box, BLOCK input, BLOCK output);
void SHatInverse(int box, BLOCK output, BLOCK input);
void LT(BLOCK input, BLOCK output);
void LTInverse(BLOCK output, BLOCK input);
void R(int i, BLOCK BHati, keySchedule KHat, BLOCK BHatiPlus1);
void RInverse(int i, BLOCK BHatiPlus1, keySchedule KHat, BLOCK BHati);
void makeSubkeysBitslice(KEY userKey, keySchedule K);
void makeSubkeys(KEY userKey, keySchedule KHat);
void encryptGivenKHat(BLOCK plainText, keySchedule KHat, BLOCK cipherText);
void decryptGivenKHat(BLOCK cipherText, keySchedule KHat, BLOCK plainText);

void shortToLongKey(KEY key, int bitsInShortKey);

void setBit(WORD x[], int p, BIT v);
BIT getBit(WORD x[], int p);
BIT getBitFromWord(WORD x, int p);
BIT getBitFromNibble(NIBBLE x, int p);
NIBBLE getNibble(WORD x, int p);
NIBBLE makeNibble(BIT b0, BIT b1, BIT b2, BIT b3);
void xorBlock(BLOCK in1, BLOCK in2, BLOCK out);
void applyPermutation(permutationTable t, BLOCK input, BLOCK output);
void applyXorTable(xorTable t, BLOCK input, BLOCK output);
NIBBLE S(int box, NIBBLE input);
NIBBLE SInverse(int box, NIBBLE output);
WORD rotateLeft(WORD x, int p);
void shiftBlockLeft(BLOCK b, BIT in);

#endif
