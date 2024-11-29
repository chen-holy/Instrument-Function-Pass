#include <stdio.h>

extern "C"
void __qy_printf(char *content) {
  printf("[qy_printf]: %s\n", content);
}