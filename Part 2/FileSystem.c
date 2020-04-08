#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


struct inode {
    char name[8];
    int32_t size;
    int32_t blockPointers[8];
    int32_t used;
};


void printHex(unsigned char data[], int size) { //prints to console for testing purposes
    printf("Printing start:\n");
    printf("Size of data: %i\n",size);
    for(int i = 0; i < size; i++) {
        printf("%x", data[i]);
    }
    printf("\nPrinting Complete\n");
}
//global variable for list of inodes
struct inode inodes[16];
FILE * file;
void myFileSystem(char* diskName){
    printf("myFileSystem start:\n");
    printf("%s\n",diskName);
    printf("Trying to read: %s\n",diskName);
    // Open the file with name diskName

    file = fopen(diskName,"rb");
    if(file == NULL) {
        printf("Read File Error\n");
        exit(1);
    }
    printf("Read Complete \n");
    // Read the first 1KB and parse it to structs/objecs representing the super block
    // 	An easy way to work with the 1KB memory chunk is to move a pointer to a
    //	position where a struct/object begins. You can use the sizeof operator to help
    //	cleanly determine the position. Next, cast the pointer to a pointer of the
    //	struct/object type.
    long readSize = 1024;
    unsigned char superBlock[readSize];
    size_t result;
    printf("Storing start:\n");
    result = fread(superBlock, 1, readSize, file);
    if(result != readSize) {
        printf("Read 1024 Error\n");
        exit(1);
    }
    printf("Storing complete:\n");

    printHex(superBlock,readSize);

    

    printf("Reading inode start:\n");
    printf("%i\n",sizeof(inodes));

    int readLocation = 128; // 128 for free block list

    for(int i = 0; i < 16; i++) {
        char readName[8];
        for(int iname = 0; i < 8; i++) {
            readName[iname] = superBlock[readLocation+iname];
        }
        readLocation += 8; //name

        int32_t readSize;
        char readSizeChar[4];
        for(int isize = 0; i < 4; i++) {
            readSizeChar[isize] = superBlock[readLocation + isize];
        }
        char* ptr;
        readSize = strtol(readSizeChar, &ptr, 2);
        readLocation += 4; //size

        int32_t readBlockPointers[8];
        for(int iBlockPointers1 = 0; iBlockPointers1 < 8; iBlockPointers1++) {
            char readBlockPointersChar[4];
            for(int iBlockPointers2 = 0; iBlockPointers2 < 4; iBlockPointers2++) {
                readBlockPointersChar[iBlockPointers2] = superBlock[readLocation + iBlockPointers2 + (iBlockPointers1*4)];
            }
            char* ptr;
            readBlockPointers[iBlockPointers1] = strtol(readBlockPointersChar, &ptr, 2);
        }
        readLocation += 32; //BlockPointers

        int32_t readUsed;
        char readUsedChar[4];
        for(int iUsed = 0; iUsed < 4; iUsed++) {
            readUsedChar[iUsed] = superBlock[readLocation + iUsed];
        }
        char* ptr2;
        readUsed = strtol(readUsedChar, &ptr2, 2);
        readLocation +=4; //Used

        inodes[i].name = readName;
        inodes[i].size = readSize;
        inodes[i].blockPointers = readBlockPointers;
        inodes[i].used = readUsed;



    }




    fclose(file);
    

    // Be sure to close the file in a destructor or otherwise before
    // the process exits.
}

int create(char name[8], long int size){
    //create a file with this name and this size

    // high level pseudo code for creating a new file

    // Step 1: Look for a free inode by searching the collection of objects
    // representing inodes within the super block object.
    // If none exist, then return an error.
    // Also make sure that no other file in use with the same name exists.

    // Step 2: Look for a number of free blocks equal to the size variable
    // passed to this method. If not enough free blocks exist, then return an error.

    // Step 3: Now we know we have an inode and free blocks necessary to
    // create the file. So mark the inode and blocks as used and update the rest of
    // the information in the inode.

    // Step 4: Write the entire super block back to disk.
    //	An easy way to do this is to seek to the beginning of the disk
    //	and write the 1KB memory chunk.
}

int delete(char name[8]){
    // Delete the file with this name

    // Step 1: Look for an inode that is in use with given name
    // by searching the collection of objects
    // representing inodes within the super block object.
    // If it does not exist, then return an error.

    // Step 2: Free blocks of the file being deleted by updating
    // the object representing the free block list in the super block object.

    // Step 3: Mark inode as free.

    // Step 4: Write the entire super block back to disk.
}

int ls(){
    // List names of all files on disk

    // Print the name and size fields of all used inodes.
}

int read(char name[8], long int blockNum, char buf[1024]){
    // read this block from this file
    // Return an error if and when appropriate. For instance, make sure
    // blockNum does not exceed size-1.

    // Step 1: Locate the inode for this file as in Step 1 of delete.

    // Step 2: Seek to blockPointers[blockNum] and read the block
    // from disk to buf.
}

int write(char name[8], long int blockNum, char buf[1024]){
    // write this block to this file
    // Return an error if and when appropriate.

    // Step 1: Locate the inode for this file as in Step 1 of delete.

    // Step 2: Seek to blockPointers[blockNum] and write buf to disk.
}






//main arguments:         moved here for testing
int main(int argc, char *argv[]){
    char diskName[] = "disk0";
    myFileSystem(diskName);



}