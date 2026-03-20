#include <stdio.h> // For printf() and scanf()

int main() {

    // --- Variables ---
    int octalNum;        // Stores the octal number from the user
    long long binaryNum = 0; // Stores the final binary number. long long for large numbers.
    int digit;           // Stores one digit of the octal number
    int place = 1;       // The place value (1, 1000, 1000000, etc.)
    int binaryEquivalent; // Stores the 3-bit binary value for one digit

    // --- Input ---
    printf("Enter an octal number: ");
    scanf("%d", &octalNum);

    int originalOctal = octalNum; // Save a copy for the final print message

    // --- Conversion Loop ---
    // This loop runs as long as there are digits left in the octal number
    while (octalNum != 0) {
        
        // 1. Get the last digit (e.g., 65 -> 5)
        digit = octalNum % 10;

        // 2. Use switch to find the 3-bit binary equivalent
        switch (digit) {
            case 0: binaryEquivalent = 0;   break; // 000
            case 1: binaryEquivalent = 1;   break; // 001
            case 2: binaryEquivalent = 10;  break; // 010
            case 3: binaryEquivalent = 11;  break; // 011
            case 4: binaryEquivalent = 100; break;
            case 5: binaryEquivalent = 101; break;
            case 6: binaryEquivalent = 110; break;
            case 7: binaryEquivalent = 111; break;
            default:
                printf("Error: Not a valid octal digit!\n");
                return 1; // Exit the program with an error
        }

        // 3. Stitch the binary numbers together
        // (e.g., add 101 * 1 to binaryNum, then add 110 * 1000)
        binaryNum = (binaryEquivalent * place) + binaryNum;

        // 4. Remove the last digit (e.g., 65 -> 6)
        octalNum /= 10;
        
        // 5. Increase the place value by 3 spots (x1000) for the next group
        place *= 1000;
    }

    // --- Output ---
    printf("Octal: %d  ->  Binary: %lld\n", originalOctal, binaryNum);

    return 0; // Indicates the program ran successfully
}