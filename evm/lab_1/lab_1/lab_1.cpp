#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <limits.h>

#define BYTE 8
#define SHORT 16
#define LONG 32
#define LONGLONG 64


void transform(int* arr, int size) {
    int first = 0;
    int amount = 0;

    printf("===========================================\n");
    printf("Введите номер старшего бита \n");

    scanf("%d", &first);

    printf("===========================================\n");
    printf("Введите количество бит \n");

    scanf("%d", &amount);

    for (int i = 0; i < size; ++i) {
        if (i >= first and i - first < amount) {
            if (arr[i] == 1) {
                arr[i] = 0;
            } else {
                arr[i] = 1;
            }
        }
    }

    printf("===========================================\n");
}

void printShort(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%2d ", i);
    }

    printf("\n");

    for (int i = 0; i < size; ++i) {
        printf("===", arr[i]);
    }

    printf("\n");

    for (int i = 0; i < size; ++i) {
        printf("%2d ", arr[i]);
    }
    printf("\n");
}

void printDouble(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%2d ", i);
    }

    printf("\n");

    for (int i = 0; i < size; ++i) {
        printf("===", arr[i]);
    }

    printf("\n");

    for (int i = 0; i < size; ++i) {
        printf("%2d ", arr[i]);
        if (i == 0 || i == 11) {
            printf("\b|");
        }
    }
    printf("\n");
}

int* serializeShort(short number) {
    //выделяем память под массив динамически
    int* ser_arr = (int*)malloc(sizeof(int) * SHORT);
    int i = 0;

    //передвигаем i на последний бит
    for (int val = (USHRT_MAX + 1) >> 1; val > 0; val >>= 1) 
    {
        if (number & val) {
            ser_arr[i] = 1;
        } else {
            ser_arr[i] = 0;
        }

        i += 1;
    }
    return ser_arr;
}

int* serializeDouble(long long number) {
    int* ser_arr = (int*)malloc(sizeof(int) * LONGLONG);
    int i = 0;

    //передвигаем i на последний бит
    for (unsigned long long val = (ULLONG_MAX >> 1) + 1; val > 0; val >>= 1) {

        if (number & val) {
            ser_arr[i] = 1;
        } else {
            ser_arr[i] = 0;
        }

        i += 1;
    }
    return ser_arr;
}

//-32768 ... +32767
void fromBitsToShort(int* arr) {
    short res = 0;

    for (int i = 0; i < SHORT; ++i) {
        if (arr[i] == 1) {
            res += (int)pow(2.0, (SHORT - 1) - i);
        }
    }

    printf("===========================================\n");
    printf("Ваше число после преобразования: %hd", res);
}

void fromBitsToDouble(int* arr) {
    double res = 0;
    double s = 0;
    double p = 0;
    double mant = 1;

    for (int i = 0; i < LONGLONG; ++i) {
        if (i == 0) {
            s = arr[i];
        } else if (i < 12) {
            if (arr[i] == 1) {
                p += pow(2.0, 11 - i);
            }
        } else {
            if (arr[i] == 1) {
                mant += 1 / pow(2.0, i - 11);
            }
        }
    }

    double sgn = pow(-1.0, s);
    double pwr = pow(2.0, p - 1023);
    
    res = sgn * pwr * mant;

    printf("===========================================\n");
    printf("Ваше число после преобразования: %lf", res);

}

union binshort {
    short s;
    unsigned short u;
};

union bindouble {
    double d;
    unsigned long long u;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    int* arr = NULL;
    short number = 0;
    union binshort bsh;
    union bindouble bdl;
    int option_1 = 0, option_2 = 0;
    int ret_val = 0;

    printf("1) двоичное представление short int \n");
    printf("2) двоичное представление double \n");

    //выбор типа данных
    scanf("%d", &option_1);
    printf("===========================================\n");
    
    /*для short*/
    if (option_1 == 1) {
        printf("Введите short int (-32768 ... +32767): ");
        scanf("%hd", &bsh.s);
        arr = serializeShort(bsh.u);
    }
    /*для double*/
    else if (option_1 == 2) {
        printf("Введите double: ");
        scanf("%lf", &bdl.d);
        arr = serializeDouble(bdl.u);
    } else {
        return 0;
    }

    printf("===========================================\n");
    printf("1) Вывести представление\n");
    printf("2) Совершить преобразование и вывести представление\n");

    scanf("%d", &option_2);
    printf("===========================================\n");


    //вывод short
    if (option_1 == 1 and option_2 == 1) {
        printShort(arr, SHORT);
        return 0;
    }
    //вывод double
    else if (option_1 == 2 and option_2 == 1) {
        printDouble(arr, LONGLONG);
        return 0;
    }
    else if (option_1 == 1 and option_2 == 2) {
        printShort(arr, SHORT);
        transform(arr, SHORT);
        printShort(arr, SHORT);
        fromBitsToShort(arr);
    }
    else if (option_1 == 2 and option_2 == 2) {
        printDouble(arr, LONGLONG);
        transform(arr, LONGLONG);
        printDouble(arr, LONGLONG);
        fromBitsToDouble(arr);
    }
        
    return 0;
}
