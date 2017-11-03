/*
  $Id: ecb_d_m.c,v 1.7 1998/06/10 20:04:46 fms Exp $

  # This file is part of the C reference implementation of Serpent.
  #
  # Written by Frank Stajano,
  # Olivetti Oracle Research Laboratory <http://www.orl.co.uk/~fms/> and
  # Cambridge University Computer Laboratory <http://www.cl.cam.ac.uk/~fms27/>.
  # 
  # (c) 1998 Olivetti Oracle Research Laboratory (ORL)
  #
  # Original (Python) Serpent reference development started on 1998 02 12.
  # C implementation development started on 1998 03 04.
  #
  # Serpent cipher invented by Ross Anderson, Eli Biham, Lars Knudsen.
  # Serpent is a candidate for the Advanced Encryption Standard.

*/

/* -------------------------------------------------- */
#include <assert.h>
#include "serpent-api.h"
#include "serpent-aux.h"
/* -------------------------------------------------- */
EMBED_RCS(ecb_d_m_c,
          "$Id: ecb_d_m.c,v 1.7 1998/06/10 20:04:46 fms Exp $")

int main(void) {
  int i, j, bitsPerShortKey, result;
  BLOCK plainText, cipherText, PT_9998;
  KEY binaryKey;
  char asciiKey[HEX_DIGITS_PER_KEY+1];
  keyInstance key;
  cipherInstance cipher;


  /* The hack that remembers PT_9998 only works if... */
  assert(BITS_PER_KEY <= 2*BITS_PER_BLOCK);
  /* ...otherwise we'd have to remember more than just PT_9998. */

  printHeader("ecb_d_m", "Electronic Codebook (ECB) Mode - DECRYPTION",
              "Monte Carlo Test");

  for(bitsPerShortKey=BITS_PER_SHORTEST_KEY; bitsPerShortKey<=BITS_PER_KEY;
      bitsPerShortKey+=BITS_PER_KEY_STEP) {
    result = stringToWords("00000000000000000000000000000000", cipherText,
                           WORDS_PER_BLOCK);
    if (result != TRUE) goto error;

    printf("KEYSIZE=%d\n\n", bitsPerShortKey);

    /* Construct (backwards) an ascii key of all 0s, of length
       bitsPerShortKey bits. */
    i=bitsPerShortKey/BITS_PER_HEX_DIGIT;
    asciiKey[i] = 0; /* terminating null */ 
    for (i--; i >=0; i--) {
      asciiKey[i] = '0';
    }

    result = cipherInit(&cipher, MODE_ECB, 0);
    if (result != TRUE) goto error;

    for(i=0; i<OUTER_LOOP_MAX; i++) {
      result = makeKey(&key, DIR_DECRYPT, bitsPerShortKey, asciiKey);
      if (result != TRUE) goto error;

      /* NIST SPEC: Record i, KEY_i, CT_0 */
      printf("I=%d\n", i);
      render("KEY=", key.userKey, bitsPerShortKey/BITS_PER_WORD);
      render("CT=", cipherText, WORDS_PER_BLOCK);
      
      for (j=0; j<INNER_LOOP_MAX; j++) {
        /* NIST SPEC: IB_j=CT_j */
        /* Implicit (no IB var used) */

        /* encrypt */
        result = blockDecrypt(&cipher, &key, (BYTE*) cipherText, 
                              BITS_PER_BLOCK, (BYTE*) plainText);
        if (result < 0) {
          goto error;
        } else if (result != BITS_PER_BLOCK) {
          result = BAD_NUMBER_OF_BITS_PROCESSED;
          goto error;
        }

        /* NIST SPEC: CT_j+1 = PT_j */
        memcpy(cipherText, plainText, BYTES_PER_BLOCK);

        if (j == INNER_LOOP_MAX-2) {
          memcpy(PT_9998, plainText, BYTES_PER_BLOCK);
        }
      }
      
      /* NIST SPEC: Record PT_j */
      render("PT=", cipherText, WORDS_PER_BLOCK);
      printf("\n");

      /* NIST SPEC: KEY_i+1 = KEY_i xor last n bits of PT, where n=key size */
      /* First, juxtapose PT_9999 and PT_9998 into binaryKey; */
      memcpy(binaryKey, PT_9998, BYTES_PER_BLOCK);
      memcpy(&binaryKey[WORDS_PER_BLOCK], plainText, BYTES_PER_BLOCK);
      memmove(binaryKey, 
             &binaryKey[(BITS_PER_KEY-bitsPerShortKey)/BITS_PER_WORD], 
             bitsPerShortKey/BITS_PER_BYTE);
      /* Then, xor this stuff with the previously used key. */
      for (j=0; j<bitsPerShortKey/BITS_PER_WORD; j++) {
        binaryKey[j] ^= key.userKey[j];
      }
      
      /* NB: the NIST API does not provide callers with a way to specify a
         new key in binary format, so we have to go through the rigmarole
         of computing the new key in binary and converting it to ascii so
         that we can feed it to makeKey which will internally reconvert it
         back to binary--yechh. Note that just poking a new binary key in
         key.userKey won't work, as we need to invoke the routine that
         makes the subkeys. */
      wordsToString(binaryKey,
                    bitsPerShortKey/BITS_PER_WORD, asciiKey);
      result = makeKey(&key, DIR_DECRYPT, bitsPerShortKey, asciiKey);
      if (result != TRUE) goto error;

      /* NIST SPEC: CT_0 = PT_9999 */
      memcpy(cipherText, plainText, BYTES_PER_BLOCK);
    }
      
    printf("==========\n\n");
  }
  exit(0);

error:
  printf("Error %d (sorry, see aes.h to see what this means)\n", result);
  exit(result);
}
