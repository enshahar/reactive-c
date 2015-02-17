#include <stdio.h>
#include <stdlib.h>

#include "reactive-c/reactive.h"

int main(void) {
  int _a = 0, _b = 0, _c = 0;
  
  observable_t a = observe(int, _a);
  observable_t b = observe(int, _b);
  observable_t c = observe(int, _c);

  script(
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
