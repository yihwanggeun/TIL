/*
    1927번 최소 힙
    1. 문제 이해
     널리 잘 알려진 자료구조로 최소 힙이 있다.
     최소 힙을 사용해서 
     1. 배열에 자연수 x를 넣는다
     2. 배열에서 가장 작은 값을 출력하고, 그 값을 배열에서 제거한다,
    
    2. 제약 사항
        1 <= 연산의 개수 <= 100,000
        0 <= 넣는 자연수 x <= 2^31 (Int형이면 충분)

    3. 자료 구조
        Priority Queue를 사용해서 넣는데 - Min Heap으로 바꿔서 넣어야 한다. 
        그리고 그냥 삭제 - erase?
    4. 시간 복잡도
        문제 X

*/
#include <iostream>
#include <queue>

using namespace std;

priority_queue<int,vector<int>, greater<int> > pq;
int N;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        int temp; cin >> temp;
        if(temp == 0){
            if(pq.empty()){
                cout << 0 << "\n";
            }
            else{
                cout << pq.top() << "\n";
                pq.pop();
            }
           
        }
        else{
            pq.push(temp);
        }
    }
}