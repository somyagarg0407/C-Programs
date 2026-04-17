#include <stdio.h>

int count = 0;

void hanoi(int n, char start, char aux, char dest)

{
    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n", start, dest);
        count++;
        return;
    }
    hanoi(n - 1, start, dest, aux);
    printf("Move disk %d from %c to %c\n", n, start, dest);
    count++;
    hanoi(n - 1, aux, start, dest);
}

int main()

{
    int n;
    printf("Enter number of disks: ");
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    printf("\nTotal moves = %d\n", count);
    return 0;

}