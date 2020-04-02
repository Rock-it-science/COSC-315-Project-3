#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    //Open file
    FILE *f = fopen("input.txt", "r"); //Use read only

    int n;  /* the n lowest significant bits that represent the offset */
    fscanf(f, "%d", &n);
    
    int m;  /* the next m bits that represent the page number; assume that n+m is always 16 */
    fscanf(f, "%d", &m);

    printf("Offset within page is %d bits, which can represent %d decimal numbers\n", n, 2<<n);
    printf("Page number is %d bits, which can represent %d decimal numbers\n", m, 2<<m);

    int mask = (2<<n) - 1;

    //Continue to read until end of file
    char buffer[sizeof(int)*2];
    int v, p, d;
    while(fscanf(f, "%s", buffer) == 1){
        v = atoi(buffer);
        //Get n least significant bits (offset) by turning m highest bits into 0s
        // Logical AND with m 0s and n 1s
        d = v & mask;

        //Shift v right by n to get the m most significant bits (page number)
        p = v >> n;

        printf("Virtual address %d is in page number %d and offset %d\n", v, p, d);
    }

    fclose(f);
    
    return 0;
}