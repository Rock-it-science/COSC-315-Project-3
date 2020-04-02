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

    char cmask[16];
    for(int i=0; i<16; i++){
        if(i<m){
            cmask[i] = 0;
        } else{
            cmask[i] = 1;
        }
    }
    int mask = atoi(cmask);

    //Continue to read until end of file
    char buffer[sizeof(int)];
    int v, p, d;
    while(fscanf(f, "%s", buffer) == 1){
        v = atoi(buffer);
        //Get n least significant bits (offset) by turning m highest bits into 0s
        // Logical AND with m 0s and n 1s
        d = v & mask;

        //Shift v right by n to get the m most significant bits (page)
        p = v >> n;

        printf("Virtual address %d is in page number %d and offset %d\n", v, p, d);
    }
}