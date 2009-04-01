#pragma comment(lib,"../yscom_win/bin/yscom_win.lib")

#include <stdio.h>
#include "tsmain.h"
#include "../yscom_win/var/fecom.h"
#include "../yscom_win/var/yscom.h"
void Usage(int argc,char **argv)
{
    fprintf(stderr,"Usage :%s <--var> [--key keystr] <--byte> <byte>\n"
                   "          <--var> [--key keystr] <--int16> <int>\n"
                   "          <--var> [--key keystr] <--int32> <int>\n"
                   "          <--var> [--key keystr] <--int64> <int>\n"
                   "          <--var> [--key keystr] <--double> <double>\n"
                   "          <--var> [--key keystr] <--str> str\n"
                   "          <--var> [--key keystr] <--bin> bin\n"
                   "          <--var> [--key keystr] <--array>\n"
                   "          <--var> [--key keystr] <--link>\n"
                   "          <--var> [--key keystr] <--alf>\n" 
                   "          <--var> [--key keystr] <--object>\n"
                   "          [--clone]\n"
        ,argv[0]);
}

int main(int argc,char **argv)
{
    if ( 2>argc )
    {
        Usage(argc,argv);
        return 0;
    }

     if ( (3<=argc)&&(!strcmp(argv[1],"--var")) )
    {
        tsvarstype(argc,argv);
    }
    else
    {
        Usage(argc,argv);
    }

    return 0;
}
