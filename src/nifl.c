#include <stdio.h>

#include <string.h>
#include <stdlib.h>

const char *PACKAGE_NAME = NULL;

void printHelp(const char *exec) {
  printf(
    "Usage: %s [install/help] <package>\n", 
    exec
  );
}

void parseArguments(const int argc, char **argv) {
  if (argc < 2) {
    printHelp(argv[0]);
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printHelp(argv[0]);
      continue;
    } else if (strcmp(argv[i], "install") == 0) {
      if (++i >= argc) {
        printf("Error: expected package name after 'install'\n");
        exit(1);
      }

      if (argv[i][0] == '\0' || argv[i][0] == '-') {
        printf("Error: invalid package name.\n");
        exit(1);
      }

      PACKAGE_NAME = argv[i];
      return;
    } else {
      printf("Error: unknown argument: \"%s\"\n", argv[i]);
      exit(1);
    }
  }
}

int main(int argc, char **argv) {
  parseArguments(argc, argv);
  
  if (!PACKAGE_NAME) return 0;

  printf("Package Name: %s\n", PACKAGE_NAME);

  return 0;
}
