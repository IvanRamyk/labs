#include <stdio.h>
#include <stdlib.h>

int* longest_increasing_subsequence(const int arr[], int n)
{
    const int INF = 1000 * 1000 * 1000;
    int dp[n + 2];
    int ind[n + 2];
    int prev[n];
    dp[0] = -INF;
    ind[0] = -1;
    for (int i = 1; i <= n + 1; ++i)
        dp[i] = INF;

    for (int i = 0; i < n; ++i) {
        int j = 0;
        while (arr[i] >= dp[j])
            ++j;
        dp[j] = arr[i];
        ind[j] = i;
        prev[i] = ind[j - 1];
    }


    int len = 0;
    while (dp[len + 1] != INF) {
        len++;
    }

    int* lis = malloc(len + 1);
    lis[0] = len;
    int cur = ind[len];
    int ind_in_lis = len;
    while (cur != -1) {
        lis[ind_in_lis] = arr[cur];
        ind_in_lis--;
        cur = prev[cur];
    }
    return lis;
}