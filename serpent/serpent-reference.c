
#include "serpent-api.h"
#include "serpent-tables.h"
#include "serpent-reference.h"
#include "serpent-aux.h"
#include "serpent-aux.c"

EMBED_RCS(serpent_reference_c,
          "$Id: serpent-reference.c,v 1.42 1998/06/10 13:50:31 fms Exp $")

int makeKey(keyInstance *key, BYTE direction, int keyLen,
			char *keyMaterial) {

  int result;

  if ((keyLen%BITS_PER_WORD)
      || (keyLen > BITS_PER_KEY)
      || (keyLen < BITS_PER_SHORTEST_KEY)) {
    return BAD_KEY_MAT;
  }
  key->direction = direction;
  key->keyLen = keyLen;

  if (keyMaterial) {
    strncpy(key->keyMaterial, keyMaterial, HEX_DIGITS_PER_KEY + 1);
  }

  result = stringToWords(key->keyMaterial, key->userKey, WORDS_PER_KEY);
  if (result != TRUE) {
    return BAD_KEY_MAT;
  }

  if (keyLen < BITS_PER_KEY) {
    shortToLongKey(key->userKey, keyLen);
  }

  makeSubkeys(key->userKey, key->KHat);
  return TRUE;
}


int cipherInit(cipherInstance* cipher, BYTE mode, char* IV) {

  int result;

  cipher->mode = mode;

  switch (mode) {
    case MODE_ECB:
      return TRUE;
    case MODE_CFB1:
    case MODE_CBC:

      result = stringToWords(IV, (WORD*) cipher->IV, WORDS_PER_IV);
      if (result != TRUE) {
        return BAD_IV;
      }
      return TRUE;
    default:
      return BAD_CIPHER_MODE;
  }
}



int blockEncrypt(cipherInstance* cipher, keyInstance* key, BYTE* input, int
                 inputLen, BYTE* outBuffer) {
  if (key->direction != DIR_ENCRYPT) {
    return BAD_KEY_MAT;
  }
  return blockEncryptOrDecrypt(cipher, key, input, inputLen, outBuffer);
}



int blockDecrypt(cipherInstance* cipher, keyInstance* key, BYTE* input, int
                 inputLen, BYTE* outBuffer) {

  if (key->direction != DIR_DECRYPT) {
    return BAD_KEY_MAT; /* see comments in blockEncrypt */
  }
  return blockEncryptOrDecrypt(cipher, key, input, inputLen, outBuffer);
}

int blockEncryptOrDecrypt(cipherInstance* cipher, keyInstance* key, BYTE*
                          input, int inputLen, BYTE* outBuffer) {

  int i, numBlocks, bytesLeftOver, result;

  numBlocks = inputLen / BITS_PER_BLOCK;
  bytesLeftOver = inputLen % BITS_PER_BLOCK;

  for (i=0; i<numBlocks; i++) {
    result = doOneBlock((WORD*)(input + i*WORDS_PER_BLOCK),
               (WORD*)(outBuffer + i*WORDS_PER_BLOCK), cipher, key);
    if (result != TRUE) {
      return BAD_CIPHER_STATE;
    }
  }
  return numBlocks*BITS_PER_BLOCK;
}


int doOneBlock(BLOCK input, BLOCK output,
               cipherInstance* cipher, keyInstance* key) {
  int i;
  BIT plainTextBit, cipherTextBit;
  BLOCK temp;

  switch (key->direction) {
    case DIR_ENCRYPT:
      switch (cipher->mode) {
        case MODE_ECB:
          encryptGivenKHat(input, key->KHat, output);
          break;
        case MODE_CBC:
          for (i=0; i < WORDS_PER_BLOCK; i++) {
            temp[i] = input[i] ^ ((WORD*) cipher->IV)[i];
          }
          encryptGivenKHat(temp, key->KHat, output);
          for (i=0; i < WORDS_PER_BLOCK; i++) {
            ((WORD*) (cipher->IV))[i] = output[i];
          }
          break;
        case MODE_CFB1:

          for (i=0; i<BITS_PER_BLOCK; i++) {
            encryptGivenKHat((WORD*)(cipher->IV), key->KHat, temp);
            plainTextBit = getBit(input, i);
            cipherTextBit = getBit(temp, BITS_PER_BLOCK-1) ^ plainTextBit;
            setBit(output, i, cipherTextBit);
            shiftBlockLeft((WORD*)(cipher->IV), cipherTextBit);
          }
          break;
        default:
          return BAD_CIPHER_MODE;
      }
      break;
    case DIR_DECRYPT:
      switch (cipher->mode) {
        case MODE_ECB:
          decryptGivenKHat(input, key->KHat, output);
          break;
        case MODE_CBC:
          decryptGivenKHat(input, key->KHat, temp);
          for (i=0; i < WORDS_PER_BLOCK; i++) {
            output[i] = temp[i] ^ ((WORD*) cipher->IV)[i];
          }
          for (i=0; i < WORDS_PER_BLOCK; i++) {
            ((WORD*) cipher->IV)[i] = input[i];
          }
          break;
        case MODE_CFB1:
          for (i=0; i<BITS_PER_BLOCK; i++) {
            encryptGivenKHat((WORD*)(cipher->IV), key->KHat, temp);
            cipherTextBit = getBit(input, i);
            plainTextBit = getBit(temp, BITS_PER_BLOCK-1) ^ cipherTextBit;
            setBit(output, i, plainTextBit);
            shiftBlockLeft((WORD*)(cipher->IV), cipherTextBit);
          }
          break;
        default:
          return BAD_CIPHER_MODE;
      }
      break;
    default:
      return BAD_KEY_DIR;
  }
  return TRUE;
}

void setBit(WORD x[], int p, BIT v) {

  if (v) {
    x[p/BITS_PER_WORD] |= ((WORD) 0x1 << p%BITS_PER_WORD);
  } else {
    x[p/BITS_PER_WORD] &= ~((WORD) 0x1 << p%BITS_PER_WORD);
  }
}

BIT getBit(WORD x[], int p) {

  return (BIT) ((x[p/BITS_PER_WORD]
                 & ((WORD) 0x1 << p%BITS_PER_WORD)) >> p%BITS_PER_WORD);
}

BIT getBitFromWord(WORD x, int p) {
  return (BIT) ((x & ((WORD) 0x1 << p)) >> p);
}
BIT getBitFromNibble(NIBBLE x, int p) {
  return (BIT) ((x & (0x1 << p)) >> p);
}

NIBBLE getNibble(WORD x, int p) {

  return (NIBBLE) (0xf & (x >> (p*BITS_PER_NIBBLE)));
}

NIBBLE makeNibble(BIT b0, BIT b1, BIT b2, BIT b3) {

  return (NIBBLE) (b0 | (b1 << 1) | (b2 << 2) | (b3 << 3));
}

void xorBlock(BLOCK in1, BLOCK in2, BLOCK out) {
  int i;
  for (i = 0; i < WORDS_PER_BLOCK; i++) {
    out[i] = in1[i] ^ in2[i];
  }
}

void applyPermutation(permutationTable t, BLOCK input, BLOCK output) {

  int p;
  for (p=0; p<WORDS_PER_BLOCK; p++) {
    output[p] = 0;
  }
  for (p=0; p<BITS_PER_BLOCK; p++) {
    setBit(output, p, getBit(input, t[p]));
  }
}

void applyXorTable(xorTable t, BLOCK input, BLOCK output) {

  int i, j;
  BIT b;
  for (i = 0; i < BITS_PER_BLOCK; i++) {
    b = 0;
    j = 0;
    while (t[i][j] != MARKER) {
      b ^= getBit(input, t[i][j]);
      j++;
    }
    setBit(output, i, b);
  }
}

NIBBLE S(int box, NIBBLE input) {

  return SBox[box][input];
}

NIBBLE SInverse(int box, NIBBLE output) {

  return SBoxInverse[box][output];
}

WORD rotateLeft(WORD x, int p) {
  return ((x << p) | (x >> (BITS_PER_WORD-p))) & 0xffffffff;
}

void shiftBlockLeft(BLOCK b, BIT in) {
  int i;
  for (i=WORDS_PER_BLOCK-1; i>0; i--) {
    b[i] <<= 1;
    setBit(&b[i], 0, getBit(&b[i-1], BITS_PER_WORD-1));
  }
  b[0] <<= 1;
  setBit(&b[0], 0, in);
}

/* -------------------------------------------------- */
/* Short key support */

void shortToLongKey(KEY key, int bitsInShortKey) {

  key[bitsInShortKey/BITS_PER_WORD] |=
    ((WORD) 1) << (bitsInShortKey%BITS_PER_WORD);
}

void IP(BLOCK input, BLOCK output) {
  applyPermutation(IPTable, input, output);
}

void FP(BLOCK input, BLOCK output) {
  applyPermutation(FPTable, input, output);
}

void IPInverse(BLOCK output, BLOCK input) {
  applyPermutation(FPTable, output, input);
}

void FPInverse(BLOCK output, BLOCK input) {
  applyPermutation(IPTable, output, input);
}

void SHat(int box, BLOCK input, BLOCK output) {
  int iWord, iNibble;
  for (iWord = 0; iWord < WORDS_PER_BLOCK; iWord++) {
    output[iWord] = 0;
    for (iNibble = 0; iNibble < NIBBLES_PER_WORD; iNibble++) {
      output[iWord] |= ((WORD) S(box, getNibble(input[iWord], iNibble)))
                        << (iNibble*BITS_PER_NIBBLE);
    }
  }
}

void SHatInverse(int box, BLOCK output, BLOCK input) {
  int iWord, iNibble;
  for (iWord = 0; iWord < WORDS_PER_BLOCK; iWord++) {
    input[iWord] = 0;
    for (iNibble = 0; iNibble < NIBBLES_PER_WORD; iNibble++) {
      input[iWord] |= ((WORD) SInverse(box, getNibble(output[iWord], iNibble)))
                        << (iNibble*BITS_PER_NIBBLE);
    }
  }
}

void LT(BLOCK input, BLOCK output) {

  applyXorTable(LTTable, input, output);
}

void LTInverse(BLOCK output, BLOCK input) {

  applyXorTable(LTTableInverse, output, input);
}

void R(int i, BLOCK BHati, keySchedule KHat, BLOCK BHatiPlus1) {

  BLOCK xored, SHati;

  xorBlock(BHati, KHat[i], xored);
  SHat(i, xored, SHati);
  if ( (0 <= i) && (i <= r-2) ) {
    LT(SHati, BHatiPlus1);
  } else if (i == r-1) {
    xorBlock(SHati, KHat[r], BHatiPlus1);
  } else {
    printf("ERROR: round %d is out of 0..%d range", i, r-1);
    exit(1);
  }

#ifdef SHOW_INTERNALS
  printf("R[%d]", i);
  render("=", BHatiPlus1, WORDS_PER_BLOCK);
#endif
}

void RInverse(int i, BLOCK BHatiPlus1, keySchedule KHat, BLOCK BHati) {

  BLOCK xored, SHati;

  if ( (0 <= i) && (i <= r-2) ) {
    LTInverse(BHatiPlus1, SHati);
  } else if (i == r-1) {
    xorBlock(BHatiPlus1, KHat[r], SHati);
  } else {
    printf("ERROR: round %d is out of 0..%d range", i, r-1);
    exit(1);
  }
  SHatInverse(i, SHati, xored);
  xorBlock(xored, KHat[i], BHati);

#ifdef SHOW_INTERNALS
  printf("Rinv[%d]", i);
  render("=", BHati, WORDS_PER_BLOCK);
#endif
}



void makeSubkeysBitslice(KEY userKey, keySchedule K) {

  int i, j, l, whichS;
  NIBBLE input, output;
  WORD k[132], raw_w[140];
  WORD* w = &raw_w[8];

  for (i = -8; i < 0; i++) {
    w[i] = userKey[i+8];
  }

  for (i = 0; i < 132; i++) {
    w[i] = rotateLeft(w[i-8] ^ w[i-5] ^ w[i-3] ^ w[i-1] ^ phi ^ i, 11);
  }

  for (i = 0; i < r+1; i++) {
    whichS = (r + 3 - i) % r;
    k[0+4*i] = k[1+4*i] = k[2+4*i] = k[3+4*i] = 0;
    for (j = 0; j < 32; j++) {
      input = makeNibble(getBitFromWord(w[0+4*i], j),
                         getBitFromWord(w[1+4*i], j),
                         getBitFromWord(w[2+4*i], j),
                         getBitFromWord(w[3+4*i], j));
      output = S(whichS, input);
      for (l = 0; l < 4; l++) {
        k[l+4*i] |= ((WORD) getBitFromNibble(output, l)) << j;
      }
    }
  }

  for (i = 0; i < 33; i++) {
    for (j = 0; j < 4; j++) {
      K[i][j] = k[4*i+j];
    }
#ifdef SHOW_INTERNALS
    printf("SK[%d]", i);
    render("=", K[i], WORDS_PER_BLOCK);
#endif
  }
}


void makeSubkeys(KEY userKey, keySchedule KHat) {

  int i;
  keySchedule K;

#ifdef SHOW_INTERNALS
  render("LONG_KEY=", userKey, WORDS_PER_KEY);
#endif

  makeSubkeysBitslice(userKey, K);

  for (i = 0; i < 33; i++) {
    IP(K[i], KHat[i]);

#ifdef SHOW_INTERNALS
    printf("SK^[%d]", i);
    render("=", KHat[i], WORDS_PER_BLOCK);
#endif
  }

}


void encryptGivenKHat(BLOCK plainText, keySchedule KHat, BLOCK cipherText) {

  BLOCK BHat;
  int i;

  IP(plainText, BHat);
  for (i = 0; i < r; i++) {
    R(i, BHat, KHat, BHat);
  }
  FP(BHat, cipherText);
}

void decryptGivenKHat(BLOCK cipherText, keySchedule KHat, BLOCK plainText) {

  BLOCK BHat;
  int i;

  FPInverse(cipherText, BHat);
  for (i = r-1; i >=0; i--) {
    RInverse(i, BHat, KHat, BHat);
  }
  IPInverse(BHat, plainText);
}

