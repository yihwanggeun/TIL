/*
    20006번 랭킹전 대기열
    1.문제 이해
    운영하던 게임에 랭킹전 기능을 추가하려고 한다. 비슷한 레벨의 플레이어들을 매칭하여 게임을 시작

    1.1 가능한 방이 없으면 새로운 방 추가 후 입장(이 방은 +- 10)
    1.2 가능한 방이 있으면 정원이 모두 찰 때까지 대기시킨다.
    2. 입장 가능한 방이 여러개면 먼저 생성된 방에 입장
    
    2. 구현 방식
    첫번쨰 줄 플레이어 수, 방의 정원 
    방 Vector<방 기준 레벨, vector<Person>>

*/
#include<iostream>
#include<vector>
#include <algorithm> // sort 함수를 사용하기 위해 추가

using namespace std;

struct Person{
    int id;
    int level;
    string name;
};

int p, m;
vector<pair<int, vector<Person> > > room;

bool cmp(Person &a, Person &b){
    return a.name < b.name;
}

int checkRoom(int player_level){
    for(int i = 0; i< room.size(); i++){
        if(room[i].first-10 <= player_level && room[i].first + 10 >= player_level && room[i].second.size() < m){
            return i;
        }
    }
    //절대값을 써서 10차이 
    return -1;
}

void checkResult(){
    for(int i = 0; i< room.size(); i++){
        if(room[i].second.size() == m) cout << "Started!\n";
        else cout << "Waiting!\n";

        sort(room[i].second.begin(), room[i].second.end(), cmp);

        for(int j = 0; j < room[i].second.size(); j++){
            cout << room[i].second[j].level << " " << room[i].second[j].name << "\n";
        }
    }
    return; 
}
int main(){
    cin >> p >> m;
    for(int i = 0; i < p; i++){
        int player_level; string player_name;
        cin >> player_level >> player_name;
        
        // 입장 가능한 방이 없을 때
        int avail = checkRoom(player_level);
        if(avail ==-1){
            room.push_back({player_level, {{i, player_level, player_name}}});
        }

        // 입장 가능한 방이 있을 때
        else{
            room[avail].second.push_back({i, player_level, player_name});
        }
    }
    checkResult(); 
}