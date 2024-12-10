#include <bits/stdc++.h>
#include <fstream>
#include <graphics.h>
#include <windows.h>

using namespace std;
ifstream fin("joc.in");
ofstream fout("joc.ou");


struct piesa{
    int player;
    int dimensiune;///1-mic  2-mediu   3-mare
    bool folosit;
};


struct cell{
    int ctPiese;
    piesa *stiva;
};



cell T[3][3];  ///TABLA DE JOC
piesa P1[6],P2[6]; ///Cei 2 PLAYERI
int winner,nrPiesa,linie,coloana;


void Configurare(){
    ///Configurare playeri-piese
    int i,j;
    for(i=0;i<6;i++){
        P1[i].player=1;
        P2[i].player=2;
        P1[i].folosit=P2[i].folosit=0;
    }

    P1[0].dimensiune=P1[1].dimensiune=P2[0].dimensiune=P2[1].dimensiune=1;///PIESELE MICI
    P1[2].dimensiune=P1[3].dimensiune=P2[2].dimensiune=P2[3].dimensiune=2;///PIESELE MIJLOCII
    P1[4].dimensiune=P1[5].dimensiune=P2[4].dimensiune=P2[5].dimensiune=3;///PIESELE MARI

    ///Configurare tabla de joc
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            {T[i][j].ctPiese=0;
            T[i][j].stiva=new piesa[3];
            }
}


///Cazurile de castig
bool Win(){
    int i;
    ///LINIE
    for(i=0;i<3;i++){
        if(T[i][0].ctPiese && T[i][1].ctPiese && T[i][2].ctPiese && T[i][0].stiva[T[i][0].ctPiese-1].player == T[i][1].stiva[T[i][1].ctPiese-1].player &&
            T[i][0].stiva[T[i][0].ctPiese-1].player == T[i][2].stiva[T[i][2].ctPiese-1].player)
        {winner=T[i][0].stiva[T[i][0].ctPiese-1].player;
            return 1;
        }
    }

    ///COLOANA
    for(i=0;i<3;i++){
        if(T[0][i].ctPiese && T[1][i].ctPiese && T[2][i].ctPiese && T[0][i].stiva[T[0][i].ctPiese-1].player == T[1][i].stiva[T[1][i].ctPiese-1].player &&
            T[0][i].stiva[T[0][i].ctPiese-1].player == T[2][i].stiva[T[2][i].ctPiese-1].player)
        {winner=T[0][i].stiva[T[0][i].ctPiese-1].player;
            return 1;
        }
    }

    ///DIAGONALE
    if(T[0][0].ctPiese && T[1][1].ctPiese && T[2][2].ctPiese &&T[0][0].stiva[T[0][0].ctPiese-1].player==T[1][1].stiva[T[1][1].ctPiese-1].player &&
       T[0][0].stiva[T[0][0].ctPiese-1].player==T[2][2].stiva[T[2][2].ctPiese-1].player)
        {winner=T[0][0].stiva[T[0][0].ctPiese-1].player;
            return 1;
        }
    if(T[0][2].ctPiese && T[1][1].ctPiese && T[2][0].ctPiese && T[0][2].stiva[T[0][2].ctPiese-1].player==T[1][1].stiva[T[1][1].ctPiese-1].player &&
       T[1][1].stiva[T[1][1].ctPiese-1].player==T[2][0].stiva[T[2][0].ctPiese-1].player)
        {winner=T[1][1].stiva[T[1][1].ctPiese-1].player;
            return 1;
        }

    return 0;
}

void WinnerAnnouncement(){
    //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),37);///AFISEAZA ALB
    cout<<"Castigatorul este Player "<<winner;
}

void CitireDate(){
    cin>>nrPiesa>>linie>>coloana;
    cout<<endl;
}

    ///SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),12);



void AfisareMatr(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            if(T[i][j].ctPiese){
                if(T[i][j].stiva[T[i][j].ctPiese - 1].player==1){
                    //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),12);///AFISEAZA ROSU-PLAYER1
                    cout<<"P1("<<T[i][j].stiva[T[i][j].ctPiese - 1].dimensiune<<") ";
                }
                else if(T[i][j].stiva[T[i][j].ctPiese - 1].player==2){
                    //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),34);///AFISEAZA ALBASTRU-PLAYER2
                    cout<<"P2("<<T[i][j].stiva[T[i][j].ctPiese - 1].dimensiune<<") ";
                }
            }
            else{
                    //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),37);///AFISEAZA ALB
                    cout << "  -  ";
                }
        cout<<endl;
    }
    //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),37);///AFISEAZA ALB
    cout<<endl;

}

void PlasarePiesa(int x){
    //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),37);///AFISEAZA ALB
    bool ok=0;
    while(!ok){
        if(x==1){
            if(P1[nrPiesa].dimensiune>T[linie][coloana].stiva[T[linie][coloana].ctPiese - 1].dimensiune && !P1[nrPiesa].folosit || T[linie][coloana].ctPiese == 0){
                ok=1;
                T[linie][coloana].stiva[T[linie][coloana].ctPiese] = P1[nrPiesa];
                T[linie][coloana].ctPiese++;
                P1[nrPiesa].folosit=1;
            }
            else{
                cout <<"Mutare invalida. Introdu din nou piesa (0-5), linia(0,2) si coloana(0,2):";
                CitireDate();
            }
        }
         else{
            if(P2[nrPiesa].dimensiune>T[linie][coloana].stiva[T[linie][coloana].ctPiese - 1].dimensiune && !P2[nrPiesa].folosit || T[linie][coloana].ctPiese == 0){
                ok=1;
                T[linie][coloana].stiva[T[linie][coloana].ctPiese] = P2[nrPiesa];
                T[linie][coloana].ctPiese++;
                P2[nrPiesa].folosit=1;
            }
            else{
                cout <<"Mutare invalida. Introdu din nou piesa (0-5), linia(0,2) si coloana(0,2):";
                CitireDate();
            }
        }
    }
}


///2 PLAYERI
void Playing2(){
    int ct=1;
    //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),37);///AFISEAZA ALB
    do{
        if(ct==1){//player1
            cout<<"Player 1-Scrie piesa (0-5), linia(0,2) si coloana(0,2):";
            CitireDate();
            PlasarePiesa(ct);
            ct++;
        }
        else{//player2
            cout<<"Player 2-Scrie piesa (0-5), linia(0,2) si coloana(0,2):";
            CitireDate();
            PlasarePiesa(ct);
            ct=1;
        }
        AfisareMatr();
    }while(!Win());
    WinnerAnnouncement();
}



int main()
{
    cout<<"----------GOBBLET GOBBLERS----------"<<endl<<endl<<endl;
    Configurare();
    Playing2();
    return 0;
}
