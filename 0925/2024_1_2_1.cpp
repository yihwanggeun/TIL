/*
    문제 이해
    R행 C열 격자에 마법의 숲을 탐색하려고 한다. 1~R -> -1을 꼭 해줘야한다.
    숲의 북쪽에서만 숲으로 들어올 수 있다.
    K 명의 정령은 각자 골렘을 타고 숲을 탐색
    - 골렘은 십자구조를 가지고 있다.
    - 중앙을 제외한 나머지는 골렘의 출구
    - 탑승 (어디서나) 하차 (정해진 출구)
    - 가장 위쪽에서 시작해서 골렘의 중앙이 C_i 열이될 때까지 내려온다.
    - 초기 골렘의 출구는 d_i방향에 위치
    우선 순위
    1. 남쪽으로한칸 내려간다 (아래 공간이 있을 경우에만)
    2. 왼쪽으로 한 번 갔다가 거기서 반시계 회전 그리고 아래쪽으로 (출구가 회전)
    3. 오른쪽으로 한 번 갔다가 거기서 시계 회전 그리고 아래쪽으로 (출구가 회전))

    남쪽으로 더이상 갈 수없다면 정령은 골렘 내에서 이동 - 여기서 이동할 수 있다.
    그리고 골렘의 몸 일부가 숲을 벗어났다면 새롭게 시작

    해결 전략
    골렘
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int drow[4] = {-1, 0, 1, 0};
int dcol[4] = {0, 1, 0, -1};
int checkDrow[9] = {0, -1, -2, -1, 0, 1, 2, 1};
int checkDcol[9] = {-2, -1, 0, 1, 2, 1, 0, -1};
int visited[71][71] = {0};
int max_row = -1;
int max_range = -1;
struct Monster{
    int id;
    int row;
    int col;
    int d;
    int live;
};

vector<pair<int,int> > cc;
vector<Monster> v;
vector<pair<int,int> > out;

int R, C, K;
int map[71][71];
int result = 0;
bool isRange(pair<int,int> point){
    if(point.second < 0 || point.first + 1 > R || point.second + 1 > C) return false;
    return true;
}

bool checkMoveDown(int idx,int crow, int ccol){
        
    for(int i = 0; i < 4; i++){
        int nrow = crow + 1 + drow[i];
        int ncol = ccol + dcol[i];
        if(nrow + 1 > R) return false;
        if(nrow < 0) continue;
        if(map[nrow][ncol]!=-1 && map[nrow][ncol]!=idx) return false;
    }

    return true;
}

bool checkMoveLeft(int idx,int crow, int ccol){
        
    for(int i = 0; i < 4; i++){
        int nrow = crow + drow[i];
        int ncol = ccol - 1 + dcol[i];
        if(ncol < 0) return false;
        if(nrow < 0) continue;
        if(map[nrow][ncol]!=-1 && map[nrow][ncol]!=idx) return false;
    }

    return true;
}

bool checkMoveRight(int idx, int crow, int ccol){

    for(int i = 0; i < 4; i++){
        int nrow = crow + drow[i];
        int ncol = ccol + 1 + dcol[i];
        if(ncol + 1 > C) return false;
        if(nrow < 0) continue;
        if(map[nrow][ncol]!=-1 && map[nrow][ncol]!=idx) return false;
    }

    return true;
}

void removeMap(int row, int col){
    for(int i = 0; i < 4; i++){
        int nrow = row + drow[i];
        int ncol = col + dcol[i];
        if(nrow < 0 || ncol < 0) continue;
        map[nrow][ncol] = -1;
    }
    if(row < 0 || col < 0) return;
    map[row][col] = -1;
    return;
    
}

void addMap(int row, int col, int idx){
    for(int i = 0; i < 4; i++){
        int nrow = row + drow[i];
        int ncol = col + dcol[i];
        if(nrow < 0 || ncol < 0) continue;
        map[nrow][ncol] = idx;
    }
    if(row < 0 || col < 0) return;
    map[row][col] = idx;
}

void moveDown(int idx){
    Monster current = v[idx];

    removeMap(current.row, current.col);

    current.row++;
    v[idx] = current;  
    cc[idx] = {current.row, current.col};
    addMap(current.row, current.col, idx);
    //cout << "아래로 이동중 : " << idx << " " << v[idx].row << " " << v[idx].col << "\n";

    return;
}

void moveLeft(int idx){
    Monster current = v[idx];

    removeMap(current.row, current.col);

    current.col--;
    v[idx] = current;
    cc[idx] = {current.row, current.col};

    addMap(current.row, current.col, idx);

    //cout << "왼쪽 이동중 : " << idx << " " << v[idx].row << " " << v[idx].col << "\n";

    return;
}
void moveRight(int idx){
    Monster current = v[idx];
    
    removeMap(current.row, current.col);

    current.col++;
    v[idx] = current;
    cc[idx] = {current.row, current.col};

    addMap(current.row, current.col, idx);

    //cout << "오른쪽 이동중 : " << idx << " " << v[idx].row << " " << v[idx].col << "\n";

    return;
}

bool checkMoveMore(int idx){
    for(int i = 0; i < 4; i++){
        int nrow = v[idx].row + drow[v[idx].d] + drow[i];
        int ncol = v[idx].col + dcol[v[idx].d] + dcol[i];
        if(nrow < 0 || ncol < 0 || nrow + 1 > R || ncol + 1 > C) continue;
        if(map[nrow][ncol] != idx && map[nrow][ncol] != -1) return true; 
    }
    return false;
}

void dfs(int row, int col){
    if(max_row == max_range) return;
    if(max_row < row) max_row = row;
    for(int i = 0; i < 4; i++){
        int nrow = row + drow[i];
        int ncol = col + dcol[i];
        auto it = find(out.begin(), out.end(), make_pair(row, col));
        if(nrow < 0 || ncol < 0 || nrow + 1 > R || ncol + 1 > C) continue;
        if(visited[nrow][ncol]==1) continue;
        if(map[nrow][ncol]==-1) continue;
        if(map[nrow][ncol] != map[row][col] && (it == out.end())) continue;
        visited[row][col] = 1;
        dfs(nrow, ncol);    
        
    }
    return;
}

bool checkFull(int idx){
    for(int i = 0; i < 4; i++){
        int nrow = v[idx].row + drow[i];
        int ncol = v[idx].col + dcol[i];
        if(nrow < 0) return true;
    }
    return false;
}
void macro(int idx){

    while(1){
        int crow = v[idx].row;
        int ccol = v[idx].col;
        
        if(checkMoveDown(idx, crow, ccol)){
            moveDown(idx);
            continue;
        }
        if(checkMoveLeft(idx, crow, ccol) && checkMoveDown(idx, crow, ccol-1)){
            moveLeft(idx);
            moveDown(idx);
            v[idx].d = (v[idx].d+3) % 4;
            continue;
        }
        if(checkMoveRight(idx, crow, ccol) && checkMoveDown(idx, crow, ccol+1)){
            moveRight(idx);
            moveDown(idx);
            v[idx].d = (v[idx].d+1) % 4;
            continue;
        }
        break;
    }
    
    //cout << "최종 위치 : " << idx << " " << v[idx].row << " " << v[idx].col << "\n";

    if(checkFull(idx)){
        for(int i = 0; i < 71; i++) for(int j = 0; j < 71; j++) map[i][j] = -1;
        out = vector<pair<int,int> >();
        return;
    }

    out.push_back({v[idx].row + drow[v[idx].d], v[idx].col + dcol[v[idx].d]});
    // 출구를 vector에 저장
    for(int i = 0 ; i < R; i++){
        for(int j = 0; j < C; j++){
            if(map[i][j]!=-1){
                max_range = i;
                break;
            }
        }
    }
    max_range++;
    dfs(v[idx].row, v[idx].col);
    visited[v[idx].row][v[idx].col] = 1;
    result += max_row + 1;
    max_row = -1;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> R >> C >> K;
    for(int i = 0; i < K; i++) {
        int start_col, start_d;
        cin >> start_col >> start_d;
        cc.push_back({-2, start_col});
        v.push_back({i, -2, start_col-1, start_d, 1});
    }

    for(int i = 0; i < 71; i++) for(int j = 0; j < 71; j++) map[i][j] = -1;
    
    for(int i = 0; i < K; i++){
        macro(i);
        for(int i = 0; i < 71; i++) for(int j = 0; j < 71; j++) visited[i][j] = 0;
        
    }
    cout << result << "\n";
}

