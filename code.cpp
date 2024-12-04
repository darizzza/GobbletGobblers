#include <bits/stdc++.h>
#include <graphics.h>
#include <windows.h>

using namespace std;

struct piesa{
    int player;
    int dimensiune;
    bool folosit;
};

/*
struct tabla{
    int player;
    piesa actuala;
    piesa piesaAnterioara==NULL;
    piesa piesaAnterioara==NULL;
};
*/


tabla T[3][3];  ///TABLA DE JOC
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
        T[i][j].player=T[i][j].dimensiune=T[i][j].folosit=0;
}


///Cazurile de castig
bool Win(){
    if(T[0][0].player==T[0][1].player && T[0][0].player==T[0][2].player && T[0][0].dimensiune){winner=T[0][0].player; return 1;}
    if(T[1][0].player==T[1][1].player && T[1][0].player==T[1][2].player && T[1][1].dimensiune){winner=T[1][0].player; return 1;}
    if(T[2][0].player==T[2][1].player && T[2][0].player==T[2][2].player && T[2][1].dimensiune){winner=T[2][0].player; return 1;}
    if(T[0][0].player==T[1][0].player && T[0][0].player==T[2][0].player && T[2][0].dimensiune){winner=T[0][0].player; return 1;}
    if(T[0][1].player==T[1][1].player && T[0][1].player==T[2][1].player && T[2][1].dimensiune){winner=T[0][1].player; return 1;}
    if(T[0][2].player==T[1][2].player && T[0][2].player==T[2][2].player && T[2][2].dimensiune){winner=T[0][2].player; return 1;}
    if(T[0][0].player==T[1][1].player && T[1][1].player==T[2][2].player && T[2][2].dimensiune){winner=T[0][0].player; return 1;}
    if(T[0][2].player==T[1][1].player && T[1][1].player==T[2][0].player && T[2][0].dimensiune){winner=T[0][2].player; return 1;}
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
            if(T[i][j].player==1){
                //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),12);///AFISEAZA ROSU-PLAYER1
                cout<<T[i][j].dimensiune<<" ";
            }
            else if(T[i][j].player==2){
                //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),34);///AFISEAZA ALBASTRU-PLAYER2
                cout<<T[i][j].dimensiune<<" ";
            }
                else{
                    //SetConsoleTextAttribute(GetStHandle(STD_OUTPUT_HANDLE),37);///AFISEAZA ALB
                    cout<<T[i][j].dimensiune<<" ";
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
            if(P1[nrPiesa].dimensiune>T[linie][coloana].dimensiune && !P1[nrPiesa].folosit){
                ok=1;
                T[linie][coloana]=P1[nrPiesa];
                P1[nrPiesa].folosit=1;
            }
            else{
                cout <<"Mutare invalida. Introdu din nou piesa (0-5), linia(0,2) si coloana(0,2):";
                CitireDate();
            }
        }
         else{
            if(P2[nrPiesa].dimensiune>T[linie][coloana].dimensiune && !P2[nrPiesa].folosit){
                ok=1;
                T[linie][coloana]=P2[nrPiesa];
                P2[nrPiesa].folosit=1;
            }
            else{
                cout <<"Mutare invalida. Introdu din nou piesa (0-5), linia(0,2) si coloana(0,2):";
                CitireDate();
            }
        }
    }
}

void Playing(){
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
    Playing();
    return 0;
}
