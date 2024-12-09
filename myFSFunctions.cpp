#include <LittleFS.h>
#include <SingleFileDrive.h>  // For Mounting drive...
#include "myFSFunctions.h"

const char* filename = "file.csv";

void writeFile() {
  File outfile = LittleFS.open(filename, "w");  // open file.txt for writing
                                                // will create it if doesn't exist
  if (!outfile) {                               // if failed - maybe forgot to set the Filesystem in IDE
    Serial.println("fail open outfile");        // or didn't call LittleFS.begin()
    Serial.println("Cannot continue... Going into inf loop...");
    while (1)
      ;
  }

  Serial.println("Writing to file...");
  int i = 42;
  outfile.printf("i,i*2,i*3\n");
  for (int i = 0; i < 10; i++) {
    outfile.printf("%d,%d,%d\n", i, i * 2, i * 3);
  }
  outfile.close();  // close file
}
void readFile() {
  File infile = LittleFS.open(filename, "r");  // open file.txt for reading
  if (!infile) {                               // failed - file not there or forgot to create it
    Serial.println("fail open file");
    Serial.println("Cannot continue... Going into inf loop...");
    while (1)
      ;
  }

  Serial.println("Printing out from file...");
  while (infile.available()) {          // return number of bytes in file unread (like Serial buffer)
    Serial.print((char)infile.read());  // read each char and print it out to Serial monitor.
  }

  infile.close();  // close the file
}


void myPlugCB(uint32_t data) {
    // Tell my app not to write to flash, we're connected
}

void myUnplugCB(uint32_t data) {
    // I can start writing to flash again
}

void myDeleteDB(uint32_t data) {
    // Maybe LittleFS.remove("myfile.txt")?  or do nothing
}

void mountDrive() {
  singleFileDrive.onPlug(myPlugCB);
  singleFileDrive.onUnplug(myUnplugCB);
  //singleFileDrive.onDelete(myDeleteCB);
  singleFileDrive.begin(filename, filename);
  Serial.println("Filesys Mounted...\nGoing into inf loop");
  while (true)
    ;
}
