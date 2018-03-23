#include <stdio.h>
#include <stdlib.h>

int main()
{
    puts("Will execute sh with the following script :");
    puts("bash buscarArch.sh Tarea");
    puts("Starting now:");
    system("bash buscarArch.sh Tarea");
    return 0;
}
