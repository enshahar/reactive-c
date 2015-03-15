// demo for "add"

#include <stdlib.h>

#include "unit/test.h"

#include "reactive-c/api.h"

void _addi(observation_t ob) {
  (*(int*)ob->observer) =
    (*(int*)(ob->observeds[0])) + (*(int*)(ob->observeds[1]));
}

void _addd(observation_t ob) {
  (*(double*)ob->observer) =
    (*(double*)(ob->observeds[0])) + (*(double*)(ob->observeds[1]));
}

observable_t addi(observable_t a, observable_t b) {
  return observe(each(a, b), _addi, int);
}

observable_t addd(observable_t a, observable_t b) {
  return observe(each(a, b), _addd, double);
}

int main(void) {
  int _var1, _var2;
  
  // create two observable values
  observable_t var1 = observe(int, _var1);
  observable_t var2 = observe(int, _var2);
  
  // and one observable combination
  observable_t var3 = addi(var1, var2);

  // simulate some events on all
  _var1 = 1;  observe_update(var1);
  _var2 = 2;  observe_update(var2);

  // at this point var3 is already updated, let's check that:

  capture_printf("%d + %d = %d\n", _var1, _var2, *(int*)observable_value(var3));

  assert_output_was( "1 + 2 = 3\n" );
  clear_output();

  _var1 = 3;  observe_update(var1);
  _var2 = 5;  observe_update(var2);

  // at this point var3 is already (again) updated, let's check that (again):

  capture_printf("%d + %d = %d\n", _var1, _var2, *(int*)observable_value(var3));

  assert_output_was( "3 + 5 = 8\n" );

  exit(EXIT_SUCCESS);
}