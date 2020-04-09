#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>


struct inode {
    unsigned char name[8];
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

//Global file
FILE* file;

void myFileSystem(char* diskName){
    printf("myFileSystem start:\n");
    printf("%s",diskName);
    printf("Trying to read: %s\n",diskName);
    // Open the file with name diskName

    file = fopen(diskName,"rb+");
    if(file == NULL) {
        printf("Read File Error\n");
        exit(1);
    }
    if(file == NULL) {
        printf("Write File Error");
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
    //printf("Storing start:\n");
    result = fread(superBlock, 1, readSize, file);
    printf("result: %ld\n",result);
    printHex(superBlock,readSize);
    if(result != readSize) {
        printf("Read 1024 Error\n");
        exit(1);
    }
    //printf("Storing complete\n");

    

    

    //printf("Reading inode start:\n");
    //printf("%li\n",sizeof(inodes));

    int readLocation = 128; // 128 for free block list

    for(int i = 0; i < 16; i++) {
        char readName[8];
        for(int iname = 0; iname < 8; iname++) {
            readName[iname] = superBlock[readLocation+iname];
        }
        readLocation += 8; //name

        int32_t readSize;
        char readSizeChar[4];
        for(int isize = 0; isize < 4; isize++) {
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

        //Store function values to inode
        strcpy(inodes[i].name, readName);
        inodes[i].size = readSize;
        memcpy(inodes[i].blockPointers, readBlockPointers, sizeof(readBlockPointers));
        inodes[i].used = readUsed;
    }
    
    //printf("Success importing file system\n");

    // Be sure to close the file in a destructor or otherwise before
    // the process exits.
    //fclose(file);
}

int create(char name[8], long int size){
    //create a file with this name and this size

    // high level pseudo code for creating a new file

    // Step 1: Look for a free inode by searching the collection of objects
    // representing inodes within the super block object.
    // If none exist, then return an error.

    bool found = false;
    int toUse = 0;
    for(int i = 0; (i < 16) && !found; i++) {
        if(inodes[i].used == 0) {
            //Mark as free and set found to true
            toUse = i;
            found = true;
        }
    }
    printf("using iNode %d\n",toUse);

    if(!found) {
        printf("No Empty inode found");
        exit(1);
    }

    // Also make sure that no other file in use with the same name exists.
    for(int i = 0; i < 16; i++) {
        if(strcmp(inodes[i].name,name) == 0) {
            printf("File name Exists");
            exit(1);
        }
    }

    // Step 2: Look for a number of free blocks equal to the size variable
    // passed to this method. If not enough free blocks exist, then return an error.
    fseek(file, 0, SEEK_SET);//Move cursor to start of file
    long readSize = 128;
    unsigned char freeBlock[readSize];
    size_t result;
    result = fread(freeBlock, 1, readSize, file);
    if(result != readSize) {
        printf("Read free Error, read %ld values\n", result);
        exit(1);
    }  
    int freeBlocks = 0;
    bool foundAll;
    int32_t blocksToWrite[size];
    for(int i = 0; (i < 128) & (freeBlocks < size); i++) {
        if(freeBlock[i] == 0) {
            blocksToWrite[freeBlocks] = i;
            freeBlocks++;
        }
    }
    if(freeBlocks < size) {
        printf("Not enough Free Blocks\n");
        exit(1);
    }

    // Step 3: Now we know we have an inode and free blocks necessary to
    // create the file. So mark the inode and blocks as used and update the rest of
    // the information in the inode.

    strcpy(inodes[toUse].name, name);
    inodes[toUse].used = 1;
    inodes[toUse].size = size;
    for(int i = 0; i < size; i++) {
        inodes[toUse].blockPointers[i] = blocksToWrite[i];
    }

    // Step 4: Write the entire super block back to disk.
    //	An easy way to do this is to seek to the beginning of the disk
    //	and write the 1KB memory chunk.

        unsigned char toWrite[1024];
        for(int i = 0; i < size; i++) {
            freeBlock[blocksToWrite[i]] = (unsigned char)1;
        }
        for(int i = 0; i < 128; i++) {
            toWrite[i] = freeBlock[i];
        }
        int writeLocation = 128;
        for(int i = 0; i < 16; i++) {
            for(int iname = 0; iname < 8; iname++) {
                toWrite[writeLocation + iname] = inodes[i].name[iname];
            }
            writeLocation += 8;

            unsigned char writeSize[4];
            //itoa(inodes[i].size,writeSize,2);
            snprintf(writeSize,4,"%d",inodes[i].size);
            for(int isize = 0; isize < 4; isize++) {
                toWrite[writeLocation + isize] = writeSize[i];
            }
            writeLocation +=4;

            for(int iBlockPointers1 = 0; iBlockPointers1 < 8; iBlockPointers1++) {
                unsigned char writeBlockPointers[4];
                //itoa(inodes[i].blockPointers[iBlockPointers1], writeBlockPointers,2);
                snprintf(writeBlockPointers,4,"%d",inodes[i].blockPointers[iBlockPointers1]);
                for(int iBlockPointers2; iBlockPointers2 < 4; iBlockPointers2++) {
                    toWrite[writeLocation + iBlockPointers2 + (iBlockPointers1*4)] = writeBlockPointers[iBlockPointers2];
                }
            }
            writeLocation += 32;

            unsigned char writeUsed[4];
            //itoa(inodes[i].used,writeUsed,2);
            snprintf(writeUsed,4,"%d",inodes[i].used);
            for(int iused = 0; iused < 4; iused++) {
                toWrite[writeLocation + iused] = writeUsed[iused];
            }
            writeLocation += 4;
        }

        printHex(toWrite,1024);
        fseek(file, 0, SEEK_SET);
        fputs(toWrite, file);

    return 1;
}

int delete(unsigned char name[8]){
    // Delete the file with this name

    //Step 0: read super block
    char super[896];
    fread(super, 1, 128, file);

    // Step 1: Look for an inode that is in use with given name
    // by searching the collection of objects
    // representing inodes within the super block object.
    // If it does not exist, then return an error.
    

        int in = -1;
        
        //Look for inode with matching name
        for(int i=0; i<16; i++){
            if(strcmp(inodes[i].name, name)){
                in = i;
            }
        }
        //if in is still -1 (inode not found)
        if(in == -1){
            printf("Could not find inode with matching name\n");
            return 0;
        }

    // Step 2: Free blocks of the file being deleted by updating
    // the object representing the free block list in the super block object.
        for(int i=in; i<in+inodes[in].size; i++){
            super[i] = 0;
        }

    // Step 3: Mark inode as free.
        //fbl = 128B, each inode = 48B, size is 9th byte in inode
        super[128+(in*48)+9] = 0;

    // Step 4: Write the entire super block back to disk.
        fseek(file, 0, SEEK_SET); //Move cursor to start of file
        fputs(super, file);
    return 1;
}

int ls(){
	printf("Files in system:\n");
    for(int i = 0; i < 16; i++) {
		if(inodes[i].used==1)
			printf("|--%s %d Blocks\n", inodes[i].name, inodes[i].size);
    }
	return 1;
}

int read(unsigned char name[8], long int blockNum, char buf[1024]){
    // read this block from this file
    // Return an error if and when appropriate. For instance, make sure
    // blockNum does not exceed size-1.
	// Step 1: Locate the inode for this file as in Step 1 of delete.
    //Look for inode with matching name
	int in = -1;
    for(int i=0; i<16; i++){
        if(strcmp(inodes[i].name, name)){
            in = i;
        }
    }
    //if in is still -1 (inode not found)
    if(in == -1){
        printf("Could not find inode with matching name\n");
		return -1;
    }
	//if invalid blocknum
	if(blockNum>7 || &inodes[in].blockPointers[blockNum] == NULL) {
		printf("Invalid block number\n");
		return -1;
	}
	//if block exists, read from file
	
	//check if block is potentially less than 1KB
	long readSize;
	if(&inodes[in].blockPointers[blockNum+1]== NULL || blockNum == 7)
		readSize = inodes[in].size - (blockNum*1024); //get the leftover block size =================================================pls check calculation
	else
		readSize = 1024;
	// Step 2: Seek to blockPointers[blockNum] and read the block
    // from disk to buf.
    size_t result;
    result = fread(buf, 1, readSize, file);
    /*if(result != readSize) {
        printf("Read 1024 Error\n");
        exit(1);
    }*/
    return 1;
}

int write(unsigned char name[8], long int blockNum, char buf[1024]){
    // write this block to this file
    // Return an error if and when appropriate.

    // Step 1: Locate the inode for this file as in Step 1 of delete.
        int in = -1;
        
        //Look for inode with matching name
        for(int i=0; i<16; i++){
            if(strcmp(inodes[i].name, name) == 0){
                in = i;
            }
        }
        //if in is still -1 (inode not found)
        if(in == -1){
            printf("Could not find inode with matching name\n");
            return 0;
        }
    // Step 2: Seek to blockPointers[blockNum] and write buf to disk.
        int blockPtr = inodes[in].blockPointers[blockNum];
        fseek(file, blockPtr, SEEK_SET);
        fputs(buf, file);

    return 1;
}



int main(int argc, char *argv[]){
    //Read input file
    FILE* fileINPUT = fopen("lab3input.txt", "r");
    
    //first get diskname
    char* diskName;
    fscanf(fileINPUT, "%s", diskName);

    //Update fileSystem
    myFileSystem(diskName);

    //Iterate through rest of the file
    char buffer[sizeof(char)*32];
    while(fscanf(fileINPUT, "%s", buffer) == 1){
        //ls
        if(buffer[0] == 'L'){
            ls();
        }
        else{
            //Get fileName
            char fileName[8];
            fscanf(fileINPUT, "%s", fileName);

            //delete
            if(buffer[0] == 'D'){
                printf("Deleting file %s\n", fileName);
                delete(fileName);
            }

            else{
                //Get final argument
                char arg[8];
                fscanf(fileINPUT, "%s", arg);

                //Create
                if(buffer[0] == 'C'){
                    printf("Creating file with name %s and size %s\n", fileName, arg);
                    create(fileName, (long)atol(arg));
                }
                //Write
                else if(buffer[0] == 'W'){
                    char dummyBuffer[1024];
                    for(int i=0; i<1024; i++){dummyBuffer[i] = '1';}
                    printf("Writing to block number %s in file with name %s\n", fileName, arg);
                    write(fileName, (long)atol(arg), dummyBuffer);
                }
                //Read
                else if(buffer[0] == 'R'){
                    printf("Reading block %s from file %s\n", arg, fileName);
                    char buf[1024];
                    read(fileName, (long)atol(arg), buf);
                    printf("file contents: %s\n", buf);
                }
            }
        }
        myFileSystem(diskName);
    }
    fclose(fileINPUT);
}