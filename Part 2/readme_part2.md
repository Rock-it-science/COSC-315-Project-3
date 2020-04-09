## Member Contributions:  
    
* Will:
     
  * Setup project and file structure
  
  * Implemented system in main function for reading from input file
  
  * Wrote delete and write functions
  
  * Debugged and refactored other functions
  
  * Wrote documentation
    
* Alvin:
  
  * Wrote ls and read functions
  
  * Helped fixing bugs and refactoring code
    
* Winter:
  * Wrote myFileSystem and create functions
  * Helped fixing bugs and refactoring code

## Design Choices:

* MyFileSystem:

    Takes diskName as input. The first  thing this function does is open the file with fileName to a global variable `file`. Segment Fault™

    ...

* Create:

* ls: Reads superblock for file names. Checks if they are empty to not print blank lines. Due to issues with writing to the superblock, this function does not work as the data is stored in structs instead of directly on the superblock.

* read: Reads superblock to see if file with the input name and if the block exists by checking the inode. Due to issues with writing to the superblock, this function does not work as the data is stored in structs instead of directly on the superblock.

* write:

## Compile/run insturctions:
  1. Setup input instructions in lab3.input.txt
  
  1. cd into Part 2 directory (`cd 'Part 2'`)
        
        (ensure to do `cd ..` to get out of Part 1 directory)
  
  1. Compile files with make
        
        If make doesn't work compile with below commands:
        
          gcc -o create lab3.create_fs.c
        
          gcc -o fs FileSystem.c
  
  1. Run create with argument for disk name (`./create disk0`)
  
  1. Run fs (`./fs`)
