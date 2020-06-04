#include <stdlib.h>
#include <unistd.h>

int main() 
{
    // A 1-character buffer to read into and out of.
    char * curr = malloc(sizeof(char));

    // Until the end of the file is reached, read one character from STDIN at a time and...
    while (read(0, curr, 1) != 0)
    {
        // ...and write that character to STDOUT.
        write(1, curr, 1);
    }

    return 0;
}
