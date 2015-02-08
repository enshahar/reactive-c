#include <stdio.h>
#include <stdlib.h>

#include "reactive-c/reactive.h"

int main(void) {
  int _a = 0, _b = 0, _c = 0;
  
  observable_t a = observe(_a);
  observable_t b = observe(_b);
  observable_t c = observe(_c);

  observable_t s = script(
    await(a),
    await(b),
    await(delayed(all(a, b, c))),
    await(delayed(any(b, c))),
    await(        all(a, b, c))
  );

  FILE *fp = fopen("await.dot", "w");
  to_dot(a, fp);
  fclose(fp);

  exit(EXIT_SUCCESS);
}
