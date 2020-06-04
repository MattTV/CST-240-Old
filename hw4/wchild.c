#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    // For each argument exluding argv[0] (The program's name)...
    for (short ii = 1; ii < argc; ++ii)
    {
        // Print the argument to STDOUT (fd1) and a space.
        write(1, argv[ii], strlen(argv[ii]));
        write(1, " ", 1);
    }

    return 0;
}
