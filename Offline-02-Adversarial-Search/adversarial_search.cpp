#define FileIO \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#include<bits/stdc++.h>
using namespace std;

#define INF 100000
#define NUM_OF_BINS 14
#define INITIAL_STONES 4
#define MANCALA_0 6
#define MANCALA_1 13
#define W1 10
#define W2 15
#define W3 20

class Mancala{
    public:
    vector<int>bins;
    int turn;
    bool gameOver;
    int additionalMove;

    Mancala(){
        bins.resize(NUM_OF_BINS);
        for(int i=0; i<NUM_OF_BINS; i++){
            bins[i] = INITIAL_STONES;
        }
        bins[MANCALA_0] = 0;
        bins[MANCALA_1] = 0;
        turn = 0;
        gameOver = false;
        additionalMove = 0;
    }
    void printGameState(){
        cout<<"___\t___\t___\t___\t___\t___\t___\t___\t___\t___\t\n"<<endl;
        // cout<<bins[MANCALA_1]<<"@"<<MANCALA_1<<"\t";
        cout<<bins[MANCALA_1]<<"\t";
        for(int i=MANCALA_1-1; i>=MANCALA_0+1; i--){
            // cout<<bins[i]<<"@"<<i<<"\t";
            cout<<bins[i]<<"\t";
        }
        cout<<"\t"<<"-->P2";
        cout<<"\n"<<endl;
        cout<<"\t";
        for(int i=0; i<MANCALA_0; i++){
            // cout<<bins[i]<<"@"<<i<<"\t";
             cout<<bins[i]<<"\t";
        }
        // cout<<bins[MANCALA_0]<<"@"<<MANCALA_0;
        cout<<bins[MANCALA_0];
        cout<<"\t"<<"-->P1"<<endl;
        cout<<"___\t___\t___\t___\t___\t___\t___\t___\t___\t___\t"<<endl;
    }

    void chooseBin(int input){
        if(turn==0){
            int val = bins[input];
            if(val==0){
                cout<<"no stones in bin "<<val<<" ,discarding input"<<endl;
                return;
            }
            distributeStones(MANCALA_1, input, val);
            int tempIndex=(input+val)%NUM_OF_BINS;
            if(bins[tempIndex]==1){
                if(tempIndex>=0 and tempIndex<=5){
                    if(bins[12-tempIndex] != 0){
                        bins[MANCALA_0] += bins[tempIndex] + bins[12-tempIndex] ;
                        bins[12-tempIndex]=0;
                        bins[tempIndex]=0;
                    }
                }
            }


            if(tempIndex != MANCALA_0){
                turn = 1-turn;
                additionalMove=0;
            }
            else{
                additionalMove++;
            }
        }

        else if(turn==1){
            int val = bins[input];
            if(val==0){
                cout<<"no stones in bin "<<val<<" ,discarding input"<<endl;
                return;
            }
            distributeStones(MANCALA_0, input, val);
            int tempIndex=(input+val)%NUM_OF_BINS;
            if(bins[tempIndex]==1){
                if(tempIndex>=7 and tempIndex<=12){
                    if(bins[12-tempIndex] != 0){
                        bins[MANCALA_1] += bins[tempIndex] + bins[12-tempIndex] ;
                        bins[12-tempIndex]=0;
                        bins[tempIndex]=0;
                    }
                }
            }

            if(tempIndex != MANCALA_1){
                turn = 1-turn;
                additionalMove=0;
            }
            else{
                additionalMove++;
            }
        }
    }

    void distributeStones(int avoid, int input, int& val){
        bins[input] = 0;
        for(int i=1; i<=val; i++){
            if((input+i)%NUM_OF_BINS != avoid){
                bins[(input+i)%NUM_OF_BINS]++;
                //cout<<(input+i)%NUM_OF_BINS<<" ";
            }
            else{
                val++;
            }
        }
        //cout<<endl;
    }

    bool rowEmpty(){
        int sum_0 = 0;
        int sum_1 = 0;
        bool boolean = false;
        for(int i=0; i<6; i++){
            sum_0 += bins[i];
        }

        for(int i=7; i<13; i++){
            sum_1 += bins[i];
        }

        if(sum_0==0){
            bins[13] += sum_1;
            for(int i=7; i<13; i++){
                bins[i] = 0;
            }
            boolean=true;
        }
        else if(sum_1==0){
            bins[6] += sum_0;
            for(int i=0; i<6; i++){
                bins[i] = 0;
            }
            boolean=true;
        }
        return boolean;
    }

    void getWinner(){
        if(bins[6]>bins[13]){
            cout<<"Player 1 is winner"<<endl;
        }
        else{
            cout<<"Player 2 is winner"<<endl;
        }

        cout<<"Player 1 : "<<bins[6]<<endl;
        cout<<"Player 2 : "<<bins[13]<<endl;

    }

    int heuristic1(int turn){
        return bins[13]-bins[6];
    }

    int heuristic2(int turn){
        return W1*heuristic1(turn) + W2*heuristic1(turn);
    }

    int heuristic3(int turn, int addMoves){
        return heuristic2(turn)+W3*(addMoves>0);
    }

    int heuristic4(int turn, int addMoves){
        return heuristic2(turn)+W3*addMoves;
    }

    int evalHeuristic(int heuristicNo, int turn, int addMoves){
        if(heuristicNo==1){
            return heuristic1(turn);
        }
        else if(heuristicNo==2){
            return heuristic2(turn);
        }
        else if(heuristicNo==3){
            // if(addMoves>0){
            //     cout<<"ADDMOVES: "<<addMoves<<endl;
            // }
            return heuristic3(turn, addMoves);
        }
        else if(heuristicNo==4){
            return heuristic4(turn, addMoves);
        }
        else{
            return heuristic1(turn);
        };
    }

    vector<int> backupBins(vector<int> v){
        vector<int>backup;
        backup.resize(NUM_OF_BINS);
        for(int i=0; i<NUM_OF_BINS; i++){
            backup[i] = v[i];
        }
        return backup;
    }

    pair<int,int> minimaxAlgorithm(int depth, int turn, int alpha, int beta, int addMoves, int heuristicNo){
        if(depth==0){
            return make_pair(evalHeuristic(heuristicNo, turn, addMoves), 1);
        }
        if(gameOver==true){
            return make_pair(evalHeuristic(heuristicNo, turn, addMoves), 1);
        }
        int maxEva;
        int minEva;
        int eva;
        int index = -1;
        if(turn){
            maxEva = -INF;
            for(int i=7; i<13; i++){
                if(bins[i]==0){
                    continue;
                }
                vector<int> b = bins;
                int turnBackup = this->turn;
                bool gameOverBackup = this->gameOver;
                int additionalMoveBackup = this->additionalMove;
                chooseBin(i);
                eva = minimaxAlgorithm(depth-1, this->turn, alpha, beta, this->additionalMove, heuristicNo).first;
                if(eva>=maxEva){
                    maxEva = eva;
                    index=i;
                }
                bins = b;
                this->turn = turnBackup;
                this->gameOver = gameOverBackup;
                this->additionalMove = additionalMoveBackup;

                alpha = max(alpha, maxEva);
                if(beta<=alpha){
                    break;
                }
            }
            return make_pair(maxEva, index);
        }
        else{
            minEva = INF;
            for(int i=0; i<6; i++){
                if(bins[i]==0){
                    continue;
                }
                vector<int> b = bins;
                int turnBackup = this->turn;
                bool gameOverBackup = this->gameOver;
                int additionalMoveBackup = this->additionalMove;
                chooseBin(i);
                eva = minimaxAlgorithm(depth-1, this->turn, alpha, beta, this->additionalMove, heuristicNo).first;
                if(eva<=minEva){
                    minEva=eva;
                    index=i;
                }

                bins = b;
                this->turn = turnBackup;
                this->gameOver = gameOverBackup;
                this->additionalMove = additionalMoveBackup;
                beta = min(minEva, beta);
                if(beta<=alpha){
                    break;
                }
            }
            return make_pair(minEva,index);
        }
    }
};


int main(){
    FileIO;
    int choice;
    cout<<"AI vs AI : Press 1"<<endl;
    cout<<"Player vs AI : Press 2"<<endl;
    cin>>choice;
    if(choice==1){
        cout<<"Playing -> AI vs AI"<<endl;
    }
    else{
        cout<<"Playing -> Player vs AI"<<endl;
    }

    Mancala *mancala = new Mancala();
    mancala->printGameState();
    int input;
    while(mancala->gameOver==false){
        cout<<"Turn : "<<mancala->turn+1<<endl;

        if(mancala->turn==0){
            if(choice==1){
                int index = mancala->minimaxAlgorithm(5, mancala->turn, -INF, INF, 0, 1).second;
                cout<<"Bin : "<<7-(index+1)<<endl;
                mancala->chooseBin(index);
                mancala->printGameState();
                mancala->gameOver = mancala->rowEmpty();
            }
            else if(choice==2){
                cin>>input;
                cout<<"Bin : "<<input<<endl;
                input=7-input;
                mancala->chooseBin(input-1);
                mancala->printGameState();
                mancala->gameOver = mancala->rowEmpty();
            }
        }
        else{
            int index = mancala->minimaxAlgorithm(4, mancala->turn, -INF, INF, 0, 2).second;
            cout<<"Bin : "<<13-index<<endl;
            mancala->chooseBin(index);
            mancala->printGameState();
            mancala->gameOver = mancala->rowEmpty();
        }
    }
    mancala->getWinner();
    mancala->printGameState();
    cout<<"GAME OVER"<<endl;
    return 0;
}

