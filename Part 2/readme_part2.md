Member Contributions:
    Will:
        - Setup project and file structure
        - Implemented system in main function for reading from input file
        - Wrote delete and write functions
        - Debugged and refactored other functions
        - Wrote documentation
    
    Alvin:
        - Wrote ls and read functions
        - Helped fixing bugs and refactoring code
    
    Winter:
        - Wrote myFileSystem and create functions
        - Helped fixing bugs and refactoring code

Design Choices:


Compile/run insturctions:
    0. Setup input instructions in lab3.input.txt
    1. cd into Part 2 directory (cd 'Part 2')
        (ensure to do cd .. to get out of Part 1)
    2. Compile files with make
        If make doesn't work compile with below commands:
            - gcc -o create lab3.create_fs.c
            - gcc -o fs FileSystem.c
    2. Run create with argument for disk name (./create disk0)
    3. Run fs (./fs)