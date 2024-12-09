#include <LittleFS.h>  // Little File System library
                       // creates global var called LittleFS
#include "myFSFunctions.h"

#pragma region EnumDeclaration

#define LIST_OF_OPTIONS \
  X(WriteFile) \
  X(ReadFile) \
  X(MountDrive)

#define X(value) value,
enum option { LIST_OF_OPTIONS };
#undef X

#define X(value) #value,
const char* color_string[] = { LIST_OF_OPTIONS };
#undef X

#pragma endregion Enumeration and String Declaration using X macro trick

/*
* @brief   Prompts user for a menu option thru Serial Monitor
* @return  the option enum value selected.
*/
option chooseOption() {
  int ret;
  while (true) {
    Serial.println("Choose a numeric option:");
    for (int i = WriteFile; i <= MountDrive; i++) {
      Serial.printf("\t%d\t%s\n", i, color_string[i]);
    }

    while (!Serial.available())
      ;
    ret = Serial.parseInt();
    if (WriteFile <= ret && ret <= MountDrive) break;
  }

  return static_cast<option>(ret);
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  if (!LittleFS.begin()) {  // MUST initialize LittleFS
    Serial.println("Cannot Init LittleFS\nLikely reason is you did not select a FileSize in Tools->Flash Size");
    Serial.println("Please select IDE Menu Tools->Flash Size and choose any option other than (No FS)");
    Serial.println("Example:   8MB (Sketch: 8128KB, FS: 64KB)");
    Serial.println("Cannot continue... Going into inf loop...");
    while (true)
      ;
  }

  Serial.println("Little FS Initized...");
}

void loop() {
  option doit = chooseOption();

  Serial.printf("Executing %s\n", color_string[doit]);

  // I'd rather make this a jump table but most students might not understand it
  // so using a switch case statement.
  switch (doit) {
    case WriteFile:
      writeFile();
      break;
    case ReadFile:
      readFile();
      break;
    case MountDrive:
      mountDrive();
      break;
    default:
      Serial.printf("oops... sumthin wrong\n");
  }
  
}
