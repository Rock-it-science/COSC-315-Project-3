Member contributions:
    Completed by Will

Design choices:
    Open input file and use scanf for n and m values first.
    Then, iterate through remaining lines to read v values.
    For each v value:
    - get the offset by using logical AND with a mask.
    The mask is calculated as (2^n)-1. I used shift left by n in place of an exponent.
    - get the page number by 2^n. I implemented this by doing v shift right by n.

Compile/run instructions:
    0. Configure input.txt file to have the desired values
    1. cd into Part 1 directory (cd 'Part 1')
    2. Compile paging.c file (gcc -o paging paging.c)
    3. Execute compiled paging file (./paging)