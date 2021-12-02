#define FileIO \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#include<bits/stdc++.h>
using namespace std;

class Board{
    int k;
    vector<vector<int>> square;
    vector<Board> adjBoard;
    bool visited;
    public:
    Board(int k){
        this->k=k;
        square.resize(k);
        visited=false;
    }
    int getk(){
        return k;
    }

    void insertValue(int row, int val){
        square[row].push_back(val);
    }

    int getCorrectRow(int val){
        return val/k;
    }

    int getCorrectColumn(int val){
        return val%k;
    }

    int hammingDistance(){
        int distance=0;
        for(int i=0; i<square.size(); i++){
            for(int j=0; j<square[i].size(); j++){
                if(square[i][j] != 0){
                    distance+= abs(getCorrectRow(square[i][j])-i)+abs(getCorrectColumn(square[i][j])-j);
                }
            }
        }
        return distance;
    }
    void printBoard(){
        cout<<"----"<<endl;
        for(int i=0; i<square.size(); i++){
            for(int j=0; j<square[i].size(); j++){
                cout<<square[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"----"<<endl;
    }

    void printAdjBoard(){
        for(auto i:adjBoard){
            i.printBoard();
        }
    }

    void swapVal(int rowSrc, int rowDest, int colSrc, int colDest){
        swap(square[rowSrc][colSrc], square[rowDest][colDest]);
    }

    bool isVisited(){
        return visited;
    }

    void makeVisited(){
        visited = true;
    }

    void getAdjBoard(){
        
        for(int i=0; i<k; i++){
            for(int j=0; j<k; j++){
                if(square[i][j] == 0){
                    if(i>0 and i<k-1){
                        Board temp(k);
                        temp = *this;
                        temp.swapVal(i, i+1, j, j);
                        adjBoard.push_back(temp);
                        temp = *this;
                        temp.swapVal(i, i-1, j, j);
                        adjBoard.push_back(temp);
                    }
                    else if(i==0){
                        Board temp(k);
                        temp = *this;
                        temp.swapVal(i, i+1, j, j);
                        adjBoard.push_back(temp);
                    }
                    else if(i==k-1){
                        Board temp(k);
                        temp = *this;
                        temp.swapVal(i, i-1, j, j);
                        adjBoard.push_back(temp);
                    }
                    if(j>0 and j<k-1){
                        Board temp(k);
                        temp = *this;
                        temp.swapVal(i, i, j, j+1);
                        adjBoard.push_back(temp);
                        temp = *this;
                        temp.swapVal(i, i, j, j-1);
                        adjBoard.push_back(temp);
                    }
                    else if(j==0){
                        Board temp(k);
                        temp = *this;
                        temp.swapVal(i, i, j, j+1);
                        adjBoard.push_back(temp);
                    }
                    else if(j==k-1){
                        Board temp(k);
                        temp = *this;
                        temp.swapVal(i, i, j, j-1);
                        adjBoard.push_back(temp);
                    }
                }
            }
        }
    }
};


int main(){
    FileIO;
    
    int k;
    cin>>k;
    Board *board = new Board(k);
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            string str;
            int val;
            cin>>str;
            if(str != "*"){
                val = stoi(str);
                board->insertValue(i, val);
            }else{
                board->insertValue(i, 0);
            }
        }
    }
    cout<<"----"<<endl;
    board->printBoard();
    cout<<"----"<<endl;
    board->getAdjBoard();
    cout<<"----"<<endl;
    board->printAdjBoard();
    cout<<"----"<<endl;
    board->printBoard();
    return 0;
}
