# Preoop
Object orientation implemented in C at compile time via the preprocessor (mostly).

Requires GCC 4.9 or above due to dependency on C11's `_Generic`.

Combine with my [Exception library](https://github.com/CTurt/Exception) for [some very high level C code](https://gist.github.com/CTurt/b94b5c475f27003886ba).

## Usage
Include `preoop.h`.

Create an `objects` macro containing an entry for every object. Make sure all entries except for the last one have commas. For example, to have 3 objects called `Object1`, `Object2` and `Object3`:

    #define objects(a, b) objectList(a,\
        objectEntry(Object1, b),\
        objectEntry(Object2, b),\
        objectEntry(Object3, b)\
    )

Declare your objects with `members` and `methods`:

    object(Object1,
        members {
            int a;
        }
        
        Object1 *method(Object1, init) {
            return self;
        }
        
        void method(Object1, doSomething) {
            self->a++;
        }
    )

All objects must have an `init` method which returns its `self`:

Now you can create definitions of pointers to your objects, these are known as a `Object Instance`s:

    Object1 *myObject;

Before you can use an object instance, you must invoke `new` on it:

    myObject = new(Object1);

This will allocate memory for the object, and call its `init` method.

To invoke further methods on an object instance, use the `invoke` macro:

    invoke(myObject, doSomething);

Since object instances are allocated on the heap, you must `free` them once you have finished with them:

    free(myObject);

For a complete demonstration of Preoop, see `sample.c`.

## Working with header and source files
For larger projects, you should declare objects with members and method prototypes in a header file, and have the methods themselves in a source file. The object list should be stored in its own header file. For example:

### objects.h:
    #pragma once

    #include "preoop.h"

    #define objects(a, b) objectList(a,\
        objectEntry(fileReader, b)\
    )

### file.h:
    #pragma once

    #include <stdio.h>

    #include "objects.h"

    object(fileReader,
        members {
            FILE *handle;
            size_t size;
            char *buffer;
        };
        
        fileReader *method(fileReader, init, char *filename);
    )

### file.c:
    #include "exception.h"

    #include "file.h"

    fileReader *method(fileReader, init, char *filename) {
		enum {
			NO_ERROR,
			ERROR_FOPEN,
			ERROR_MALLOC,
			errorCount,
		};
		
		char *errors[errorCount] = {
			[ERROR_FOPEN] = "Could not open file",
			[ERROR_MALLOC] = "Could not allocate memory",
		};
		
		try(
			self->handle = fopen(filename, "rb");
			if(!self->handle) throw(ERROR_FOPEN);
			
			fseek(self->handle, 0, SEEK_END);
			self->size = ftell(self->handle);
			
			self->buffer = malloc(self->size);
			if(!self->buffer) throw(ERROR_MALLOC);
		);
		
		catch(ERROR_FOPEN || ERROR_MALLOC) {
			printf("%s!\n", errors[e]);
			
			free(self);
			return NULL;
		}
        
        rewind(self->handle);
        fread(self->buffer, self->size, 1, self->handle);
        
        fclose(self->handle);
        
        return self;
    }

## How does it work?
Methods are essentially functions with the addition of `self` as the first parameter, and the name of the object appended to the name of the function to avoid conflict.

For example, this method:

    void method(foo, printPosition) {
        printf("X: %d\nY: %d\n", self->x, self->y);
    }

Is processed into:

    void printPosition_foo(foo *self) {
        printf("X: %d\nY: %d\n", self->x, self->y);
    }

And all `invokes` are processed from:

    invoke(bar, printPosition);

To:

    printPosition_foo(bar);