#include <stdio.h>

int main() {
    // Initializes the transactions array with deposit and withdrawal values.
    // 3 different array options:
    // int trans[] = {200, -150, -500, -400, -50, -200, 300};
    // int trans[] = {23, 150, 50, -850, -7, 1000, 600}; 
    int trans[] = {-23, -150, -50, -850, -7, -1000, -600};
    // Initializes an array with size of trans array to store unprocessed transactions.
    int to_process[sizeof(trans) / sizeof(trans[0])];
    int balance_amt = 1000;// Initializes the balance_amt with 1000 AED.
    int to_process_index = 0;// Index variable to keep track of no.of transactions to be processed.

    // Loops through each transaction in the transactions array.
    for (int i = 0; i < sizeof(trans) / sizeof(trans[0]); i++) {
        // Checks if the transaction is a withdrawal and if it exceeds the current balance_amt.
        if (trans[i] < 0 && balance_amt + trans[i] < 0) {
            // If the withdrawal exceeds the balance_amt, print an error message.
            printf("Invalid transaction: %d\n", trans[i]);
            to_process[to_process_index++] = trans[i];
        } else {
            // For valid transactions (either deposit or withdrawal within balance_amt), the balance_amt is updated.
            balance_amt += trans[i];

            // If the balance_amt becomes zero, the code stops processing further transactions.
            if (balance_amt == 0) {
                printf("Balance is zero, no further transactions will be processed.\n");
                for (int j = i + 1; j < sizeof(trans) / sizeof(trans[0]); j++) {
                    to_process[to_process_index++] = trans[j];
                }
                break;
            }
        }
    }

    // Prints the final balance_amt after all valid transactions have been processed.
    printf("Final balance_amt: %d AED\n", balance_amt);

    // Prints the unprocessed transactions.
    printf("Unprocessed transactions: ");
    for (int i = 0; i < to_process_index; i++) {
        printf("%d ", to_process[i]);
    }
    printf("\n");

    return 0;
}