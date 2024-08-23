#include <stdio.h>
#include <assert.h>
#include <string.h>

void captureOutput(void (*func)(), char* output) {
    // Redirect stdout to a buffer
    freopen("/tmp/output.txt", "w", stdout);
    func();
    fflush(stdout);
    freopen("/dev/tty", "w", stdout);
    
    // Read the buffer into the output variable
    FILE* file = fopen("/tmp/output.txt", "r");
    fread(output, sizeof(char), 1024, file);
    fclose(file);
}

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);
        }
    }
    return i * j;
}

int main() {
    char output[1024] = {0};
    captureOutput(int (*printColorMap)(), output);

    const char* expectedOutput = 
        "1 | White | Blue\n2 | White | Orange\n3 | White | Green\n4 | White | Brown\n5 | White | Slate\n"
        "6 | Red | Blue\n7 | Red | Orange\n8 | Red | Green\n9 | Red | Brown\n10 | Red | Slate\n"
        "11 | Black | Blue\n12 | Black | Orange\n13 | Black | Green\n14 | Black | Brown\n15 | Black | Slate\n"
        "16 | Yellow | Blue\n17 | Yellow | Orange\n18 | Yellow | Green\n19 | Yellow | Brown\n20 | Yellow | Slate\n"
        "21 | Violet | Blue\n22 | Violet | Orange\n23 | Violet | Green\n24 | Violet | Brown\n25 | Violet | Slate\n";
    
    assert(strcmp(output, expectedOutput) == 0);  // Check if the output matches

    int result = printColorMap();
    assert(result == 25);  // Check if return value is 25
    printf("All is well (maybe!)\n");
    return 0;
}
