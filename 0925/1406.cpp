/*
    한 줄로 된 간단한 에디터를 구현하려고 한다. *최대 600,000글자
    '커서'는 문장 맨 앞, 문장  맨 뒤, 문장 중간 임의의 곳
    'L' - 커서를 왼쪽으로
    'R' - 커서를 오른쪽으로
    'B' - 커서 왼쪽에 있는 문자를 삭제 맨 앞이면 무시
    'P $' - $라는 문자를 커서 왼쪽에 추가

    초기 문자열 <= 100,000
    1 <= 명령어 수 <= 500,000
    무조건 O(NLOGN) or O(N) -> 한 명령어당 LogN을 넘으면 안 된다. 

*/
#include<iostream>
#include<vector>
#include<string>
#include<list>
using namespace std;

string init;
list<char> sentence;
int M;
int main(){
    cin >> init;
    for(int i = 0; i < init.size(); i++){
        sentence.push_back(init[i]);
    }
    cin >> M;
    cin.ignore();
    list<char>::iterator cursor = sentence.end();
    for(int i = 0; i < M; i++){
        string command;
        getline(cin, command);
        if(command[0]== 'L'){
            if(cursor != sentence.begin()) cursor--;
        }
        else if(command[0] == 'D'){
            if(cursor != sentence.end()) cursor++;
        }
        else if(command[0] == 'B'){
            if(cursor != sentence.begin()) {
                cursor = sentence.erase(--cursor);
            }
        }
        else if(command[0] == 'P'){
            sentence.insert(cursor, command[2]);
        }
    }

    for(auto it = sentence.begin(); it != sentence.end(); it++){
        cout << *it;
    }
    cout << "\n";
    return 0;
}