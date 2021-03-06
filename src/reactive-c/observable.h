#ifndef __OBSERVABLE_H
#define __OBSERVABLE_H

#include "unknown.h"
#include "observable.h"

typedef struct observable *observable_t;

#include "observables.h"

// an observation consists of:
// 1. an array of pointers to the values of the observed observables.
// 2. a pointer to the location of the resulting observing value
typedef struct observation {
  observable_t source, self;
  unknown_t *observeds;
  unknown_t observer;
} *observation_t;

// an observer handles an observation
typedef void (*observer_t)(observation_t);

// retrieve the current value of the observable
unknown_t observable_value(observable_t);

// adds observer to a list of observables, providing memory space for its value,
// based on its size
observable_t __observing(char*, observables_t, observer_t, int);

// construct an observable from a (pointer to a) value
observable_t __observing_value(char*, unknown_t, int);

#define observed(t) __observing(#t, NULL, NULL, sizeof(t))

// actually starts an observable
observable_t start(observable_t);

// suspends a started observable
observable_t suspend(observable_t);

// delay an observable until its scripting parent is activated
observable_t delay(observable_t);

observable_t auto_dispose(observable_t);

// add a callback to the observable, triggered when it is disposed
typedef void (*observable_callback_t)(observable_t);
observable_t on_dispose(observable_t, observable_callback_t);
observable_t on_activation(observable_t, observable_callback_t);

// remove an observer from all observeds and releases it entirely
void dispose(observable_t);

observable_t disposing(observable_t);

// trigger gargage collection
void empty_trash(void);

// trigger and observable to be updated
void observe_update(observable_t observable);

// value manipulation support
void observable_value_copy(observable_t, observable_t);

void __set(observable_t, void*, int);

typedef bool(*validator_t)(unknown_t);

void stop_observing(void);

// overloaded constructor for creating observables
#define __o1(v)       __observing_value(#v,(void*)&v,sizeof(v))
#define __o2(t,v)     __observing_value(#v,(void*)&v,sizeof(t))
#define __o3(l,o,t)   __observing(#l,l,o,sizeof(t))
#define __o4(l,o,t,s) __observing(#l,l,o,sizeof(t)*s)
#define __ox(_1,_2,_3,_4,NAME,...) NAME
#define observing(...) __ox(__VA_ARGS__, __o4, __o3, __o2, __o1, 0)(__VA_ARGS__)

// helper macro to combine creation and activation
#define observe(...) start(observing(__VA_ARGS__))

// sometimes its nicer to write... e.g. return suspended(this)
#define suspended(x) suspend(x)
#define started(x)   start(x)
#define delayed(x)   delay(x)

// set support
#define set(o,v) { __typeof__ (v) _v = (v); __set(o, &_v, sizeof(v)); }

// map support
#define __m3(o,f,t)   observe(just(o),f,t)
#define __m4(o,f,t,s) observe(just(o),f,t,s)
#define __mx(_1, _2, _3, _4,NAME,...) NAME
#define map(...) auto_dispose(__mx(__VA_ARGS__, __m4, __m3, __m2, __m1)(__VA_ARGS__))

// modification support
void let(observable_t, observable_t);

// forces a level to a given value -> OVERWRITTEN BY FRAMEWORK WHEN NEEDED
observable_t force_level(observable_t, int);

#endif
