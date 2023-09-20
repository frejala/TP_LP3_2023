#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define NUM_ACCOUNTS 5

float account_balances[NUM_ACCOUNTS];

/* Initialize the array of account balances. */
void initialize_accounts()
{
    for (int i = 0; i < NUM_ACCOUNTS; i++)
    {
        account_balances[i] = 1000.0; // Initialize all accounts with a balance of $1000
    }
}

/* Transfer DOLLARS from account FROM_ACCT to account TO_ACCT. Return
0 if the transaction succeeded, or 1 if the balance FROM_ACCT is
too small. */
int process_transaction(int from_acct, int to_acct, float dollars)
{
    int old_cancel_state;
    /* Check the balance in FROM_ACCT. */
    if (account_balances[from_acct] < dollars)
        return 1;
    /* Begin critical section. */
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
    /* Move the money. */
    account_balances[to_acct] += dollars;
    account_balances[from_acct] -= dollars;
    /* End critical section. */
    pthread_setcancelstate(old_cancel_state, NULL);
    return 0;
}

int main()
{
    initialize_accounts();

    int comprobante = process_transaction(1, 3, 100.0);

    if (comprobante == 1)
    {
        printf("Transaction denied\n");
    }
    else
    {
        printf("Transaction approved\n");
    }
    return 0;
}
