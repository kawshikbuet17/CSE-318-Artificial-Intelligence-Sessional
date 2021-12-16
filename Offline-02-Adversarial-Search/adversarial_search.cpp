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

    Mancala(){
        bins.resize(NUM_OF_BINS);
        for(int i=0; i<NUM_OF_BINS; i++){
            bins[i] = INITIAL_STONES;
        }
        bins[MANCALA_0] = 0;
        bins[MANCALA_1] = 0;
        turn = 0;
        gameOver = false;

    }
    void printGameState(){
        cout<<"___\t___\t___\t___\t___\t___\t___\t___\t___\t___\t\n"<<endl;
        // cout<<bins[MANCALA_1]<<"@"<<MANCALA_1<<"\t";
        cout<<bins[MANCALA_1]<<"\t";
        for(int i=MANCALA_1-1; i>=MANCALA_0+1; i--){
            // cout<<bins[i]<<"@"<<i<<"\t";
            cout<<bins[i]<<"\t";
        }
        cout<<"\t"<<"-->P1";
        cout<<"\n"<<endl;
        cout<<"\t";
        for(int i=0; i<MANCALA_0; i++){
            // cout<<bins[i]<<"@"<<i<<"\t";
             cout<<bins[i]<<"\t";
        }
        // cout<<bins[MANCALA_0]<<"@"<<MANCALA_0;
        cout<<bins[MANCALA_0];
        cout<<"\t"<<"-->P0"<<endl;
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
            cout<<"Player 0 is winner"<<endl;
        }
        else{
            cout<<"Player 1 is winner"<<endl;
        }

        cout<<"Player 0 : "<<bins[6]<<endl;
        cout<<"Player 1 : "<<bins[13]<<endl;

    }

    int heuristic1(int turn){
        if(turn==0){
            return bins[6]-bins[13];
        }
        else{
            return bins[13]-bins[6];
        }
    }

    int heuristic2(int turn){
        return W1*heuristic1(turn) + W2*heuristic1(turn);
    }

    int heuristic3(int turn){
        return heuristic2(turn)+W3;
    }

    int evalHeuristic(int heuristicNo, int turn){
        if(heuristicNo==1){
            return heuristic1(turn);
        }
        else if(heuristicNo==2){
            return heuristic2(turn);
        }
        else if(heuristicNo==3){
            return heuristic3(turn);
        }
    }

    vector<int> backupBins(vector<int> v){
        vector<int>backup;
        backup.resize(NUM_OF_BINS);
        for(int i=0; i<NUM_OF_BINS; i++){
            backup[i] = v[i];
        }
        return backup;
    }

    pair<int,int> minimaxAlgorithm(int depth, int turn, int alpha, int beta){
        if(depth==0){
            return make_pair(evalHeuristic(1, turn), 1);
        }
        if(gameOver==true){
            return make_pair(evalHeuristic(1, turn), 1);
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
                chooseBin(i);
                eva = minimaxAlgorithm(depth-1, this->turn, alpha, beta).first;
                if(eva>maxEva){
                    maxEva = eva;
                    index=i;
                }
                bins = b;
                this->turn = turnBackup;
                this->gameOver = gameOverBackup;

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
                chooseBin(i);
                eva = minimaxAlgorithm(depth-1, this->turn, alpha, beta).first;
                if(eva<minEva){
                    minEva=eva;
                    index=i;
                }

                bins = b;
                this->turn = turnBackup;
                this->gameOver = gameOverBackup;
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
    Mancala *mancala = new Mancala();
    mancala->printGameState();
    int input;
    while(mancala->gameOver==false){
        cout<<"Turn : "<<mancala->turn<<endl;

        if(mancala->turn==0){
            cin>>input;
            cout<<"Bin : "<<input<<endl;
            mancala->chooseBin(input-1);
            mancala->printGameState();
            mancala->gameOver = mancala->rowEmpty();
        }
        else{
            ///Play with computer

            int index = mancala->minimaxAlgorithm(7, mancala->turn, -INF, INF).second;
            cout<<"Bin : "<<index<<endl;
            //cout<<"Printing current BInS"<<endl;
            //cout<<"TURN___"<<mancala->turn<<endl;
            //mancala->printGameState();
            //cout<<"Printing current BInE"<<endl;
            mancala->chooseBin(index);
            mancala->printGameState();
            mancala->gameOver = mancala->rowEmpty();

            //Play with player
            //cin>>input;
            //cout<<"Bin : "<<input<<endl;
            //mancala->chooseBin(input);
            //mancala->printGameState();
            //mancala->gameOver = mancala->rowEmpty();
        }
    }
    mancala->getWinner();
    mancala->printGameState();
    cout<<"GAME OVER"<<endl;
    return 0;
}

///turn 0, player
///turn 1, PC
