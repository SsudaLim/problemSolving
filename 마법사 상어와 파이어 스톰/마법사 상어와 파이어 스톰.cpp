#include <iostream>
#include <cmath>
#include <queue>

using namespace std;
// 2 ≤ N ≤ 6
// 1 ≤ Q ≤ 1,000
// 0 ≤ A[r][c] ≤ 100
// 0 ≤ Li ≤ N


void printMat(int* A, int side){
    for(int i=0; i<side; i++){
        for(int j=0;j<side; j++){
            cout << A[i*side + j] << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";
}


void rotateInnerMat(int* A, int side, int L, int base_x, int base_y){
    //deep copy of mat A
    int A_copy[L*L];
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            A_copy[i*L + j] = A[(i+base_x)*side + (j+base_y)];
        }
    }

    //change location of number
    for(int i=0; i<L; i++){
        int y = L - i - 1;
        for(int j=0; j<L; j++){
            A[(j+base_x)*side +(y+base_y)] = A_copy[i*L + j];
        }

    }
}

void rotateMat(int* A, int side, int L){
    for(int i=0; i<side; i+=L){
        for(int j=0; j<side; j+=L){
            rotateInnerMat(A, side, L, i, j);
        }
    }
}

void meltIce(int *A, int side){
    //copy map
    int A_copy[side*side];
    for(int i=0; i<side; i++){
        for(int j=0; j<side; j++){
            A_copy[i*side + j] = A[i*side + j];
        }
    }

    //melt ice
    int x_move[4] = {0, -1, 0, 1};
    int y_move[4] = {-1, 0, 1, 0};
    for(int i=0; i<side; i++){
        for(int j=0; j<side; j++){
            int count = 0;
            for(int k=0; k<4; k++){
                int x = i + x_move[k];
                int y = j + y_move[k]; 
                if(x>-1 && y>-1 && x<side && y<side && A_copy[x*side+y]>0){
                    count++;
                }
            }

            if(count<3 && A[i*side+j]>0){
                A[i*side+j]--;
            }
        }
    }
}


int getTotalIce(int *A, int side){
    int total_ice = 0;
    for(int i=0; i<side; i++){
        for(int j=0; j<side; j++){
            total_ice += A[i*side + j];
        }
    }
    return total_ice;
}


int getChunkSize(int *A_init, int *A, int side, int x_start, int y_start){
    if(A_init[x_start*side + y_start] > 0|| A[x_start*side + y_start] < 1){
        return 0;
    }

    int x_move[4] = {0, -1, 0, 1};
    int y_move[4] = {-1, 0, 1, 0};

    queue<int> que_x;
    queue<int> que_y;
    que_x.push(x_start);
    que_y.push(y_start);

    int count = 0;
    bool is_adjacent = false;
    while(que_x.size()){
        x_start = que_x.front();
        y_start = que_y.front();
        que_x.pop();
        que_y.pop();
        if(A_init[x_start*side + y_start] > 0){
            continue;
        }
        A_init[x_start*side + y_start] = ++count;
        for(int i=0; i<4; i++){
            int x = x_start + x_move[i];
            int y = y_start + y_move[i];
            if(x>-1 && y>-1 && x<side && y<side && A[x*side + y]>0){
                que_x.push(x);
                que_y.push(y);
            }
        }
    }
    return count;
}

int getBiggestIce(int *A, int side){
    int ice_max = 0;
    int ice_count = 0;
    int A_init[side*side] = {0,};
    
    for(int i=0; i<side; i++){
        for(int j=0; j<side; j++){
            ice_count = getChunkSize(A_init, A, side, i, j);
            if(ice_count > ice_max){
                ice_max = ice_count;
            }
        }
    }
    return ice_max;
}

int main()
{ 
    int N,Q;
    cin >> N >> Q;
    N = pow(2, N);
    
    int A[N*N];
    int L[Q];
    for(int i=0; i<N*N; i++){
        cin >> A[i];
    }

    for(int i=0; i<Q; i++){
        cin >> L[i];
        L[i] = pow(2,L[i]);
        
        rotateMat(A, N, L[i]);
        meltIce(A, N);
    }

    int total_ice = getTotalIce(A, N);
    cout << total_ice << "\n";

    int big_ice = getBiggestIce(A, N);
    cout << big_ice;


    return 0;
}