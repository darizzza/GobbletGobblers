#include <bits/stdc++.h>

using namespace std;

struct piesa{
    int player;
    int dimensiune;///1-mic  2-mediu   3-mare
    bool peTabla;
    piesa *sub;
};

struct cell{
    int ctPiese;
    piesa *stiva;
};

cell T[3][3];  ///TABLA DE JOC
piesa P[2][6]; ///Cei 2 PLAYERI
int winner,nrPiesa,linie,coloana;
bool testOpt;


void ConfigurareJocPiese(){
    ///ConfigurareJocPiese playeri-piese-tabla
    int i,j;

    ///PIESELE JUCATORILOR IN MATRICEA P
    for(i=0;i<2;i++)
        for(j=0;j<6;j++)
            {P[i][j].player=i;
            P[i][j].peTabla=0;
            P[i][j].sub=NULL;
            }

    P[0][0].dimensiune=P[0][1].dimensiune=P[1][0].dimensiune=P[1][1].dimensiune=1;  ///Piesele mici
    P[0][2].dimensiune=P[0][3].dimensiune=P[1][2].dimensiune=P[1][3].dimensiune=2;  ///Piesele mijlocii
    P[0][4].dimensiune=P[0][5].dimensiune=P[1][4].dimensiune=P[1][5].dimensiune=3;  ///Piesele mari

    ///ConfigurareJocPiese tabla de joc
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            {T[i][j].ctPiese=0;
            T[i][j].stiva=NULL;
            }
}

void AdaugarePiesaPeTabla(int l, int c, piesa *p){
    p->sub=T[l][c].stiva;
    T[l][c].stiva=p;
    T[l][c].ctPiese++;
    p->peTabla=1;
}

void StergerePiesaPeTabla(int l,int c){
    if(T[l][c].stiva){
        piesa *deSters=T[l][c].stiva;
        T[l][c].stiva=T[l][c].stiva->sub;
        T[l][c].ctPiese--;
    }
}


///Cazurile de castig
bool WinCases(cell T[3][3]){
    int i;
    ///LINIE
    for(i=0;i<3;i++){
        if(T[i][0].ctPiese && T[i][1].ctPiese && T[i][2].ctPiese && T[i][0].stiva->player == T[i][1].stiva->player && T[i][0].stiva->player == T[i][2].stiva->player)
            {winner=T[i][0].stiva->player;return 1;}
    }

    ///COLOANA
    for(i=0;i<3;i++){
        if(T[0][i].ctPiese && T[1][i].ctPiese && T[2][i].ctPiese && T[0][i].stiva->player == T[1][i].stiva->player && T[0][i].stiva->player == T[2][i].stiva->player)
            {winner=T[0][i].stiva->player;return 1;}
    }

    ///DIAGONALE
    if(T[0][0].ctPiese && T[1][1].ctPiese && T[2][2].ctPiese &&T[0][0].stiva->player==T[1][1].stiva->player && T[0][0].stiva->player==T[2][2].stiva->player)
        {winner=T[0][0].stiva->player;return 1;}
    if(T[0][2].ctPiese && T[1][1].ctPiese && T[2][0].ctPiese && T[0][2].stiva->player==T[1][1].stiva->player && T[1][1].stiva->player==T[2][0].stiva->player)
        {winner=T[1][1].stiva->player;return 1;}

    return 0;
}

void WinnerAnnouncement(){
    cout<<"!!!!!  Castigatorul este Player "<<winner+1<<"     !!!!!"<<endl;
}

void CitireDate(int x){
    cout<<"Jucator "<<x+1<<" alege piesa (0-5), linia(0,2) si coloana (0,2): ";
    while (!(cin >> nrPiesa >> linie >> coloana)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Intrare invalida! Reintroduceti piesa (0-5), linia(0-2) si coloana (0-2): ";
    }
    cout<<endl;
}

void AfisareMatr(){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++)
            if(T[i][j].ctPiese && T[i][j].stiva){
                if(T[i][j].stiva->player==0){
                    cout<<"P1("<<T[i][j].stiva->dimensiune<<") ";
                }
                else if(T[i][j].stiva->player==1){
                    cout<<"P2("<<T[i][j].stiva->dimensiune<<") ";
                }
            }
            else{
                    cout << "  -  ";
                }
        cout<<endl;
    }
    cout<<endl;

}


void PlasarePiesa(int x){///X ESTE PLAYER-UL
    CitireDate(x);
    ///Verifica daca datele piesei si a lin+col sunt corecte
    if(nrPiesa<0 || nrPiesa>5 || linie<0 || linie>2 || coloana<0 || coloana>2 ){
        cout<<"Mutare invalida!"<<endl;
        testOpt=0;
        return;
    }

    piesa *p= &P[x][nrPiesa];
    if(p->peTabla){
        cout<<"Mutare invalida! Piesa este deja pe tabla!"<<endl;
        testOpt=0;
        return;
    }

    if(T[linie][coloana].stiva && p->dimensiune <= T[linie][coloana].stiva->dimensiune){
        cout<<"Mutare invalida! Piesa nu se poate plasa deasupra!"<<endl;
        testOpt=0;
        return;
    }
    AdaugarePiesaPeTabla(linie,coloana, &P[x][nrPiesa]);
    testOpt=1;
}


void MutarePiesa(int x){///X ESTE PLAYER-UL
    int l,c;
    cout<<"Ce piesa doriti mutata? (linie(0-2) si coloana(0-2)):   ";
    cin>>l>>c;

    if(l<0 || l>2 || c<0 || c>2) {
            cout<<"Mutare invalida!"; testOpt=0; return;
    }

    if(!T[l][c].stiva){
        cout<<"Mutare invalida! Nu exista piesa pe aceasta pozitie."<<endl;
        testOpt=0;
        return;
    }

    if(T[l][c].stiva->player!=x){
        cout<<"Mutare invalida! Nu puteti muta piesa adversarului!"<<endl;
        testOpt=0;
        return;
    }


    cout<<"Introduceti linia(0-2) si coloana(0-2):   ";
    cin>>linie>>coloana;

    if(linie<0 || linie >2 ||coloana<0 || coloana>2){
        cout<<"Mutare invalida! Pozitia de destinatie este in afara tablei!"<<endl;
        testOpt=0;
        return;
    }
    if(T[linie][coloana].stiva && T[linie][coloana].stiva->dimensiune>= T[l][c].stiva->dimensiune){
        cout<<"Mutare invalida! Piesa nu se poate plasa deasupra!"<<endl;
        testOpt=0;
        return;
    }
    if(l==linie && c==coloana){
        cout<<"Mutare invalida! Nu puteti muta piesa pe aceeasi pozitie!"<<endl;
        testOpt=0;
        return;
    }
    piesa *p=T[l][c].stiva;
    StergerePiesaPeTabla(l,c);
    AdaugarePiesaPeTabla(linie,coloana,p);
    testOpt=1;
}

void AlegereOptiune(int x){
    char optiune;
    testOpt=0;
    ///ASEZARE PE TABLA DIN RAND    SAU      MUTARE DE PE TABLA
    ///       A                                   M
    while(!testOpt){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Jucator "<<x+1<<":"<<endl;
        cout<<"ASEZI DIN SIR UN GOBBLER PE TABLA ( A )     sau      MUTI DE PE TABLA ( M ):"<<endl;
        cin>>optiune;
        if(optiune=='A' || optiune=='a') {testOpt=1; PlasarePiesa(x);}
        else if(optiune=='M' || optiune=='m') {testOpt=1; MutarePiesa(x);}
            else {cout<<"Optiune invalida!!!  Incearca din nou :("<<endl;}
    }
}

void Playing2(){
    int turnPl=0;
    do{
        AlegereOptiune(turnPl);
        AfisareMatr();
        if(WinCases(T)) break;
        turnPl=1-turnPl;
    }while(!WinCases(T));
    WinnerAnnouncement();
}



///VS CALCULATOR

vector<pair<int, int>> getValidMoves(cell T[3][3]) {
    vector<pair<int, int>> moves;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (T[i][j].ctPiese == 0) {
                moves.push_back({i, j});
            }
        }
    }
    return moves;
}

void applyMove(cell T[3][3], int player, pair<int, int> move) {
    if (T[move.first][move.second].ctPiese == 0) {
        piesa* newPiesa = new piesa();
        newPiesa->player = player;
        newPiesa->peTabla = true;
        newPiesa->dimensiune = 1;
        T[move.first][move.second].stiva = newPiesa;
        T[move.first][move.second].ctPiese++;
    }
}

int evaluate(cell T[3][3], int player) {
    if (WinCases(T)) {
        return (winner == player) ? 10 : -10;
    }
    return 0;
}

int minimax(cell T[3][3], int depth, bool isMaximizing, int player) {
    int score = evaluate(T, player);

    if (score == 10 || score == -10) return score;
    if (depth == 0) return 0;

    vector<pair<int, int>> validMoves = getValidMoves(T);

    if (isMaximizing) {
        int best = -1000;
        for (auto move : validMoves) {
            applyMove(T, player, move);
            best = max(best, minimax(T, depth - 1, false, 1 - player));
            StergerePiesaPeTabla(move.first, move.second);
        }
        return best;
    } else {
        int best = 1000;
        for (auto move : validMoves) {
            applyMove(T, 1 - player, move);
            best = min(best, minimax(T, depth - 1, true, 1 - player));
            StergerePiesaPeTabla(move.first, move.second);
        }
        return best;
    }
}

pair<int, int> findBestMove(cell T[3][3], int player) {
    int bestVal = -1000;
    pair<int, int> bestMove;

    vector<pair<int, int>> validMoves = getValidMoves(T);
    for (auto move : validMoves) {
        applyMove(T, player, move);
        int moveVal = minimax(T, 2, false, player);
        StergerePiesaPeTabla(move.first, move.second);

        if (moveVal > bestVal) {
            bestMove = move;
            bestVal = moveVal;
        }
    }
    return bestMove;
}


void Playing1(){
    int turnPl = 0;
    do {
        if (turnPl == 0) {
            AlegereOptiune(turnPl);
        } else {
            // AI move
            pair<int, int> bestMove = findBestMove(T, turnPl);
            applyMove(T, turnPl, bestMove);
            cout << "AI a mutat la " << bestMove.first << " " << bestMove.second << endl;
        }
        AfisareMatr();
        if (WinCases(T)) break;
        turnPl = 1 - turnPl;
    } while (!WinCases(T));
    WinnerAnnouncement();
}

void Meniu(){
    int optiune;
    cout<<"Alege optiune:"<<endl;
    cout<<"1. SINGLE PLAYER "<<endl;
    cout<<"2. MULTIPLAYER "<<endl;
    cout<<"3. EXIT "<<endl;
    cout<<endl<<endl;
    cout<<"Alegeti optiunea (1 / 2 / 3): ";
    cin>>optiune;
    if(optiune==1)Playing1();
    else if(optiune==2)Playing2();
        else {cout<<"PA!";}
}
int main()
{
    srand(time(0));
    cout<<"----------GOBBLET GOBBLERS----------"<<endl<<endl<<endl;
    ConfigurareJocPiese();
    Meniu();
    return 0;
}
