#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

int bottomUp(vector<int> cards, int n);

int topDown(vector<int> cards, int i, int j);

int recursive(vector<int> cards, int i, int j);

#define ROWS 100
#define COLS 100

int dp[ROWS][COLS];

int main() {
    vector<int> cards;
    cards.push_back(2);
    cards.push_back(100);
    cards.push_back(1);
    cards.push_back(2);

    cout << "Recursive: " << recursive(cards, 0, cards.size() - 1) << endl;
    memset(dp, -1, sizeof(dp));
    cout << "Top Down: " << topDown(cards, 0, cards.size() - 1) << endl;
    cout << "Bottom Up: " << bottomUp(cards, cards.size());
    return 0;
}

int bottomUp(vector<int> cards, int n) {
    int Dp[n][n];
    memset(Dp, 0, sizeof(Dp));
    int x = 0, y = 0;

    //base-case #1
    for (int i = 0; i < n; i++)
        Dp[i][i] = cards.at(i);

    //base-case #2
    for (int i = 0; i < n - 1; i++) {
        Dp[i][i + 1] = max(cards.at(i), cards.at(i + 1));
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 2; j < n; j++) { //starting j from i as j can't be lower than i. It is not possible.
            x = min(Dp[i + 2][j], Dp[i + 1][j - 1]);
            y = min(Dp[i + 1][j - 1], Dp[i][j - 2]);
            Dp[i][j] = max(cards.at(i) + x, cards.at(j) + y);
        }
    }
    return Dp[0][n - 1];
}

int topDown(vector<int> cards, int i, int j) {
    if (i == j) //only one card is left.
    {
        dp[i][j] = cards.at(i);
        return cards.at(i); // j could be returned as well.
    }

    if (j - i == 1) //two cards are left, then we chose the one with max value
    {
        dp[i][j] = max(cards.at(i), cards.at(j));
        return dp[i][j];
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    dp[i][j] = max(cards.at(i) + min(recursive(cards, i + 2, j), recursive(cards, i + 1, j - 1)),
                   cards.at(j) + min(recursive(cards, i + 1, j - 1), recursive(cards, i, j - 2)));

    return dp[i][j];
}

int recursive(vector<int> cards, int i, int j) {
    if (i == j) //only one card is left.
    {
        return cards.at(i); // j could be returned as well.
    }

    if (j - i == 1) //two cards are left, then we chose the one with max value
    {
        return max(cards.at(i), cards.at(j));
    }

    return max(cards.at(i) + min(recursive(cards, i + 2, j), recursive(cards, i + 1, j - 1)),
               cards.at(j) + min(recursive(cards, i + 1, j - 1), recursive(cards, i, j - 2)));
}