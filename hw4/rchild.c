#include <stdlib.h>
#include <unistd.h>

int main() 
{
    // A 1-character buffer to read into and out of.
    char buffer[10];

    short num = 10;

    // Until the end of the file is reached, read one character from STDIN at a time and...
    while (num == 10)
    {
        // ...and write that character to STDOUT.
        num = read(0, buffer, 10);
        write(1, buffer, num);
    }

    return 0;
}
