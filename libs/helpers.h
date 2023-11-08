#include "structs.h"
#include <stdlib.h>
#include <string.h>
#include <uriparser/Uri.h>
#include <uriparser/UriBase.h>

void wrapStrFromPTR(char *str, size_t len, const char *head, const char *tail);

void setupServerSettings(int argc, const char **argv, serverSettings *ss);
int retrieveGETQueryIntValByKey(char *req, const char *key);

int __calcFibTCO(int n, int x, int y);
int __calcFibRecusrion(int n);
int calcFibonacci(int n);
int calcDigits(int n);
