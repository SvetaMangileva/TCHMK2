#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ClassLN.h"
int main(int argc, const char * argv[])
{
    if (argc < 5 || argc > 7)
    {
        printf("You must be enter more than 5 and fewer than 7 arguments. For example:\n");
	printf("<file_a> <[ + | - | x | / | % | ^ ]> <file_b> <file_result> <file_module>\n");
	printf("or:\n");
	printf("<file_a> <[ + | - | x | / | % | ^ ]> <file_b> <file_result> <file_module> <-b>\n");
	return 0;
    }
    int bin = 0;
    if (argc == 5)
    {
        if (argv[2][0] == '^')
        {
            printf("You must be enter module file\n");
            return 0;
        }
    }
    if (argc == 6)
    {
        if (strcmp(argv[5], "-b") == 0)
            bin = 1;
        else
            bin = 0;
        if (bin == 0)
        {
            if (argv[2][0] != '^')
            {
                printf("Bad argument %s!\n", argv[5]);
                return 0;
            }
            else
            {
                FILE* Module_File = fopen(argv[5], "r");
                if (!Module_File)
                {
                    printf("Module file %s not found!\n",argv[5]);
                    return 0;
                }
                fclose(Module_File);
            }
        }
    }
    if (argc == 7)
    {
        if (strcmp(argv[6], "-b") == 0)
            bin = 1;
        else
        {
            printf("What this %s?\n",argv[6]);
            return 0;
        }
        if (argv[2][0] != '^')
        {
            printf("Bad argument %s!\n", argv[5]);
            return 0;
        }
        else
        {
            FILE* Module_File = fopen(argv[5], "r");
            if (!Module_File)
            {
                printf("Module file %s not found!\n",argv[5]);
                return 0;
            }
            fclose(Module_File);
        }
    }
    FILE* Long_A_File = fopen(argv[1], "r");
    if (!Long_A_File)
    {
        printf("File %s not found!\n", argv[1]);
        return 0;
    }
    fclose(Long_A_File);
    FILE* Long_B_File = fopen(argv[3], "r");
    if (!Long_B_File)
    {
        printf("File %s not found!\n", argv[3]);
        return 0;
    }
    fclose(Long_B_File);
    FILE* Result_File = fopen(argv[4], "w");
    fclose(Result_File);
    const char* op = argv[2];
    if ((strlen(op) > 1 || op[0] == '\0') || op[0] != '+' && op[0] != '-' && op[0] != 'x' && op[0] != '/' && op[0] != '%' && op[0] != '^')
    {
        printf("Bad operation: %s \n", op);
        return 0;
    }
    ClassLN a,b;
    if  (bin == 1)
    {
        a.ReadBin(argv[1]);
        b.ReadBin(argv[3]); 
    }
    else
    {
        a.ReadText(argv[1]);
        b.ReadText(argv[3]);
    }
    ClassLN result;
    switch (op[0]) 
    {
        case '+':
        {
            result = a + b;
            break;
        }
        case '-':
        {
            result = a - b;
            break;
        }
        case 'x':
        {
            result = a * b;
            break;
        }
        case '/':
        {
            result = a / b;
            break;
        }
        case '%':
        {
            result = a % b;
            break;
        }
        case '^':
        {
            ClassLN c;
            if(bin == 1)
                c.ReadBin(argv[5]);
            else
                c.ReadText(argv[5]);
            result = PowMod(a, b, c);
            c.ClearMemory();
            break;
        }
        default:
            break;
    }
    if (bin == 1)
        result.WriteBin(argv[4]);
    else
        result.WriteText(argv[4]);
    a.ClearMemory();
    b.ClearMemory();
    result.ClearMemory();
    return 0;           
}  
