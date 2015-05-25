/*
Program output:
X: 100
Y: 50
*/

#include <stdio.h>

#include "preoop.h"

// Include all objects in this list:
#define objects(a, b) objectList(a,\
	objectEntry(foo, b)\
)

object {
	int x;
	int y;
} foo;

foo *method(foo, init) {
	self->x = 0;
	self->y = 0;
	
	// All `init` methods must return `self`
	return self;
}

void method(foo, setPosition, int x, int y) {
	self->x = x;
	self->y = y;
}

void method(foo, printPosition) {
	printf("X: %d\nY: %d\n", self->x, self->y);
}

int main(void) {
	// The `new` keyword allocates memory to the object, and calls its `init` method
	foo *bar = new(foo);
	
	invoke(bar, setPosition, 50, 100);
	invoke(bar, printPosition);
	
	// Objects are allocated on the heap, so must be freed when finished with
	free(bar);
	
	return 0;
}
