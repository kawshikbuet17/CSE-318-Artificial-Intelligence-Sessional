#define FileIO \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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
    int capture;

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
        capture = 0;
    }

    void printGameState(){
        cout<<"\t1\t2\t3\t4\t5\t6\t"<<endl;
        cout<<"---\t---\t---\t---\t---\t---\t---\t"<<endl;
        cout<<"\t";
        for(int i=MANCALA_1-1; i>=MANCALA_0+1; i--){
            cout<<bins[i]<<"\t";
        }
        cout<<"\t"<<"-->P2\n";
        cout<<bins[MANCALA_1]<<"\t\t\t\t\t\t\t"<<bins[MANCALA_0];
        cout<<endl;
        cout<<"\t";
        for(int i=0; i<MANCALA_0; i++){
             cout<<bins[i]<<"\t";
        }

        cout<<"\t"<<"-->P1"<<endl;
        cout<<"---\t---\t---\t---\t---\t---\t---\t"<<endl;
        cout<<"\t6\t5\t4\t3\t2\t1\t"<<endl;
        cout<<endl;
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
                        capture = bins[tempIndex] + bins[12-tempIndex] ;
                        bins[MANCALA_0] += bins[tempIndex] + bins[12-tempIndex] ;
                        bins[12-tempIndex]=0;
                        bins[tempIndex]=0;
                    }
                    else{
                        capture=0;
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
                cout<<"no stones in bin "<<input<<" ,discarding input"<<endl;
                return;
            }
            distributeStones(MANCALA_0, input, val);
            int tempIndex=(input+val)%NUM_OF_BINS;
            if(bins[tempIndex]==1){
                if(tempIndex>=7 and tempIndex<=12){
                    if(bins[12-tempIndex] != 0){
                        capture = bins[tempIndex] + bins[12-tempIndex] ;
                        bins[MANCALA_1] += bins[tempIndex] + bins[12-tempIndex] ;
                        bins[12-tempIndex]=0;
                        bins[tempIndex]=0;
                    }
                    else{
                        capture=0;
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

    int getWinner(){
        cout<<"Player 1 : "<<bins[6]<<endl;
        cout<<"Player 2 : "<<bins[13]<<endl;
        if(bins[6]>bins[13]){
            cout<<"Player 1 is winner"<<endl;
            return 1;
        }
        else if(bins[6]<bins[13]){
            cout<<"Player 2 is winner"<<endl;
            return 2;
        }
        else{
            cout<<"Match Tied"<<endl;
            return 3;
        }
    }

    int getWinnerInt(){
        if(bins[6]>bins[13]){
            return 1;
        }
        else if(bins[6]<bins[13]){
            return 2;
        }
        else{
            return 3;
        }
    }

    int heuristic1(){
        return bins[13]-bins[6];
    }

    int heuristic2(){
        return W1*heuristic1() + W2*heuristic1();
    }

    int heuristic3(int addMoves){
        return heuristic2()+W3*(addMoves>0);
    }

    int heuristic4(int addMoves){
        return heuristic2()+1*addMoves;
    }

    int heuristic5(int addMoves){
        return W1*heuristic1()+W2*(addMoves>0);
    }

    int heuristic6(int capt){
        return heuristic1() + W3*capt;
    }

    int evalHeuristic(int heuristicNo, int turn, int addMoves, int capt){
        if(heuristicNo==1){
            return heuristic1();
        }
        else if(heuristicNo==2){
            return heuristic2();
        }
        else if(heuristicNo==3){
            return heuristic3(addMoves);
        }
        else if(heuristicNo==4){
            return heuristic4(addMoves);
        }
        else if(heuristicNo==5){
            return heuristic5(addMoves);
        }
        else if(heuristicNo==6){
            return heuristic6(capt);
        }
        else{
            return heuristic1();
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

    pair<int,int> minimaxAlgorithm(int depth, int turn, int alpha, int beta, int addMoves, int capt, int heuristicNo){
        if(depth==0){
            return make_pair(evalHeuristic(heuristicNo, turn, addMoves, capt), 1);
        }
        if(gameOver==true){
            return make_pair(evalHeuristic(heuristicNo, turn, addMoves, capt), 1);
        }
        int maxEva;
        int minEva;
        int eva;
        int index = -1;
        if(turn){
            maxEva = -INF;
            vector<int>tmp = {7,8,9,10,11,12};
            shuffle(tmp.begin(), tmp.end(), rng);
            for(int i:tmp){
                if(bins[i]==0){
                    continue;
                }
                vector<int> b = bins;
                int turnBackup = this->turn;
                bool gameOverBackup = this->gameOver;
                int additionalMoveBackup = this->additionalMove;
                int captureBackup = this->capture;
                chooseBin(i);
                eva = minimaxAlgorithm(depth-1, this->turn, alpha, beta, this->additionalMove, this->capture, heuristicNo).first;
                if(eva>=maxEva){
                    maxEva = eva;
                    index=i;
                }
                bins = b;
                this->turn = turnBackup;
                this->gameOver = gameOverBackup;
                this->additionalMove = additionalMoveBackup;
                this->capture = captureBackup;
                alpha = max(alpha, maxEva);
                if(beta<=alpha){
                    break;
                }
            }
            return make_pair(maxEva, index);
        }
        else{
            minEva = INF;
            vector<int>tmp = {0,1,2,3,4,5};
            shuffle(tmp.begin(), tmp.end(), rng);
            for(int i:tmp){
                if(bins[i]==0){
                    continue;
                }
                vector<int> b = bins;
                int turnBackup = this->turn;
                bool gameOverBackup = this->gameOver;
                int additionalMoveBackup = this->additionalMove;
                int captureBackup = this->capture;
                chooseBin(i);
                eva = minimaxAlgorithm(depth-1, this->turn, alpha, beta, this->additionalMove, this->capture, heuristicNo).first;
                if(eva<=minEva){
                    minEva=eva;
                    index=i;
                }

                bins = b;
                this->turn = turnBackup;
                this->gameOver = gameOverBackup;
                this->additionalMove = additionalMoveBackup;
                this->capture = captureBackup;
                beta = min(minEva, beta);
                if(beta<=alpha){
                    break;
                }
            }
            return make_pair(minEva,index);
        }
    }
};


int gamePlay(bool csv, int choice, int heu_p1, int heu_p2, int depth_p1, int depth_p2){
    Mancala *mancala = new Mancala();
    if(!csv){
        mancala->printGameState();
    }

    int input;
    while(mancala->gameOver==false){
        if(!csv){
            cout<<"Turn : "<<mancala->turn+1<<endl;
        }

        if(mancala->turn==0){
            if(choice==1){
                int heuristic = heu_p1;
                int index = mancala->minimaxAlgorithm(depth_p1, mancala->turn, -INF, INF, 0, 0, heuristic).second;

                if(!csv){
                    cout<<"Bin : "<<7-(index+1)<<endl;
                }

                mancala->chooseBin(index);

                if(!csv){
                    mancala->printGameState();
                }

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
            int heuristic = heu_p2;
            int index = mancala->minimaxAlgorithm(depth_p2, mancala->turn, -INF, INF, 0, 0, heuristic).second;
            if(!csv){
                cout<<"Bin : "<<13-index<<endl;
            }

            mancala->chooseBin(index);
            if(!csv){
                mancala->printGameState();
            }
            mancala->gameOver = mancala->rowEmpty();
        }
    }
    int winner ;
    if(!csv){
        winner = mancala->getWinner();
        mancala->printGameState();
        cout<<"GAME OVER"<<endl;
    }else{
        winner = mancala->getWinnerInt();
    }
    return winner;
}

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

    int csv = 0;
    if(csv){
        cout<<"Depth,P1_Heu,P2_Heu,P1_Win,P2_Win,Draw"<<endl;
        for(int m=1; m<7; m++){
            for(int i=1; i<7; i++){
                for(int j=1; j<7; j++){
                    int cnt_p1_win = 0;
                    int cnt_p2_win = 0;
                    int draw = 0;
                    for(int k=0; k<100; k++){
                        int ret = gamePlay(csv, choice, i, j, m, m);
                        if(ret==1){
                            cnt_p1_win++;
                        }
                        else if(ret==2){
                            cnt_p2_win++;
                        }
                        else{
                            draw++;
                        }
                    }
                    cout<<m<<","<<i<<","<<j<<","<<cnt_p1_win<<","<<cnt_p2_win<<","<<draw<<endl;
                }
            }
            cout<<endl;
        }
    }
    else{
        int heu1 = 1;
        int heu2 = 3;
        int depth1 = 5;
        int depth2 = 6;
        gamePlay(csv, choice, heu1, heu2, depth1, depth2);
    }
    return 0;
}

