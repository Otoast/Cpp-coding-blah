#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  int i;
  for(i = 0; str[i] != '\0'; ++i);
  return i;
}

unsigned int find(char str[], char character) {
int i = 0;
char charCheck = str[0];
while(charCheck != character && charCheck != '\0'){
  ++i;
  charCheck = str[i];
  }

return i;
}

bool equalStr(char str1[], char str2[]) {
  int i = 0;
  char charAt1 = str1[0];
  char charAt2 = str2[0];
  while (charAt1 != '\0' && charAt2 != '\0'){
    if (charAt1 != charAt2) return false;
    charAt1 = str1[++i];
    charAt2 = str2[i];
  }
  return (charAt1 == charAt2)? true : false;
}