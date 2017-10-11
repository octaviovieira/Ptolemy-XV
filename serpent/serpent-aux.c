
#include "serpent-api.h"
#include "serpent-aux.h"

EMBED_RCS(serpent_aux_c,
          "$Id: serpent-aux.c,v 1.5 1998/06/07 08:12:33 fms Exp $")

int checkHexNumber(char* s) {

  int i = 0;

  if (s) {
    while (s[i]) {
      if(isxdigit((int) s[i])) {
        i++;
      } else {
        return -1;
      }
    }
  }
  return i;
}

char hex(int n) {

  if ((0 <= n)  && (n <= 9)) {
    return (char) (n + '0');
  } else if ((10<=n) && (n <= 15)) {
    return (char) (n - 10 + 'a');
  } else {
    printf("ERROR: %d can't be converted to a hex digit\n", n);
    exit(1);
  }
}

int stringToWords(char* s, WORD w[], int words) {

  int digits, i, highestWordWithData;
  char buffer[HEX_DIGITS_PER_WORD+1];

  digits = checkHexNumber(s);

  if (digits < 0) {
    return BAD_HEX_DIGIT;
  }
  if ((digits > words*HEX_DIGITS_PER_WORD) || (digits%HEX_DIGITS_PER_WORD)) {
    return BAD_LENGTH;
  }

  highestWordWithData = digits/HEX_DIGITS_PER_WORD;
  for (i = highestWordWithData; i < words; i++) {
    w[i] = 0;
  }

  buffer[HEX_DIGITS_PER_WORD] = 0;
  for (i = 0; i < highestWordWithData; i++) {

    digits -= HEX_DIGITS_PER_WORD;

    strncpy(buffer, &s[digits], HEX_DIGITS_PER_WORD);
    sscanf(buffer, "%lx", &w[i]);
  }

  return TRUE;
}

void printHeader(char* filename, char* mode, char* test) {
  printf(
         "=========================\n\n"
         "FILENAME:  \"%s.txt\"\n\n"
         "%s\n"
         "%s\n\n"
         "Algorithm Name: Serpent\n"
         "Principal Submitter: Ross Anderson, Eli Biham, Lars Knudsen\n\n"
         "==========\n\n",
         filename, mode, test
         );
}


char* wordsToString(WORD x[], int size, char* buffer) {

  int i, j=0;
  for (i = size-1; i>=0; i--, j+=HEX_DIGITS_PER_WORD) {
    sprintf(&buffer[j], "%08lx", x[i]);
  }
  buffer[j] = 0;
  return buffer;
}

void render(char* label, WORD x[], int size) {

  int i;
  printf("%s", label);
  for (i = size-1; i>=0; i--) {
    printf("%08lx", x[i]);
  }
  printf("\n");
}
