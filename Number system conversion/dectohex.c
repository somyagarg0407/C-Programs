#include <stdio.h>

int main() {
    long decimalNumber;
    int remainder;
    int i = 0;
    char hexNumber[100]; // Array to store the hexadecimal digits

    // 1. Get input from user
    printf("Enter any decimal number: ");
    scanf("%ld", &decimalNumber);

    // 2. Loop until the number becomes 0
    while (decimalNumber != 0) {
        remainder = decimalNumber % 16; // Find the remainder

        // 3. Convert remainder to Hex character
        if (remainder < 10) {
            // For 0-9, we add 48 (ASCII value of '0')
            hexNumber[i] = remainder + 48;
        } else {
            // For 10-15 (A-F), we add 55. 
            // Example: 10 + 55 = 65, which is ASCII for 'A'
            hexNumber[i] = remainder + 55;
        }

        i++; // Move to the next position in the array
        decimalNumber = decimalNumber / 16; // Divide input by 16
    }

    // 4. Print the array in reverse order
    printf("Hexadecimal value: ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hexNumber[j]);
    }
    printf("\n");

    return 0;
}