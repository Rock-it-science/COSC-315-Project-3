void myFileSystem(char diskName){
	// Open the file with name diskName
    int fd;
    char* buf;
    fd = open(argv[1], O_RDONLY, S_IRUSR);
    int nodeNum;
    for (int i = 0; i < 16; i++)
    {
        if (buf[i].name == diskName) {
            nodeNum = i;
        }
    }
   // Read the first 1KB and parse it to structs/objecs representing the super block
   // 	An easy way to work with the 1KB memory chunk is to move a pointer to a
   //	position where a struct/object begins. You can use the sizeof operator to help
   //	cleanly determine the position. Next, cast the pointer to a pointer of the
   //	struct/object type.

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
    FILE* writer;
    writer = fopen("filesys.bin", "rb");
    fread(buf, sizeof(buf), 1, reader);
    //=====================Need to get inode list and free block list=================
    int nodeNum;
    for (int i = 0; i < length; i++)
    {
        if (iList[i].name == name) {
            nodeNum = i;//save iNode number if empty
            break;
        }
        return -1;//No file with that name found
    }
    writer = fopen("filesys.bin", "wb");//write to filesys.bin in binary
    fwrite(buf, sizeof(buf), 1, writer);//write 1KB from the buffer
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
    int fd;
    char* buf;
    fd = open(argv[1], O_RDONLY, S_IRUSR);
    for (int i = 0; i < 16; i++)
    {
        if (buf[i].used==1) {
            printf(buf[i].name +" " +buf[i].name);
        }
    }
  // Print the name and size fields of all used inodes.
}

int read(char name[8], long int blockNum, char buf[1024]){
   // read this block from this file
    FILE* reader;
    reader = fopen("filesys.bin", "rb");
    fread(buf, sizeof(buf), 1, reader);
    int nodeNum;
    for (int i = 0; i < 16; i++)
    {
        if (iList[i].name == name) {//find inode with this name
            nodeNum = i;
            break;
        }
    }
   // Return an error if and when appropriate. For instance, make sure
   // blockNum does not exceed size-1.
    if (blockNum < iList[nodeNum].size)
        return -1;//Trying to access block that doesn't exist
   // Step 1: Locate the inode for this file as in Step 1 of delete.
   // Step 2: Seek to blockPointers[blockNum] and read the block
   // from disk to buf.
   return 0;//file read
}

int write(char name[8], long int blockNum, char buf[1024]){
   // write this block to this file
   FILE* writer;
   writer = fopen("filesys.bin", "rb");
   fread(buf, sizeof(buf), 1, reader);
   //=====================Need to get inode list and free block list=================
   int nodeNum;
   for (int i = 0; i < length; i++)
   {
       if (iList[i].used == 0) {
           nodeNum = i;//save iNode number if empty
           break;
       }
       return -1;//No empty iNode
   }
   writer = fopen("filesys.bin", "wb");//write to filesys.bin in binary
   fwrite(buf, sizeof(buf), 1, writer);//write 1KB from the buffer
   //Return an error if and when appropriate.
   //Find empty location
   
   // Step 1: Locate the inode for this file as in Step 1 of delete.

   // Step 2: Seek to blockPointers[blockNum] and write buf to disk.
}

int main(int argc, char *argv[]){
	return 0;
}