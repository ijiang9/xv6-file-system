#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

//show the file status given the file name
void show(char * fileName) {
  struct stat st;
  if(stat(fileName, &st) < 0) {
    return;
  }
  if(st.type == T_SMALLFILE) {
    printf(1, "TYPE: T_SMALLFILE\n");
    printf(1,"FILENAME: %s\n\t-INODE_NUMBER: %d\n\t-Size: %d\n\t-nlink: %d\n", fileName, st.ino, st.size, st.nlink);
  }

  if(st.type == T_FILE) {
    printf(1, "TYPE: T_FILE\n");
    printf(1,"FILENAME: %s\n\t-INODE_NUMBER: %d\n\t-Size: %d\n\t-nlink: %d\n", fileName, st.ino, st.size, st.nlink);
  }
}


int 
main(int argc, char* argv[]) {
  int fd;
  mkSFdir("foo");

  char buff[63] = "0123456789abcdefghijk0123456789abcdefghijk0123456789abcdefghijk";

  printf(1,"---------------------------\n");
  printf(1, "Test creating small file\n");
  if((fd = open("foo/test_file1.txt", O_CREATE | O_RDWR)) < 0){
	
      printf(1, "Failed to create the file\n");
  } else {
	
      printf(1, "Successfully create the file\n");
      char * fileName = "foo/test_file1.txt";
      show(fileName);
      struct stat sb;
      stat("foo/test_file1.txt", &sb);
  }
  close(fd);
  printf(1,"---------------------------\n");
  printf(1, "Test write small buffer to a small file\n");
  if((fd = open("foo/test_file2.txt", O_CREATE | O_RDWR)) < 0){
      printf(1, "Failed to create the file\n");
  } else {
      printf(1, "Successfully create the file\n");

      int n;
      char buff0[3] = "012";
      if((n = write(fd, &buff0, 3)) != 3) {
        printf(1, "Write Failed\n");

      } else {
        char * fileName = "foo/test_file2.txt";
        show(fileName);
      }
      printf(1, "Test write overflow a small file and convert to normal file\n");
      printf(1, "Writing more...\n");
      
      if((n = write(fd, &buff, 63)) != 63) {
        printf(1, "Write Failed\n");

      } else {
  close(fd);
        char * fileName = "foo/test_file2.txt";
        show(fileName);
      }

  }

  printf(1,"---------------------------\n");
  ///testing small link to small
  printf(1, "Testing link small file to small directory \n");
  if ((fd = open("foo/test_file1.txt", O_RDWR)) < 0){
    printf(1, "Failed to open the file\n");
  } else {
    printf(1, "Successfully create the file\n");
    
    if (link("foo/test_file1.txt", "foo/smalllink.txt") < 0){
      printf(1, "Failed to link the file\n");
    } else {
      printf(1, "Successfully linked the file\n");
      char * fileName = "foo/smalllink.txt";
      show(fileName);
      close(fd);
    }
  }
  printf(1, "Writing to small file using the link...\n");
  if((fd = open("foo/smalllink.txt", O_RDWR)) < 0){
      printf(1, "Failed to open the file\n");
  } else {
      printf(1, "Successfully open the file\n");
      char buff0[3] = "012";
      int n;
      if((n = write(fd, &buff0, 3)) != 3) {
        printf(1, "Write Failed\n");
      } else {
        close(fd);
        char * fileName = "foo/smalllink.txt";
        show(fileName);
      }
  }

  printf(1,"---------------------------\n");
  ///testing normal link to small
  printf(1, "Testing link small file to normal directory\n");
  if ((fd = open("foo/smalllink1.txt", O_CREATE | O_RDWR)) < 0){
    printf(1, "Failed to create the file\n");
  } else {
    printf(1, "Successfully create the file\n");
    char * fileName = "foo/smalllink1.txt";
    show(fileName);
    if (link("foo/smallink1.txt", "normallink.txt") < 0){
      printf(1, "Failed to link the file\n");
    } else {
      printf(1, "Successfully linked the file\n");
      char * fileName = "normallink.txt";
      show(fileName);
      close(fd);
    }
  }
  printf(1,"---------------------------\n");
  ///testing normal link to normal
  printf(1, "Testing link normal file to normal directory\n");
  if ((fd = open("normalFile.txt", O_CREATE | O_RDWR)) < 0){
    printf(1, "Failed to create the file\n");
  } else {
    printf(1, "Successfully create the file\n");
    char * fileName = "normalFile.txt";
    show(fileName);
    if (link("normalFile.txt", "normallink.txt") < 0){
      printf(1, "Failed to link the file\n");
    } else {
      printf(1, "Successfully linked the file\n");
      char * fileName = "normallink.txt";
      show(fileName);
      close(fd);
    }
  }
  printf(1,"---------------------------\n");
  exit();
}
