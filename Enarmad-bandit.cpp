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

int räknaVinstRader(int spelPlan[3][3]){

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

    return vinstRader;
    
}

int main()
{
    //Sätter variabler och startar seed timer
    string username = "Användare";
    int saldo = 0;
    bool fortsättSpelet = true;
    srand(time(0));

    //Ber om användarens namn samt förklarar spelets regler
    cout << endl << endl <<"Vad heter du: ";
    cin >> username;
    cout << endl << endl << "Hej "<< username <<"!" << endl 
    << "Reglerna är enkla. Du kommer att få sätta in pengar och välja en insats." <<
    "Ett 3x3 bräde kommer att presenteras för dig med ettor tvåor och treor. " <<
    "Får du en rad som representeras utav samma siffra vinner du " <<
    "Annars förlorar du din insats."
    "Nu kör vi!"<< endl;

    //Användaren sätter in pengar som läggs till saldot
    cout << endl <<"Hur mycket pengar vill du sätta in?" << endl;
    saldo = takeInput('i', saldo);

    //Spelloopen startar och fortsätter tills användaren vill avsluta.
    while(fortsättSpelet){
        //Be om insats och dra bort insatsen från saldot.
        cout << endl <<"Hur mycket pengar vill du satsa?" << endl;
        int satsa = takeInput('s', saldo);
        saldo -= satsa;
        cout << "Ditt saldo är nu: " << saldo << "kr" << endl << "Du har valt Insatsen: " << satsa << "kr" << endl << endl;
        
        //Skapa spelplanen och allokera symboler 1, 2 elle 3 till de nio fälten i 2Darrayen
        int spelPlan[3][3];
        for(int i = 0;i<3 ;i++){
            for(int j = 0; j<3;j++){
                spelPlan[i][j] = slumpaSpelPlan(i, j);
                cout << spelPlan[i][j] << " ";
            }
            cout << endl;
        }

        //Funktion som räknar ut hur många vinstrader det blev på brädet
        int vinstRader = räknaVinstRader(spelPlan);

        //Funktion som räknar ut vad vinsten blev sedan adderas den till saldot och användaren informeras.
        int vinst = räknaUtVinst(satsa, vinstRader);
        saldo += vinst;
        cout << endl << endl <<"Du vann" << vinst << "kr. Ditt saldo är nu: " << saldo << endl << endl;

        //Stämmer av om användaren har några pengar kvar, om inte får de möjlighet att sätta in nya pengar.
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
            //Om användaren har saldo ställs frågan om en ny spelomgång önskas.
            cout << endl << "Vill du fortsätta spelet?";
            cin >> fortsättSpelet;
        }
    }

    return 0;
}
