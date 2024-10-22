#include <stdio.h>
#include <math.h>       // For sin() and cos()
#include <string.h>     // For memset()
#include <unistd.h>     // For usleep()

int main() {
    float A = 0, B = 0; // Rotation angles
    float i, j;
    int k;
    float z[1760];  // Z-buffer array to store depth information
    char b[1760];   // Output buffer to store the ASCII characters

    // Clear the console screen
    printf("\x1b[2J");

    // Infinite animation loop
    for (;;) {
        // Initialize buffers
        memset(b, 32, 1760);   // Fill output buffer with spaces (' ')
        memset(z, 0, 7040);     // Fill z-buffer with 0 (initial depth)

        // Loop through the donut shape angles
        for (j = 0; j < 6.28; j += 0.07) {
            for (i = 0; i < 6.28; i += 0.02) {
                // Donut math
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5); // Calculate depth
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;

                // Calculate projected 2D coordinates (x, y)
                int x = (int)(40 + 30 * D * (l * h * m - t * n));
                int y = (int)(12 + 15 * D * (l * h * n + t * m));
                int o = x + 80 * y;

                // Calculate luminance index based on the normal vector
                int N = (int)(8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n));

                // Determine if the pixel should be drawn based on depth and screen boundaries
                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        // Move the cursor to the home position (top-left) and print the frame
        printf("\x1b[H");
        for (k = 0; k < 1760; k++) {
            putchar(k % 80 ? b[k] : 10);  // Print newline character after every 80 characters
        }

        // Increment rotation angles for animation
        A += 0.04;
        B += 0.02;

        // Sleep for a short duration to control the speed of the animation
        usleep(30000);
    }

    return 0;
}
    
