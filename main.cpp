//POP 2019-12-09 projekt 1 Ostrowski Michal EIT 1 179941 Code::Blocks 17.12 GCC-6.3.0-1
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

//Definicje stalych do obslugi tablic------------------------------------------------

//WYMIARY

const int roz_blk = 5; //rozmiar pojedynczego bloku tablicy (kwadrat)

const int blk_x = 15; //ilosc blokow w osi x (szerokosc wiersza)

const int blk_y = 10; //ilosc blokow w osi y (szerokosc kolumny)

const int zas_rys = 5; //zasieg rysowania

const int x_tab = zas_rys*2 + roz_blk*blk_x; //ilosc kratek w tablicy (XXX)

const int y_tab = zas_rys*2 + roz_blk*blk_y; //ilosc kratek w tablicy (YYY)

const int wyb_tab = 6; //ilosc tablic (konieczna dla funkcji losujacej)

//WYPELNIENIE

const unsigned char sc = 219; //definicja sciany

const unsigned char pu = 32; //definicja wolnego miejsca

const unsigned char skb = 36; //definicja skarbu

const unsigned char gr = 64; //definicja gracza

//SZABLONY TABLIC


const unsigned char A[roz_blk][roz_blk]={{sc,sc,pu,sc,sc},
                                        {sc,pu,pu,sc,sc},
                                        {pu,pu,sc,pu,pu},
                                        {sc,pu,pu,pu,sc},
                                        {sc,sc,pu,sc,sc}};

const unsigned char B[roz_blk][roz_blk]={{sc,sc,pu,pu,sc},
                                        {pu,sc,sc,pu,sc},
                                        {pu,pu,pu,pu,pu},
                                        {sc,pu,pu,pu,sc},
                                        {sc,sc,pu,pu,sc}};

const unsigned char C[roz_blk][roz_blk]={{pu,pu,pu,pu,pu},
                                        {pu,pu,sc,pu,pu},
                                        {pu,pu,sc,sc,pu},
                                        {sc,pu,sc,sc,sc},
                                        {sc,pu,pu,pu,pu}};

const unsigned char D[roz_blk][roz_blk]={{sc,sc,pu,pu,pu},
                                        {sc,pu,pu,sc,pu},
                                        {pu,pu,sc,pu,pu},
                                        {pu,sc,pu,pu,sc},
                                        {sc,pu,pu,sc,sc}};

const unsigned char E[roz_blk][roz_blk]={{pu,pu,pu,sc,sc},
                                        {sc,pu,pu,pu,sc},
                                        {pu,pu,sc,pu,pu},
                                        {pu,pu,sc,pu,pu},
                                        {pu,pu,pu,pu,sc}};

const unsigned char F[roz_blk][roz_blk]={{sc,sc,pu,sc,sc},
                                        {sc,sc,pu,sc,sc},
                                        {pu,pu,pu,pu,pu},
                                        {sc,sc,pu,sc,sc},
                                        {sc,sc,pu,sc,sc}};

//Definicje zmiennych pozostalych--------------------------------------------------------------------------------------------

struct XY{ //Struktura opisujaca pozycje gracza

    int x;
    int y;

};

const int skarb_cel_podstawa = 5;

const int skarb_los_podstawa = 20;

const char Alarm = 7;


//Definicje funkcji do rysowania--------------------------------------------------------------------------------------

void DrawFull(unsigned char Tablica[][x_tab])
{
    for(int j=0; j<y_tab; j++){
        for(int i=0; i<x_tab; i++){
            cout << Tablica[j][i];}
        cout << endl;}
};

void DrawPartial(unsigned char Tablica[][x_tab], XY PozycjaGracza)
{
    for(int j=(PozycjaGracza.y-zas_rys); j<(PozycjaGracza.y + zas_rys+1); j++){
        for(int i=(PozycjaGracza.x-zas_rys); i<(PozycjaGracza.x + zas_rys+1); i++){
            cout << Tablica[j][i];}
        cout << endl;}
};




//Testowanie czy poprawnie wklepalem wzory segmentow

void TestSmall(const unsigned char Tablica[][roz_blk])
{
    for(int j=0; j<roz_blk; j++){
        for(int i=0; i<roz_blk; i++){
            cout << Tablica[j][i];}
        cout << endl;}
    cout << "----------" << endl;
};

void Debug()
{
    cout << "Uwaga! Diagnostyka." << endl << "Zapisane tablice:" <<endl;

    TestSmall(A);
    TestSmall(B);
    TestSmall(C);
    TestSmall(D);
    TestSmall(E);
    TestSmall(F);
    system("pause");
}

//Funkcje odpowiadajace za ruch gracza--------------------

int Gora(unsigned char Mapa[][x_tab], XY &PozycjaGracza, int Krok, int &Skarby)
{
    if(Mapa[(PozycjaGracza.y-1)][PozycjaGracza.x]!=sc)
    {
        if((Mapa[(PozycjaGracza.y-1)][PozycjaGracza.x])==skb)
        {
            Skarby++;
            cout << Alarm << Alarm << Alarm;
            Mapa[(PozycjaGracza.y)-1][PozycjaGracza.x]=gr;
            Mapa[PozycjaGracza.y][PozycjaGracza.x]=pu;
            PozycjaGracza.y=(PozycjaGracza.y)-1;
            Krok++;
        }
        else
        {
            Mapa[(PozycjaGracza.y)-1][PozycjaGracza.x]=gr;
            Mapa[PozycjaGracza.y][PozycjaGracza.x]=pu;
            PozycjaGracza.y=(PozycjaGracza.y)-1;
            Krok++;
        }
    }
    else cout << Alarm;
    return Krok;
}

int Dol(unsigned char Mapa[][x_tab], XY &PozycjaGracza, int Krok, int &Skarby)
{
    if(Mapa[(PozycjaGracza.y+1)][PozycjaGracza.x]!=sc)
    {
        if(Mapa[(PozycjaGracza.y+1)][PozycjaGracza.x]==skb)
        {
            Skarby++;
            cout << Alarm << Alarm << Alarm;
            Mapa[(PozycjaGracza.y)+1][PozycjaGracza.x]=gr;
            Mapa[PozycjaGracza.y][PozycjaGracza.x]=pu;
            PozycjaGracza.y=(PozycjaGracza.y)+1;
            Krok++;
        }
        else
        {
            Mapa[(PozycjaGracza.y)+1][PozycjaGracza.x]=gr;
            Mapa[PozycjaGracza.y][PozycjaGracza.x]=pu;
            PozycjaGracza.y=(PozycjaGracza.y)+1;
            Krok++;
        }
    }
    else cout << Alarm;
    return Krok;
}

int Lewo(unsigned char Mapa[][x_tab], XY &PozycjaGracza, int Krok, int &Skarby)
{
    if(Mapa[PozycjaGracza.y][(PozycjaGracza.x-1)]!=sc)
    {
        if(Mapa[PozycjaGracza.y][(PozycjaGracza.x-1)]==skb)
        {
            Skarby++;
            cout << Alarm << Alarm << Alarm;
            Mapa[PozycjaGracza.y][(PozycjaGracza.x-1)]=gr;
            Mapa[PozycjaGracza.y][PozycjaGracza.x]=pu;
            PozycjaGracza.x=(PozycjaGracza.x)-1;
            Krok++;
        }
        else
        {
            Mapa[PozycjaGracza.y][(PozycjaGracza.x)-1]=gr;
            Mapa[PozycjaGracza.y][PozycjaGracza.x]=pu;
            PozycjaGracza.x=(PozycjaGracza.x)-1;
            Krok++;
        }
    }
    else cout << Alarm;
    return Krok;
}

int Prawo(unsigned char Mapa[][x_tab], XY &PozycjaGracza, int Krok, int &Skarby)
{
    if(Mapa[PozycjaGracza.y][(PozycjaGracza.x+1)]!=sc)
    {
        if(Mapa[PozycjaGracza.y][(PozycjaGracza.x+1)]==skb)
        {
            Skarby++;
            cout << Alarm << Alarm << Alarm;
            Mapa[PozycjaGracza.y][(PozycjaGracza.x+1)]=gr;
            Mapa[PozycjaGracza.y][PozycjaGracza.x]=pu;
            PozycjaGracza.x=(PozycjaGracza.x)+1;
            Krok++;
        }
        else
        {
            Mapa[PozycjaGracza.y][(PozycjaGracza.x)+1]=gr;
            Mapa[PozycjaGracza.y][PozycjaGracza.x]=pu;
            PozycjaGracza.x=(PozycjaGracza.x)+1;
            Krok++;
        }
    }
    else cout << Alarm;
    return Krok;
}

//Funkcja rysujaca krawedzie, ochrona przed wyjsciem poza tablice i rysowaniem smieci (hakjerskie rozwiazanie!)

void ObrysTab(unsigned char Mapa[][x_tab])
{
    //Gorna krawedz
    for(int j=0; j<zas_rys; j++){
        for(int i=0; i<x_tab; i++){
            Mapa[j][i]=sc;}
    }
    //Dolna krawedz
    for(int j=y_tab-zas_rys; j<y_tab; j++){
        for(int i=0; i<x_tab; i++){
            Mapa[j][i]=sc;}
    }
    //Lewa krawedz
    for(int j=0; j<y_tab; j++){
        for(int i=0; i<zas_rys; i++){
            Mapa[j][i]=sc;}
    }
    //Prawa krawedz
    for(int j=0; j<y_tab; j++){
        for(int i=x_tab-zas_rys; i<x_tab; i++){
            Mapa[j][i]=sc;}
    }
}

//Funkcja kopiujaca z szablonu do tablicy (zmienne off - OFFSET tablicy docelowej)

void CopyTab(unsigned char Cel[][x_tab], const unsigned char Zrodlo[][roz_blk], int x_off, int y_off)
{
    for(int j=0; j<roz_blk; j++){
        for(int i=0; i<roz_blk; i++){
            Cel[y_off+j][x_off+i]=Zrodlo[j][i];}
    }
}

//Funkcja losujaca szablony do tablicy

void RandTab(unsigned char Cel[][x_tab])
{
    for(int j=0; j<blk_y; j++){
        for(int i=0; i<blk_x; i++){

            int randblk;
            randblk = 1+rand()%(wyb_tab);
            switch(randblk)
            {
            case 1:
                CopyTab(Cel, A, (zas_rys + (roz_blk*i)), (zas_rys + (roz_blk*j)) );
                break;

            case 2:
                CopyTab(Cel, B, (zas_rys + (roz_blk*i)), (zas_rys + (roz_blk*j)) );
                break;

            case 3:
                CopyTab(Cel, C, (zas_rys + (roz_blk*i)), (zas_rys + (roz_blk*j)) );
                break;

            case 4:
                CopyTab(Cel, D, (zas_rys + (roz_blk*i)), (zas_rys + (roz_blk*j)) );
                break;

            case 5:
                CopyTab(Cel, E, (zas_rys + (roz_blk*i)), (zas_rys + (roz_blk*j)) );
                break;

            case 6:
                CopyTab(Cel, F, (zas_rys + (roz_blk*i)), (zas_rys + (roz_blk*j)) );
                break;
            }

        }
    }
}

//Funkcja losujaca polozenie skarbow

void GenSkarb(unsigned char Tab[][x_tab], int skarb_los)
{
    for(int i=0; i<skarb_los; ){
        int rand_x;
        int rand_y;

        rand_x = rand()%x_tab;
        rand_y = rand()%y_tab;

        if(Tab[rand_y][rand_x]==pu){
            Tab[rand_y][rand_x]=skb;
            i++;}
    }
}

//Losowanie polozenia gracza w tablicy i strukturze

void GenGracz(unsigned char Tab[][x_tab], XY &PozycjaGracza)
{
    for(int i=0; i<1; ){
        int rand_x;
        int rand_y;

        rand_x = rand()%x_tab;
        rand_y = rand()%y_tab;

        if(Tab[rand_y][rand_x]==pu){
            Tab[rand_y][rand_x] = gr;
            PozycjaGracza.x = rand_x;
            PozycjaGracza.y = rand_y;
            i++;}
    }
}

int main()
{
    int poziom = 0;


    while(true)
    {
        //To co sie zmienia w trakcie gry

        unsigned char MAPA[y_tab][x_tab];
        int krok = 0;
        int skarby = 0;
        XY Gracz;
        int hack = 0;

        int skarb_cel_poziom = skarb_cel_podstawa + poziom;
        int skarb_los_poziom = skarb_los_podstawa + 3*poziom;

        //Inicjalizacja generatora liczb

        srand(time(NULL));

        //Przygotowanie mapy

        ObrysTab(MAPA);
        RandTab(MAPA);
        GenGracz(MAPA, Gracz);
        GenSkarb(MAPA, skarb_los_poziom);




        while(skarby<skarb_cel_poziom)
        {
            system("cls");

            if(hack==1)
                DrawFull(MAPA);
            else DrawPartial(MAPA, Gracz);

            cout << endl << "Poziom:" << pu << poziom << pu << "Skarby:" << pu << skarby << pu << "Brakuje:" << pu << skarb_cel_poziom - skarby << pu << endl;

            char wybor;

            wybor = _getch();

            switch(wybor)
            {
            case 'w':
                krok=Gora(MAPA, Gracz, krok, skarby);
                break;
            case 's':
                krok=Dol(MAPA, Gracz, krok, skarby);
                break;
            case 'a':
                krok=Lewo(MAPA, Gracz, krok, skarby);
                break;
            case 'd':
                krok=Prawo(MAPA, Gracz, krok, skarby);
                break;
            case 'n':
                hack=1;
                break;
            case 'm':
                hack=0;
                break;
            case 'x':
                Debug();
                break;
            default:
                break;
            }
        }
        system("cls");
        cout << "Gratulacje! Wykonales zadanie w:" << pu << krok << pu << "krokow!" << endl;
        poziom++;
        system("pause");
    }
}
