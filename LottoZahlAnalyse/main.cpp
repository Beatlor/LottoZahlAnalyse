//
//  main.cpp
//  LottoZahlAnalyse
//
//  Created by Stephan on 17.11.18.
//  Copyright © 2018 Stephan Callsen. All rights reserved.
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <bitset>


using namespace std;

void bsort(uint64_t list[], int size)
{
    uint64_t temp;
    for(int i=0; i<size; i++)
    {
        for(int j=size-1; j>i; j--)
        {
            if(list[j]<list[j-1])
            {
                temp=list[j-1];
                list[j-1]=list[j];
                list[j]=temp;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    bool DBG=false;
    string DrawWeek;
    int Weeks = 1;
    int AllDraw[5000][6];
    uint64_t Sum[5000], CopySum[5000],MagDig=0;
    uint16_t i=0, j=0, DigitExist=0, Occurences[49],AllBalls=0;
    
    char F_NAME[] = "alldraws55-17";
    ifstream FILE;
    FILE.open (F_NAME, ios::in);
    if (FILE.is_open())
        {
        while ( getline (FILE,DrawWeek) )
            {
                DrawWeek.erase((DrawWeek.size() - 1));
                if (DrawWeek != ";;;;;;")
                {
                    if (DBG) cout << DrawWeek << '\n';
                    istringstream s(DrawWeek);
                    string field;
                    i=0;
                    while (getline(s, field,';'))
                    {
                        AllDraw[Weeks][i]= stoi(field,nullptr,0);
                        if (DBG) cout << "Week: " << AllDraw[Weeks][i] << "\n";
                        i++;
                    }
                    sort(AllDraw[Weeks],AllDraw[Weeks]+6);
                    if (DBG) cout << "Row/Week " << Weeks << " - ";
                    for (i=0;i<6;i++)
                    {
                        if (DBG) cout << AllDraw[Weeks][i] << " ";
                        Sum[Weeks]+=pow(2,(AllDraw[Weeks][i]-1));
                        CopySum[Weeks]=Sum[Weeks];
                    }
                    if (DBG) cout << "Sum " << Sum[Weeks] << "  Bit " << bitset<49>(Sum[Weeks])<< "\n";
                    if (DBG) cout << bitset<49>(Sum[Weeks])<< "\n";
                    Weeks++;
                }
            }
        FILE.close();
        }
    else cout << "Unable to open file";
    for (i=0; i<Weeks;i++)
    {
        //cout << "Week: " << i << " Bits " << bitset<49>(Sum[i])<< "\n";
    }
    bsort (CopySum, Weeks);
    for (i=1; i<Weeks;i++)
    {
        cout << "Sorted: " << i << " Sum " << CopySum[i] <<"  - Bits " << bitset<49>(CopySum[i])<< "\n";
    }
    cout << "-----------------------------------------------------\n\n";
    for (i=1; i<50;i++)
    {
        DigitExist=0;
        for (j=0; j<Weeks;j++)
        {
            DigitExist+=(CopySum[j] >> (i-1)) & 1;
        }
        Occurences[i-1]=DigitExist;
        AllBalls+=DigitExist;
        if (Occurences[i-1]>531) cout << "Field " << i << " Exist " << Occurences[i-1] << "\n";
    }
    cout << "Balls " << AllBalls << " in " << Weeks-1 <<" Weeks\n\n";
    MagDig= (1UL<<5)|(1UL<<21)|(1UL<<25)|(1UL<<31)|(1UL<<37)|(1UL<<48);
    cout << MagDig << "\n\n";
    for (i=0; i<Weeks;i++)
    {
        if ( Sum[i]==MagDig) cout << "Match " << i;
    }
    return 0;
}
