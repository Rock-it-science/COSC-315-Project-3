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
  
  * Helped with documentation
    
* Winter:
  * Wrote myFileSystem and create functions
  
  * Helped fixing bugs and refactoring code
  
  * Helped a bit with documentation

## Design Choices:

* MyFileSystem:

    Takes diskName as input. The first  thing this function does is open the file with fileName to a global variable `file`. The function then reads the superblock of the disk and stores it into an unsigned char array of size 1024. After that the function goes skips the first 128 bytes and starts reading the inodes. Multiple for loops are used for this process. outline:

        Loop through 16 inodes in the disk
            read 8 bytes for name
            read 4 bytes for size
            Loop through 8 times for each block pointer
                Read 4 bytes for each block pointer
            read 4 bytes for used
    
    Then the function saves these inodes to a global variable called inodes

* Create:
    The create functions first loops through all the free blocks to see if there is enough space. Then it loops through the file names to see if the new name is identical to any of the previous names. The function then adds to the inodes global varible and then starts the process of writing to the disk. outline:
        Loop through 16 inodes in the program
            write 8 bytes for name
            write 4 bytes for size
            Loop through each block pointer in inode
                write 4 bytes for each block pointer
            write 4 bytes for used

* delete: Firstly, this function reads the suprblock into a buffer to be used in this function, storing the data in a char array called super.
    
    Next, it finds the inode with the name matching what it was handed as an argument.
    To keep track of the corresponding inode, it simply stores its index in the inodes array.
    
    Next, it will free the blocks that are to be deleted by setting their values to all 0. It does this by finding the indexes of the blocks' data and iterating through it, setting all of it to 0.
    
    The next step is to mark the inode as free. To do this, it has to find the free block list in the super block and mark the corresponding inode's `used` value to 0.
    
    Finally, the function writes the super block back to the file. It fseek to move the cursor back to the start of the file, and fputs to write the modified super block to that position. 

* ls: 
	Reads superblock for file names. Checks if they are empty to ensure blank lines are not printed. Due to issues with writing to the superblock, this function does not work as the data is stored in structs instead of directly on the superblock.

* read:
	Reads superblock to see if file with the input name and the appropriate block exists by checking the inode section. Due to issues with writing to the superblock, this function does not work as the data is stored in structs instead of directly on the superblock, meaning newly written files might be seen as non existent.

* write: Like delete, this file must find the corresponding inode for the given name. nce it has found the inode, it must calculate the pointer to the correct block. This is obtained from the blockPointers attribute on each inode. This block pointer is used as an offset to seek to the correct place in the file. After that, the buffer is written to the file.

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
