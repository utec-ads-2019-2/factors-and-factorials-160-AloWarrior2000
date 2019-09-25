#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> prime;

vector<int> mergeVec(vector<int> A, vector<int> B){
    for ( int i : B ){
        A.push_back(i);
    }
    return A;
}

void getnextpirme(){
    int x = prime.size();
    if (x == 0){
        prime.push_back(2);
    } else {
        int pos = prime[x-1];
        vector<int> dividers;
        dividers.clear();
        while (dividers.size() != 1) {
            pos++;
            dividers.clear();
            int divi = 1;
            while (divi != pos){
                divi++;
                if (pos%divi == 0){
                    dividers.push_back(divi);
                }
            }
        }
        prime.push_back(pos);
    }

}

vector<int> countRepet(vector<int> vec){
    vector<int> repes;
    int x = 0;
    int actual = prime[x];
    int cont = 0;
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] == actual){
            cont++;
        } else {
            repes.push_back(cont);
            //cout << cont << " ";
            actual = prime[++x];
            cont = 0;
            --i;
        }
    }
    repes.push_back(cont);
    return repes;
}

vector<int> separateFactors(int num){
    int i = 0;
    vector<int> factors;
    while (num!=1){
        if (i == prime.size()){
            getnextpirme();
        }
        if (num%prime[i] == 0){
            factors.push_back(prime[i]);
            //cout << num << " " << prime[i] << endl;
            num/=prime[i];
        }else{
            ++i;
        }
    }
    return factors;
}


vector<int> getFactorialVec(int num){
    if (num == 1){
        return separateFactors(num);
    }
    return mergeVec(separateFactors(num),getFactorialVec(num-1));
}

void printAns(int num, vector<int> ans){
    cout << num << "! = ";
    for ( int i : ans){
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    int N=1;
    vector<int> listofN;
    while(N!=0) {
        do {
            cin >> N;
        } while (100 <= N | 1 == N | N < 0 );
        listofN.push_back(N);
    }
    listofN.pop_back();
    for (int k : listofN) {
        auto x = getFactorialVec(k);
        sort(x.begin(), x.end());
        printAns(k, countRepet(x));
    }
    return 0;
}