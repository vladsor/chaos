
typedef struct
{
    int i1;
    int i2;
//    int i3;
//    int i4;
//    int i5;
} arg_t;

arg_t test(arg_t arg)
{
    arg.i2=0;
    
    return arg;
}

    arg_t arg;
    arg_t arg2;

int main(void)
{
    arg.i1 = 0;
    
    arg2 = test(arg);
    arg2.i2 = 1;
    
    return 0;
}
