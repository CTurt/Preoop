/*
Program output:
X: 100
Y: 50
*/

#include <stdio.h>

#include "preoop.h"

// Include all objects in this list:
#define objects(a, b) _Generic((a),\
	foo *: b##_foo\
)

object {
	int x, y;
} foo;

foo *method(foo, init) {
	self->x = 100;
	self->y = 50;
	
	// All `init` methods must return `self`
	return self;
}

void method(foo, printPosition) {
	printf("X: %d\nY: %d\n", self->x, self->y);
}

int main(void) {
	// The `new` keyword allocates memory to the object, and calls its `init` method
	foo *bar = new(foo);
	
	invoke(bar, printPosition);
	
	// Objects are allocated on the heap, so must be freed when finished with
	free(bar);
	
	return 0;
}
