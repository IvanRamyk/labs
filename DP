#include <bits/stdc++.h>

using namespace std;

int const maxN = 10;

void read_Matrix(int Matrix[maxN][maxN], int &N){
    cin >> N;
    for (int i = 0; i <= N; ++i)
        for (int j = 0; j <= N; ++j)
            cin >> Matrix[i][j];
}

void get(pair <int, int> prev[maxN][maxN], int N){
    int i = N ;
    int j = N;
    vector < pair <int, int> > path;
    while (i + j){
        path.push_back({i, j});
        i = prev[i][j].first;
        j = prev[i][j].second;
    }
    reverse(path.begin(), path.end());
    cout << "0 0\n";
    for (int i = 0; i < path.size(); ++i)
        cout << path[i].first << " " << path[i].second << "\n";
}

void dinamic_solve(int Matrix[maxN][maxN], int N){
    int answer[maxN][maxN];
    pair < int, int > prev[maxN][maxN];
    answer[0][0] = Matrix[0][0];
    for (int i = 1; i <= N; ++i){
        answer[i][0] = answer[i - 1][0] + Matrix[i][0];
        prev[i][0] = {i - 1, 0};
    }
    for (int i = 1; i <= N; ++i){
        answer[0][i] = answer[0][i - 1] + Matrix[0][i];
        prev[0][i] = {0 , i - 1};
    }
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j){
            if (answer[i - 1][j - 1] > answer[i - 1][j] && answer[i - 1][j - 1] > answer[i][j - 1]){
                answer[i][j] = answer[i - 1][j - 1] + Matrix[i][j];
                prev[i][j] = {i - 1 , j - 1};
            }
            else if (answer[i - 1][j] > answer[i][j - 1]){
                answer[i][j] = answer[i - 1][j] + Matrix[i][j];
                prev[i][j] = {i - 1 , j};
            }
            else {
                answer[i][j] = answer[i][j - 1] + Matrix[i][j];
                prev[i][j] = {i , j - 1};
            }
        }
    cout << "Max = " << answer[N][N] << "\n";
    get(prev, N);
}

int main()
{
    int Matrix[maxN][maxN], N;
    read_Matrix(Matrix, N);
    dinamic_solve(Matrix, N);
    return 0;
}
