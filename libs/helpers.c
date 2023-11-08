#include "structs.h"
#include <stdlib.h>
#include <string.h>
#include <uriparser/Uri.h>
#include <uriparser/UriBase.h>

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

int retrieveGETQueryIntValByKey(char *req, const char *key) {
  int result = 0;

  const char *uriHead = strchr(req, ' ') + 1;
  const char *uriTail = strchr(uriHead, ' ');
  size_t uriLen = uriTail - uriHead + 1;
  char strUri[uriLen];
  wrapStrFromPTR(strUri, uriLen, uriHead, uriTail);

  UriUriA uri;
  const char *errorPos;
  if (uriParseSingleUriA(&uri, strUri, &errorPos) == URI_SUCCESS) {
    UriQueryListA *querylist;
    int itemCount;
    if (uriDissectQueryMallocA(&querylist, &itemCount, uri.query.first,
                               uri.query.afterLast) == URI_SUCCESS) {
      while (itemCount--) {
        if (strcmp(querylist->key, key) == 0) {
          result = atoi(querylist->value);
          break;
        }
        querylist = querylist->next;
      }
      uriFreeQueryListA(querylist);
    }
  }
  return result;
}

// tail call optimization
int __calcFibTCO(int n, int x, int y) {
  if (n == 0) {
    return x;
  }
  if (n == 1) {
    return y;
  }
  return __calcFibTCO(n - 1, y, y + x);
}

int __calcFibRecusrion(int n) {
  if (n <= 1) {
    return n;
  }
  return __calcFibRecusrion(n - 1) + __calcFibRecusrion(n - 2);
}

int calcFibonacci(int n) {
  // return __calcFibTOC(n, 0, 1);
  return __calcFibRecusrion(n);
}
