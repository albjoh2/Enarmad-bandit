#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int takeInput(char inputType, int saldo){
    int value = 0;
    bool approvedValue = false;
    while(!approvedValue){
        cin >> value;
        if (inputType == 'i'){
            approvedValue = (value == 100 || value == 300 || value == 500);
        }
        if (inputType == 's'){
            approvedValue = (value > 0 && value <= saldo);
        }
        if(!approvedValue){
            cout << "Ej godkänt värde, prova igen!" << endl;
        }
    }
    return value;
}


int slumpaSpelPlan(int i, int j){
    int slumpadSymbol = rand() % 3+1;
    return slumpadSymbol;
}

int räknaUtVinst(int insats, int vinstrader){
    int multiplikator = 0;
    if(vinstrader == 1){
        multiplikator = 2;
    }else if (vinstrader == 2){
        multiplikator = 3;
    }else if (vinstrader == 3){
        multiplikator = 4;
    }else if (vinstrader == 4){
        multiplikator = 5;
    }else if (vinstrader == 5){
        multiplikator = 7;
    }else if (vinstrader == 6){
        multiplikator = 8;
    }else if (vinstrader > 7){
        multiplikator = 9;
    }
    int vinst = insats * multiplikator;
    return vinst;
}

int main()
{
    string name = "Användare";
    cout << endl << endl <<"Vad heter du: ";
    cin >> name;
    cout << endl << endl << "Hej "<< name <<"!" << endl << "Nu kör vi!"<< endl;
    int saldo = 0;
    bool fortsättSpelet = true;
    srand(time(0));
    cout << endl <<"Hur mycket pengar vill du sätta in?" << endl;
    int insats = takeInput('i', saldo);
    saldo += insats;
    while(fortsättSpelet){
        cout << endl <<"Hur mycket pengar vill du satsa?" << endl;
        int satsa = takeInput('s', saldo);
        saldo -= satsa;
        cout << "Ditt saldo är nu: " << saldo << "kr" << endl << "Du har valt Insatsen: " << satsa << "kr" << endl << endl;
        int spelPlan[3][3];
        for(int i = 0;i<3 ;i++){
            for(int j = 0; j<3;j++){
                spelPlan[i][j] = slumpaSpelPlan(i, j);
                cout << spelPlan[i][j] << " ";
            }
            cout << endl;
        }


        int radSymbol;
        int antalIRad;
        int vinstRader = 0;

        //Kollar antalet rader
        for(int i = 0;i<3 ;i++){
            for(int j = 0; j<3;j++){
                if(radSymbol == spelPlan[i][j]){
                    antalIRad += 1;
                    if(antalIRad == 2){
                        vinstRader += 1;
                    }
                }
                radSymbol = spelPlan[i][j];
            }
            radSymbol = 0;
            antalIRad = 0;
        }

        //Kollar antalet kollumner
        for(int j = 0; j<3;j++){
            for(int i = 0;i<3 ;i++){
                if(radSymbol == spelPlan[i][j]){
                    antalIRad += 1;
                    if(antalIRad == 2){
                        vinstRader += 1;
                    }
                }
                radSymbol = spelPlan[i][j];
            }
            radSymbol = 0;
            antalIRad = 0;
        }

        if(spelPlan[0][0] == spelPlan[1][1] && spelPlan[1][1] == spelPlan[2][2]){
            vinstRader += 1;
        }
        if(spelPlan[2][0] == spelPlan[1][1] && spelPlan[1][1] == spelPlan[0][2]){
            vinstRader += 1;
        }


        if (vinstRader < 1){
            cout << "Tyvärr ingen vinst denna gång.";
        }else{
            cout << vinstRader << (vinstRader == 1 ? " vinstrad":" vinstrader");
        }

        int vinst = räknaUtVinst(satsa, vinstRader);

        saldo += vinst;

        cout << endl << endl <<"Du vann" << vinst << "kr. Ditt saldo är nu: " << saldo << endl << endl;

        if (saldo < 1){
            bool nyInsättning;
            cout << "Dina pengar är slut, vill du göra en ny insättning?";
            cin >> nyInsättning;
            if(nyInsättning){
                cout << endl <<"Hur mycket pengar vill du sätta in?" << endl;
                saldo += takeInput('i', saldo);     
            }else{
                fortsättSpelet = false;
            }
        }else{
            cout << endl << "Vill du fortsätta spelet?";
            cin >> fortsättSpelet;
        }
    }

    return 0;
}
