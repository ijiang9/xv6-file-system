#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device

#define T_SMALLFILE 5 //Small File
#define T_SFDIR 4  // Directory for small files

struct stat {
  short type;  // Type of file
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short nlink; // Number of links to file
  uint size;   // Size of file in bytes
};
