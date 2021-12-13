#define FileIO \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#include<bits/stdc++.h>
using namespace std;

#define NUM_OF_BINS 14
#define INITIAL_STONES 4
#define MANCALA_0 6
#define MANCALA_1 13

class Mancala{
    public:
    vector<int>bins;
    int turn;
    Mancala(){
        bins.resize(NUM_OF_BINS);
        for(int i=0; i<NUM_OF_BINS; i++){
            bins[i] = INITIAL_STONES;
        }
        bins[MANCALA_0] = 0;
        bins[MANCALA_1] = 0;
        turn = 0;
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
            input--;
            int val = bins[input];
            if(val==0){
                cout<<"no stones in bin "<<val<<" ,discarding input"<<endl;
            }
            bins[input] = 0;
            for(int i=1; i<=val; i++){
                if((input+i)%NUM_OF_BINS != 13){
                    bins[(input+i)%NUM_OF_BINS]++;
                }
                else{
                    val++;
                }
            }

            if(bins[(input+val)%NUM_OF_BINS]==1 and (input+val)%NUM_OF_BINS != 6 and bins[12-(input+val)%NUM_OF_BINS]!=0){
                bins[6] += bins[(input+val)%NUM_OF_BINS] + bins[12-(input+val)%NUM_OF_BINS] ;
                bins[12-(input+val)%NUM_OF_BINS]=0;
                bins[(input+val)%NUM_OF_BINS]=0;
            }

            printGameState();
            if((input+val)%NUM_OF_BINS!=6){
                turn = 1-turn;
            }
            else{
                cout<<"turn not changed"<<endl;
            }
        }

        else if(turn==1){
            input+=6;
            int val = bins[input];
            if(val==0){
                cout<<"no stones in bin "<<val<<endl;
            }
            bins[input] = 0;
            for(int i=1; i<=val; i++){
                if((input+i)%NUM_OF_BINS != 6){
                    bins[(input+i)%NUM_OF_BINS]++;
                }
                else{
                    val++;
                }
            }

            if(bins[(input+val)%NUM_OF_BINS]==1 and (input+val)%NUM_OF_BINS != 13 and bins[12-(input+val)%NUM_OF_BINS]!=0){
                bins[13] += bins[(input+val)%NUM_OF_BINS] + bins[12-(input+val)%NUM_OF_BINS];
                bins[12-(input+val)%NUM_OF_BINS]=0;
                bins[(input+val)%NUM_OF_BINS]=0;
            }

            printGameState();
            if((input+val)%NUM_OF_BINS != 13){
                turn = 1-turn;
            }
            else{
                cout<<"turn not changed"<<endl;
            }
        }

        bool done = rowEmpty();
        if(rowEmpty()){
            printGameState();
            getWinner();
        }
    }

    bool rowEmpty(){
        int sum_0 = 0;
        int sum_1 = 0;

        for(int i=0; i<6; i++){
            sum_0 += bins[i];
        }

        for(int i=7; i<12; i++){
            sum_1 += bins[i];
        }

        if(sum_0==0){
            bins[13] += sum_1;
            for(int i=7; i<12; i++){
                bins[i] = 0;
            }
            return true;
        }
        else if(sum_1==0){
            bins[6] += sum_0;
            for(int i=0; i<6; i++){
                bins[i] = 0;
            }
            return true;
        }
        return false;

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
};

int main(){
    FileIO;
    Mancala *mancala = new Mancala();
    mancala->printGameState();

    int input;
    while(1){
       
        if(mancala->rowEmpty()==false){
            cin>>input;
            if(input==0)
                break;
            cout<<"Turn : "<<mancala->turn<<endl;
            cout<<"Bin : "<<input<<endl;
            mancala->chooseBin(input);
        }
        else{
            break;
        }
    }
}
