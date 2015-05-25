# Preoop
Object orientation implemented in C via the preprocessor (mostly).

Requires GCC 4.9 or above due to dependency on C11's `_Generic`.

## Usage
Include `preoop.h`.

Keep the `objects` macro updated with the names of all objects. Make sure all lines except for the last 2 have commas. For example, to have 3 objects called `Object1`, `Object2` and `Object3`:

    #define objects(a, b) _Generic((a),\
        Object1 *: b##_Object1,\
        Object2 *: b##_Object2,\
        Object3 *: b##_Object3\
    )

Declare your objects:

    object {
        int a;
    } Object1;
    
    object {
        int b;
    } Object2;
    
    object {
        int c;
    } Object3;

Add methods to your objects:

    void method(Object1, doSomething) {
        self->a++;
    }

All objects must have an `init` method which returns its `self`:

    Object1 *method(Object1, init) {
        return self;
    }

Now you can create definitions of pointers to your objects, these are known as a `Object Instance`s:

    Object1 *myObject;

Before you can use an object instance, you must invoke `new` on it:

    myObject = new(Object1);

This will allocate memory for the object, and call its `init` method.

To invoke further methods on an object instance use the `invoke` macro:

    invoke(myObject, doSomething);

Once you are finished with your object instance, you must `free` it:

    free(myObject);