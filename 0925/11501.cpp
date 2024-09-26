/*
    11501번 주식

    1. 문제 이해
    매일 세가지 중 한 행동을 한다.
    1. 주식 하나를 산다
    2. 원하는 만큼 가지고 있는 주식을 판다.
    3. 아무것도 안 한다.

    미래를 예상하는 뛰어난 안목이 있지만, 자신이 최대 이익을 얻을 수 있는 법을 모른다.
    최대 이익이 얼마인지 계산

    2. 문제 해결
    '그떄 팔 걸', '그떄 살 걸'이라는 개념으로 접근해야 할 것 같다.
    오르다가 떨어진 경우 
    유지하다가 떨어진 경우
    떨어지다가 떨어진 경우

    떨어지다가 오른 경우
    유지하다가 오른 경우
    오르다가 오른 경우
*/
#include<iostream>
#include<vector>

using namespace std;
vector<int> have;
vector<int> total;
int T;

long long sellAll(int high_value){
    long long sum_sell = 0;
    for(int value : have){
        if(high_value - value >= 0) sum_sell += high_value - value;
    }
    have = vector<int>();
    return sum_sell;
}

void macro(){
    int N; cin >> N;
    int state = 0;
    long long result = 0;

    have = vector<int>();
    total = vector<int>();

    int max_price = 0;
    for(int i = 0; i < N; i++) {int temp; cin >> temp; total.push_back(temp);}
    for(int i = N-1; i >= 0; i--){
        if(total[i] <= max_price){
            result += max_price - total[i];
        }
        else{
            max_price = total[i];
        }
    }
    
    cout << result << "\n";
    return;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int i = 0 ; i < T; i++) macro();
}