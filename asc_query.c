#include <stdio.h>
#include <stdlib.h>

enum 
{
    OPT_CHAR = 1,
    OPT_INT  = 2,
    OPT_HELP = 3,
    OPT_HEX  = 0x8
};

void aq_usage()
{
    printf("Usage: ascquery [options] character.\n\n"
           "This program can show the ascii code of the character, also,"
           " it can show the char of the character.\n\n"
           "OPTIONS:\n"
           "\t-i, --int: get ascii code of the character.\n"
           "\t-c, --char: get char of the given ascii code.\n"
           "\t-x, --hex: the given ascii code is hex, or output the ascii code as hex.\n"
           "\t-h, --help: show this message.\n");
}

int get_operation(int *argc, char ***argv)
{
    int i, opt = 0;
    for (i = 1; i < *argc; ++ i)
    {
        char *arg = (*argv)[i];
        if (arg[0] != '-')
            continue;
        switch (arg[1])
        {
        case '-':
            break;
        case 'i':
            opt = (opt | 0x3) &(0xfffffff8 | OPT_INT);
            break;
        case 'c':
            opt = (opt | 0x3) & (0xfffffff8 | OPT_CHAR);
            break;
        case 'x':
            opt = OPT_HEX;
            break;
        case 'h':
            opt = (opt | 0x3) & (0xfffffff0 | OPT_HELP);
            break;
        default:
            break;
        }
    }
    return opt;
}

int main(int argc, char *argv[])
{
    int idx;
    int opt, opflag;
    if (argc < 2) 
    {
        aq_usage();
        return 0;
    }
    opt = get_operation(&argc, &argv);
    opflag = opt & 0x3;
    if (opflag  == OPT_HELP) 
    {
        aq_usage();
        return 0;
    }
    opflag = opt & OPT_HEX;
    for (idx = 1; idx < argc; ++ idx)
    {
        const char *arg = argv[idx];
        if (arg[0] == '-')
            continue;
        if ((opt & 0x3) == OPT_INT)
        {
            if (opflag == OPT_HEX)
            {
                printf("the ascii of '%s' is %X\n", arg, (unsigned char)arg[0]);
            } else 
            {
                printf("the ascii of '%s' is %d\n", arg, (unsigned char)arg[0]);
            }
        } else
        {
            int code = 0;
            if (opflag == OPT_HEX)
            {
                code = strtoul(arg, NULL, 16);
            } else
            {
                code = strtoul(arg, NULL, 10);
            }
            printf("the character of ascii '%s' is '%c'\n", arg, (unsigned char)code);
        }
    }
    return 0;
}
