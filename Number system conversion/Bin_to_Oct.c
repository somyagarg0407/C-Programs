#include <stdio.h> // For printf() and scanf()
#include <math.h>  // For pow() function

int main() {

    // --- Variables ---
    long long binaryNum; // Stores the binary number input by the user
    int decimalNum = 0;  // Stores the decimal equivalent
    int octalNum = 0;    // Stores the final octal equivalent
    int i = 0;           // A counter, used as the power for 2 (2^0, 2^1, etc.)
    int remainder;       // Stores the last digit of the number

    // --- Input ---
    printf("Enter a binary number: ");
    scanf("%lld", &binaryNum);

    // Keep a copy of the original number for the final print message
    long long originalBinary = binaryNum; 

    // --- Step 1: Binary to Decimal Conversion ---
    // This loop runs as long as binaryNum is not 0
    while (binaryNum != 0) {
        
        // 1. Get the last digit (e.g., 1101 -> 1)
        remainder = binaryNum % 10; 
        
        // 2. Remove the last digit (e.g., 1101 -> 110)
        binaryNum /= 10; 
        
        // 3. Add to the decimal total: (digit * 2^position)
        // pow(2, i) calculates 2 to the power of i
        decimalNum += remainder * pow(2, i); 
        
        // 4. Increase the position (i) for the next digit
        ++i; 
    }

    // --- Step 2: Decimal to Octal Conversion ---
    i = 1; // Reset our helper 'i'. Now it will represent place value (1, 10, 100...)

    // This loop runs as long as the decimalNum is not 0
    while (decimalNum != 0) {
        
        // 1. Get the remainder when dividing by 8
        remainder = decimalNum % 8;
        
        // 2. Divide the decimal number by 8
        decimalNum /= 8;
        
        // 3. Build the octal number by adding the remainder at the correct place value
        octalNum += remainder * i;
        
        // 4. Move to the next place value (1s -> 10s -> 100s)
        i *= 10; 
    }

    // --- Output ---
    printf("Binary: %lld  ->  Octal: %d\n", originalBinary, octalNum);

    return 0; // Indicates the program ran successfully
}