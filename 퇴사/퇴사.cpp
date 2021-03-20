#include <iostream>

using namespace std;
// 2 ≤ N ≤ 6
// 1 ≤ Q ≤ 1,000
// 0 ≤ A[r][c] ≤ 100
// 0 ≤ Li ≤ N

int payment(int N, int* T, int* P){
    int final_payment = 0;
    int max_payment[N] = {0,};

    for(int i=N-1; i>=0; i--){
        if(T[i] > N-i){
            continue;
        }

        int min_day = i + T[i]; //9+1
        int pay = P[i];
        for(int j=min_day; j<N; j++){
            int curr_pay = P[i] + max_payment[j];
            
            if(pay >= curr_pay){
                continue;
            }
            pay = curr_pay;
        }
        max_payment[i] = pay;

        if(final_payment >= pay ){
            continue;
        }
        final_payment = pay;
    }
    


    return final_payment;
}

int main()
{ 
    int N = 0;
    cin >> N;

    int T[N] = {0,};
    int P[N] = {0,};
    for(int i=0; i<N; i++){
        cin >> T[i];
        cin >> P[i];
    }

    cout << payment(N, T, P);

    return 0;
}
