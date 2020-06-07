#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// -> Protocol supported
const char * schemes[] = {"http", "https", "ftp", "ssh", "git", "spotify"};

// -> Default ports by protocols
const char * ports[] = { "80", "443", "22", "21", "9418", "4070" };

// -> Simple regex to parse URL
const char * PATH_REGEX = "%[^/]/%[^*]";
const char * AUTHORITY_REGEX = "%[^:]:%[^:]";
const char * SIMPLE_REGEX = "%[^:]:%[^:]:%[^/]%[^*]";
const char * ADVANCED_REGEX = "%[^:]:%[^@]@%[^/]%[^*]";

int getScheme(char * scheme) {
  for(int i=0; i < sizeof(schemes); i++) {
    if(strcmp(scheme, schemes[i]) == 0) {
      return i;
    }
  }
  return -1;
}

void parseAuthority(char * url, char * arg1, char * arg2, const char * regex) {
  sscanf(url, regex, arg1, arg2);
}

void getDefaultPort(int iScheme, char * customPort) {
  if(strlen(customPort) == 0) {
    strcpy(customPort, ports[iScheme]);
  }
}

int parseURI(char * url) {
  int iScheme;
  char scheme[8];
  char arg2[64];
  char arg3[64];
  char arg4[256];
  bool withAuthority = strchr(url, '@');
  
  if(withAuthority) {
    sscanf(url, ADVANCED_REGEX, scheme, arg2, arg3, arg4);
  } else {
    sscanf(url, SIMPLE_REGEX, scheme, arg2, arg3, arg4);
  }
  iScheme = getScheme(scheme);

  if(iScheme == -1) {
    printf("Protocol `%s` is not supported!", scheme);
    return 0;
  } else {
    if(arg2[0] == '/') { // -> Not spotify
      memmove(arg2, arg2+2, strlen(arg2));
      printf("protocol : `%s`\n", scheme);
      char arg5[32];
      char arg6[256];
      if(withAuthority) { // -> Authority required
        if(iScheme != 3) { // -> Not ssh
          printf("domain = \"%s\"\n", arg3);
          parseAuthority(arg2, arg5, arg6, AUTHORITY_REGEX);
          printf("username = \"%s\"\n", arg5);
          printf("password = \"%s\"\n", arg6);
        } else {
          parseAuthority(arg3, arg5, arg6, AUTHORITY_REGEX);
          printf("username = \"%s\"\n", arg2);
          printf("domain = \"%s\"\n", arg5);
          printf("port = \"%s\"\n", arg6);
        }
        printf("path = \"%s\"\n", arg4);
      } else { // -> Without authority
        parseAuthority(arg2, arg5, arg6, PATH_REGEX);
        printf("domain = \"%s\"\n", arg5);
        getDefaultPort(iScheme, arg3);
        printf("port = \"%s\"\n", arg3);
        printf("path = \"%s\"\n", arg6);
      }
    } else {
      printf("type = \"%s\"\n", arg2);
      printf("songUid = \"%s\"\n", arg3);
    }
  }
}

int main(int argc , char* argv[]) {
  if(argc == 1) {
    printf("URL is missing in parameter!"); 
    return 0;
  }
  else {
    if(argc != 2) {
      printf("You have to pass only one parameter (URL)!");
    } else {
      printf("Trying to parse URL : %s\n", argv[1]);
      parseURI(argv[1]);
    }
  }
  return 0;
}