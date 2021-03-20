#include <iostream>
#include <queue>
#include <map>

using namespace std;


map<char, vector<int>> moving = {
    {'e', {0, 1}},
    {'w', {0, -1}},
    {'n', {1, 0}},
    {'s', {-1, 0}}
};

map<char, vector<char>> lotation = {
    {'e', {'s','n'}},
    {'w', {'n','s'}},
    {'n', {'e', 'w'}},
    {'s', {'w', 'e'}}
};

void printMat(int N, int* map){
    cout << "\n";
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << map[i*N + j] << " ";
        }
        cout<< "\n";
    }

}

int playing(int* s, int* d, int L, int* map, int N){
    queue<int> x;
    queue<int> y;

    char cur_head = 'e';
    int cur_x  = 0;
    int cur_y = 0;

    x.push(cur_x);
    y.push(cur_y);
    map[cur_x*N + cur_y] = -1;

    int cur_s = 0;
    int turn_idx = 0;

    while(true){
        cur_s++;
        
        //change head direction that the snake move in this stage
        if(turn_idx < L && s[turn_idx] == cur_s-1){
            int turn_d = d[turn_idx];
            cur_head = lotation[cur_head][turn_d];
            turn_idx++;
        }

        //get location where the snake will move in next stage
        vector<int> move = moving[cur_head];
        cur_x = cur_x + move[0];
        cur_y = cur_y + move[1];

        
        //check if the snake can moveback
        if(cur_x < 0 || cur_x > N-1 || cur_y < 0 || cur_y > N-1 || map[cur_x*N + cur_y] == -1) break;

        //check if there is an apple
        bool is_apple = false;
        if(map[cur_x*N + cur_y] == 1) is_apple = true;

        //move snake
        x.push(cur_x);
        y.push(cur_y);
        map[cur_x*N + cur_y] = -1;
            
        //change map according to the existance of apple
        if(!is_apple){
            int prv_x = x.front();
            int prv_y = y.front();
            x.pop();
            y.pop();
            map[prv_x*N + prv_y] = 0;
        }


    }

    return cur_s;
}


int main(){

    //get input
    int N, K;
    cin >> N >> K;

    //get and check apple location
    int map[N*N] = {0, };
    for(int i=0; i<K; i++){
        int x, y;
        cin >> x >> y;
        map[(x-1)*N + (y-1)] = 1;
    }

    int L;
    cin >> L;

    //get when and where the snake change the location
    int sec[L];
    int dir[L];
    for(int i=0; i<L; i++){
        int s;
        char d;
        cin >> s >> d;

        if(d=='L') d = 0;
        else d = 1;

        sec[i] = s;
        dir[i] = d;
    }

    //get when the game is over
    int end = playing(sec, dir, L, map, N);
    cout << end;

    return 0;
}