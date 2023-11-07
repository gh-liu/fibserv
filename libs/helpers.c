#include "structs.h"
#include <stdlib.h>
#include <string.h>

void wrapStrFromPTR(char *str, size_t len, const char *head, const char *tail) {
  for (size_t i = 0; head != tail; head++)
    str[i++] = *head;

  str[len - 1] = '\0';
}

void setupServerSettings(int argc, const char **argv, serverSettings *ss) {
  while (argc-- > 1) {
    // key
    const char *keyHead = argv[argc];
    const char *keyPos = strchr(keyHead, '=');
    const size_t keyLen = keyPos - keyHead + 1;
    char key[keyLen];
    wrapStrFromPTR(key, keyLen, keyHead, keyPos);
    // value
    const char *valHead = keyHead + keyLen;
    const char *valPos = strchr(valHead, '\0');
    const size_t valLen = valPos - valHead;
    char val[valLen];
    // wrapStrFromPTR(val, valLen, valHead, valPos);
    for (size_t i = 0; valHead <= valPos; valHead++) {
      val[i++] = *valHead;
    }

    if (strcmp(key, "thread_count")) {
      ss->threadCount = atoi(val);
    }
  }
}
