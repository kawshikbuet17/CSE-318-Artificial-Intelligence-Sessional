#define FileIO \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#include<bits/stdc++.h>
using namespace std;

class Board{
    int k;
    vector<vector<int>> square;
    bool visited;
    int gn;
    int hn;
    Board* parent;
    public:
    Board(int k){
        this->k=k;
        square.resize(k);
        visited=false;
        parent = NULL;
    }


    void setk(int k){
        this->k = k;
    }

    int getk(){
        return k;
    }

    void setParent(Board* b){
        parent = b;
    }

    Board* getParent(){
        return parent;
    }

    void setGn(int gn){
        this->gn = gn;
    }

    void setHn(int hn){
        this->hn = hn;
    }

    int getGn(){
        return gn;
    }

    int getHn(){
        return hn;
    }

    void insertValue(int row, int val){
        square[row].push_back(val);
    }

    vector<vector<int>> getGrid(){
        return square;
    }

    int getCorrectRow(int val){
        return (val-1)/k;
    }

    int getCorrectColumn(int val){
        return (val-1)%k;
    }

    int getInverseCount(vector<int> arr){
        int inv_count = 0;
        for (int i = 0; i < k*k - 1; i++)
            for (int j = i+1; j < k*k; j++)
                if (arr[j] && arr[i] &&  arr[i] > arr[j])
                    inv_count++;
        cout<<"INV Count = "<<inv_count<<endl;
        return inv_count;
    }

    bool isSolvable()
    {
        vector<int> arr;
        for(int i=0; i<k; i++){
            for(int j=0; j<k; j++){
                arr.push_back(square[i][j]);
            }
        }
        // Count inversions in given 8 puzzle
        int invCount = getInverseCount(arr);
        return (invCount%2 == 0);
    }

    int manhattan(){
        int manhattanDist=0;
        for(int i=0; i<k; i++){
            for(int j=0; j<k; j++){
                if(square[i][j] != 0){
                    manhattanDist+= abs(getCorrectRow(square[i][j])-i)+abs(getCorrectColumn(square[i][j])-j);
                }
            }
        }
        return manhattanDist;
    }

    int hammingDistance(){
        int hammingDistance=0;
        for(int i=0; i<k; i++){
            for(int j=0; j<k; j++){
                if(square[i][j] != 0){
                    int should_be = i * k + j + 1;
                    hammingDistance += (should_be != square[i][j]);
                }
            }
        }
        return hammingDistance;
    }

    int linearConflict(){
        int count = 0;
        for(int i=0; i<k; i++){
            for(int j=0; j<k-1; j++){
                for(int l=j+1; l<k; l++){
                    if(square[i][j]!=0 and square[i][l]!=0 and square[i][j]>square[i][l] and getCorrectRow(square[i][j])==i and getCorrectRow(square[i][l])==i){
                        count++;
                    }
                }
            }
        }
        return count;
    }

    int linearConflictHeuristic(){
        return manhattan()+2*linearConflict();
    }

    void printBoard(){
        cout<<"----"<<endl;
        for(int i=0; i<square.size(); i++){
            for(int j=0; j<square[i].size(); j++){
                if(square[i][j]==0){
                    cout<<"*"<<" ";
                }
                else{
                    cout<<square[i][j]<<" ";
                }
            }
            cout<<endl;
        }
        cout<<"----"<<endl;
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

    bool operator==(Board *b){
        bool yes=true;
        vector<vector<int>> sq = b->getGrid();
        for(int i=0; i<square.size(); i++){
            for(int j=0; j<square[i].size(); j++){
                if(sq[i][j] != square[i][j]){
                    yes=false;
                    break;
                }
            }
        }
        return yes;
    }
};

struct Compare
{
    bool operator()(Board *a, Board *b){
        int cost1 = a->getGn()+a->getHn();
        int cost2 = b->getGn()+b->getHn();
        return cost1>cost2;
    }
};


class Graph {
    Board *board;
    int k;
    public:

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    bool isOutSide(int x, int y){
        if(x < 0 or x >= k or y<0 or y>=k ) return true;
        return false;
    }

    Graph(int k){
        board = new Board(k);
        this->k = k;
    }

    void insertValue(int row, int val){
        board->insertValue(row, val);
    }

    void printBoard(){
        board->printBoard();
    }

    bool isSolvable(){
        return board->isSolvable();
    }

    void A_Star_Search(int heuristic){
        cout<<"Performing A* Search"<<endl;
        board->setGn(0);
        priority_queue<Board*, vector<Board*>, Compare>pq;
        pq.push(board);
        int num_of_move=0;
        unordered_set<Board*> visited;

        while(!pq.empty()){
            Board *topBoard = pq.top();
            topBoard->printBoard();
            pq.pop();
            visited.insert(topBoard);

            vector<vector<int>> goal;
            int cnt=1;
            goal.resize(k);
            for(int i=0; i<k; i++){
                for(int j=0; j<k; j++){
                    goal[i].push_back(cnt);
                    cnt++;
                }
            }
            goal[k-1][k-1] = 0;

            if(topBoard->getGrid() == goal){
                cout<<"Done"<<endl;
                cout<<"Hamming Distance: "<<topBoard->hammingDistance()<<endl;
                cout<<"Manhattan Distance: "<<topBoard->manhattan()<<endl;
                cout<<"Linear Conflict: "<<topBoard->linearConflict()<<endl;
                cout<<"Num of Move: "<<num_of_move<<endl;
                topBoard->printBoard();
                break;
            }
            num_of_move++;

            int zeroX = -1;
            int zeroY = -1;
            for(int i=0; i<k; i++){
                for(int j=0; j<k; j++){
                    if(topBoard->getGrid()[i][j]==0){
                        zeroX = i;
                        zeroY = j;
                        break;
                    }
                }
            }

            for(int i=0; i<4; i++){

                int new_x = zeroX+dx[i], new_y = zeroY+dy[i];
                if(isOutSide(new_x, new_y)) continue;

                Board *newBoard = new Board(k);
                for(int i=0; i<k; i++){
                    for(int j=0; j<k; j++){
                        newBoard->insertValue(i, topBoard->getGrid()[i][j]);
                    }
                }
                newBoard->swapVal(zeroX, new_x, zeroY, new_y );
                newBoard->setParent(topBoard);
                newBoard->setGn(newBoard->getParent()->getGn()+1);
                if(heuristic==1){
                    newBoard->setHn(newBoard->hammingDistance());
                }
                else if(heuristic==2){
                    newBoard->setHn(newBoard->manhattan());
                }
                else if(heuristic==3){
                    newBoard->setHn(newBoard->linearConflictHeuristic());
                }

                if(visited.find(newBoard)==visited.end()){
                    pq.push(newBoard);
                }
            }
        }
    }
};


int main(){
    FileIO;

    int k;
    cin>>k;
    Graph *graph = new Graph(k);
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            string str;
            int val;
            cin>>str;
            if(str != "*"){
                val = stoi(str);
                graph->insertValue(i, val);
            }else{
                graph->insertValue(i, 0);
            }
        }
    }
    graph->printBoard();
    if(graph->isSolvable()){
        cout<<"Puzzle is Solvable"<<endl;
        graph->A_Star_Search(1);
        graph->A_Star_Search(2);
        graph->A_Star_Search(3);
    }else{
        cout<<"Puzzle is NOT Solvable"<<endl;
    }
    
    return 0;
}
