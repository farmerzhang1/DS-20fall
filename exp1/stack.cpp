#include <iostream>
#include <string>
#define initSIZE 2
#define initStack(stack)\
    do {\
        stack ## _base_pointer = new stack[initSIZE];\
        if (stack ## _base_pointer) {\
            stack ## _top_pointer = stack ## _base_pointer;\
            stack ## _size = initSIZE;\
        } else exit(0);\
    }while(0)

#define stackEmpty(stack) (stack ## _base_pointer) == (stack ## _top_pointer)
#define stackFull(stack) (stack ## _top_pointer) - (stack ## _base_pointer) == (stack ## _size)
#define getTop(stack) *(stack ## _top_pointer-1)
#define clearStack(stack) (stack ## _top_pointer) = (stack ## _base_pointer)
#define destroyStack(stack) delete [] stack ## _base_pointer
#define pop(stack, e)\
    do {\
        if (stackEmpty(stack));\
        else e = *(--stack ## _top_pointer);\
    }while(0)

#define push(stack, e)\
    do {\
        if (stackFull(stack)) {\
            stack* temp = new stack[(stack ## _size)*2];\
            (stack ## _size) *= 2;\
            for (int i = 0; i < initSIZE; i++) {\
                temp[i] = stack ## _base_pointer[i];\
            }\
            destroyStack(stack);\
            stack ## _base_pointer = temp;\
            stack ## _top_pointer = temp + (stack ## _size);\
            *(stack ## _top_pointer++) = e;\
        }\
        else *(stack ## _top_pointer++) = e;\
    }while(0)

using namespace std;

int* int_base_pointer;
int* int_top_pointer;
int int_size;
char* char_base_pointer;
char* char_top_pointer;
int char_size;
string* string_base_pointer;
string* string_top_pointer;
int string_size;
double* double_base_pointer;
double* double_top_pointer;
int double_size;

//why not use template ? why so much trouble ?
int main(void) {
    int n;
    initStack(int);
    if (stackEmpty(int)) cout << "int stack empty" << endl;
    push(int, 10);
    push(int, 2);
    push(int, 3);
    push(int, 4);
    cout << getTop(int) << endl;
    if (stackFull(int)) cout << "full stack" << endl;
    pop(int, n);
    cout << n << ' ' << getTop(int) << endl;
    if (stackFull(int)) cout << "full stack" << endl;
    return 0;
}