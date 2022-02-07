#include<bits/stdc++.h>
using namespace std;

#define FileIO \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

class GhostSensor{
    public:
    int n, m, k;
    int p;
    vector<vector<double>> grid;

    GhostSensor(int n, int m, int k){
        this->n = n;
        this->m = m;
        this->k = k;

        p = 0.9;
    }

    void MakeGrid(){
        grid.resize(n);
        for(int i=0; i<n; i++){
            grid[i].resize(m);
            for(int j=0; j<m; j++){
                grid[i][j] = 1.0/(n*m-k);
            }
        }
        for(int i=0; i<k; i++){
            int u,v;
            cin>>u>>v;
            grid[u][v] = 0;
        }
    }

    void PrintGrid(){
        cout<<endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cout<< fixed << setprecision(3)<<grid[i][j]<<"\t";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    void GhostMove(){
        ;
    }

};

int main(){
    FileIO;
    int n, m, k;
    cin>>n>>m>>k;
    cout<<"Input Successful"<<endl;
    cout<<"n= "<<n<< " m= "<<m<<" k= "<<k<<endl<<endl;

    GhostSensor *ghostsensor;
    ghostsensor = new GhostSensor(n, m, k);
    ghostsensor->MakeGrid();
    cout<<"MakeGrid Successful"<<endl;

    ghostsensor->PrintGrid();

    for(int t=1; t<=5; t++){
        cout<<"In time "<<t<<" :"<<endl;
        ghostsensor->GhostMove();
    }
    return 0;
}
