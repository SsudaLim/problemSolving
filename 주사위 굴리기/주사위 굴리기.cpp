#include <iostream>
#include <map>
#include <vector>

using namespace std;

int one_line[7][4] = {
    {0,0,0,0},
    {2,3,5,4},
    {4,6,3,1},
    {1,2,6,5},
    {6,2,1,5},
    {1,3,6,4},
    {5,3,2,4}
};

map<int, vector<int>> moving = {
    {1, {1,0}},
    {2, {-1,0}},
    {3, {0,-1}},
    {4, {0,1}}
};


int roll(int* map, int N, int M, int* x, int* y, int location, int* dice, int* downside_num, int* eastside_num){
    int downside = *downside_num;
    int eastside = *eastside_num;
    
    //get upside number of dice after moving
    int next_downside = downside;
    int next_eastside = eastside;

    int* updown_line = one_line[eastside];
    int idx = -1;
    for(int i=0; i<4; i++){
        if(updown_line[i] == downside){
            idx = i;
            break;
        }
    }
    switch(location){
        case 1:
            next_downside = eastside;
            next_eastside = 7 - downside;
            break;
        case 2:
            next_downside = 7 - eastside;
            next_eastside = downside;
            break;
        case 3:
            if(++idx > 3) idx = 0;
            next_downside = updown_line[idx];
            break;
        case 4:
            if(0 > --idx) idx = 3;
            next_downside = updown_line[idx];
            break;
    }
    int next_upside = 7 - next_downside;

    
    //get dice location after moving
    vector<int> curr_moving = moving.at(location);
    int next_x = *x + curr_moving[0];
    int next_y = *y + curr_moving[1];
    
    bool move = false;
    if( -1<next_x && next_x<M  &&  -1<next_y && next_y<N ) move = true;

    //rolling dice
    if(!move) return -1;
    int map_loc = next_y*M + next_x;
    if(map[map_loc] == 0 ){
        map[map_loc] = dice[next_downside];
    }else{
        dice[next_downside] = map[map_loc];
        map[map_loc] = 0;
    }

    //return dice value
    *x = next_x;
    *y = next_y;
    *downside_num = next_downside;
    *eastside_num = next_eastside;
    return dice[next_upside];
}

int print_mat(int N, int M, int* mat){
    for(int i=0; i<N*M; i++){
        cout << mat[i] << " ";
        if((i+1)%M==0)  cout << "\n";
    }
    cout << "\n" << "\n";
}

int main(){
    //get input
    int N, M, K;
    int x, y;
    cin >> N >> M >> x >> y >> K;

    int map[N*M];
    for(int i=0; i<N*M; i++){
        cin >> map[i];
    }
    
    int command[K];
    for(int i=0; i<K; i++){
        cin >> command[i];
    }

    int dice[7] = {0, };
    int downside = 6;
    int eastside = 3;

    //roll
    for(int i=0; i<K; i++){
        int num = roll(map, N, M, &x, &y, command[i], dice, &downside, &eastside);
        if(num == -1) continue;
        cout << num;
    }
}