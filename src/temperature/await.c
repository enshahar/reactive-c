#include <stdlib.h>
#include <stdio.h>

#include "reactive.h"

int main(void) {
  int _a = 0, _b = 0;
  
  observable_t a = observable_from_value((void*)&_a);
  observable_t b = observable_from_value((void*)&_b);
  
  observable_from_script(
    await(a),
    await(b)
  );

  printf("b=1\n");
  _b = 1; observe_update(b);  // does nothing

  printf("a=1\n");
  _a = 1; observe_update(a);  // finalizes await(a)

  printf("a=2\n");
  _a = 2; observe_update(a);  // does nothing

  printf("b=2\n");
  _b = 2; observe_update(b);  // finalizes await(b)

  printf("b=3\n");
  _b = 3; observe_update(b);  // does nothing
  
  exit(EXIT_SUCCESS);
}