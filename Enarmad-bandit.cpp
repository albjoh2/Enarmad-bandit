#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const int SPELPLANENS_STORLEK = 3;
const int ANTAL_SYMBOLER = 3;

int takeInput(char inputType, int saldo){
    bool approvedValue = false;
    int value = 0;
    while(!approvedValue){
        //Inputs som ska vara av typen int går in i detta blocket.
        if(inputType == 'i' || inputType == 's'){
            cin >> value;
            //Om felaktig input anges ex en bokstav rensas inputen
            while (cin.fail()){
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Insatsen ska vara ett heltal. ";
            }
            //Om inputen är användarens insättning kollar detta blocket om värdet är korrekt.
            if (inputType == 'i'){
                approvedValue = (value == 100 || value == 300 || value == 500);
                if(!approvedValue){
                    cout << "Prova igen, giltiga insättningar är 100, 300 och 500!" << endl;
                }
            }
            //Om inputen är hur mycket användaren vill sattsa kollar detta blocket att insattsen är mellan 1kr - saldot.
            if (inputType == 's'){
                approvedValue = (value > 0 && value <= saldo);
                if(!approvedValue){
                    cout << "Prova igen, ange ett tal mellan 1 - " << saldo << "." << endl;
                }
            }
        } //Om intputen ska tas emot som en string kontrolleras det i detta blocket.
        else{
            string svar = "";
            cin >> svar;
            if (inputType == 'y'){
                approvedValue = (svar == "ja" || svar == "Ja" || svar == "nej" || svar == "Nej");
                if(!approvedValue){
                    cout << "Prova igen, vänligen svara ja eller nej." << endl;
                }else{
                    if (svar == "ja" || svar == "Ja"){
                        value = 1;
                    } else{
                        cout << "Du har valt att avsluta spelet, ditt saldo är: " << saldo << ". Tack för att du spelat!";
                        value = 0;
                    }
                    
                }
            }
        }
        
    }
    return value;
}


int slumpaSpelPlan(int i, int j){
    int slumpadSymbol = rand() % ANTAL_SYMBOLER+1;
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
        multiplikator = 10;
    }
    int vinst = insats * multiplikator;
    return vinst;
}

int räknaVinstRader(int spelPlan[SPELPLANENS_STORLEK][SPELPLANENS_STORLEK]){
    
    int vinstRader = 0;

    //Kollar antalet rader med vinst genom att itterera raderna.
    for(int i = 0;i<SPELPLANENS_STORLEK ;i++){
        for(int j = 0; j<SPELPLANENS_STORLEK ;j++){
            if(j == SPELPLANENS_STORLEK - 1){
                vinstRader += 1;
                break;
            }
            if(spelPlan[i][j] == spelPlan[i][j+1]){
                continue;
            }else{
                break;
            }
        }
    }

    //Kollar antalet kollumner med vinst genom att itterera kollumnerna.
    for(int j = 0; j<SPELPLANENS_STORLEK;j++){
        for(int i = 0;i<SPELPLANENS_STORLEK ;i++){
            if(i == SPELPLANENS_STORLEK - 1){
                vinstRader += 1;
            }
            if(spelPlan[i][j] == spelPlan[i+1][j]){
                continue;
            }else{
                break;
            }
        }
    }

    
    //Kontrollerar om det blev vinstrad i diagonal 1
    for (int i = 0; i < SPELPLANENS_STORLEK; i++){
        if(i == SPELPLANENS_STORLEK - 1){
            vinstRader += 1;
        }
        if(spelPlan[i][i] == spelPlan[i+1][i+1]){
            continue;
        }
        else{
            break;
        }
    }
    
    //Kontrollerar om det blev vinstrad i diagonal 2
    for (int i = 0; i < SPELPLANENS_STORLEK; i++){
        if (i == SPELPLANENS_STORLEK - 1){
            vinstRader += 1;
        }
        if(spelPlan[SPELPLANENS_STORLEK - 1 - i][i] == spelPlan[SPELPLANENS_STORLEK - i - 2][i+1]){
            continue;
        }else{
            break;
        }
    }

    //Skriv ut antalet vinstrader
    if (vinstRader < 1){
        cout << endl << "Tyvärr ingen vinst denna gång.";
    }else{
        cout << endl << "Grattis, det blev " << vinstRader << (vinstRader == 1 ? " vinstrad!":" vinstrader!");
    }

    return vinstRader;
    
}

int test(){
    bool testOk = true;
    int one[SPELPLANENS_STORLEK][SPELPLANENS_STORLEK];
    for (int i = 0; i < SPELPLANENS_STORLEK; i++){
        for (int j = 0; j < SPELPLANENS_STORLEK; j++){
        one[i][j] = 1;
        }
    }
    //test som kontrollerar att funtionen räknaVinstRader fungerer som den ska.
    if (räknaVinstRader(one) != SPELPLANENS_STORLEK * 2 + 2){
        cout << " Test 1 misslyckades";
        testOk = false;
    }
    return testOk;
}

int main(){
    // Detta är ett test, om den skriver ut 1 är testet ok skriver den ut 0 är något fel.
    // cout << test();

    //Sätter variabler och startar seed timer
    string username = "Användare";
    int saldo = 0;
    bool fortsättSpelet = true;
    srand(time(0));

    //Ber om användarens namn samt förklarar spelets regler
    cout << endl << endl <<"Vad heter du: ";
    cin >> username;
    cout << endl << endl << "Hej "<< username <<"!" << endl 
    << "Reglerna är enkla. Du kommer att få sätta in pengar och välja en insats. " << endl <<
    "Ett rutnät kommer att presenteras för dig där varje ruta innehåller en siffra. " << endl <<
    "Får du en hel rad, kolumn eller diagonal med samma siffra har du en vinstrad, fler vinstrader ger mer pengar. " << endl <<
    "Får du inga vinstrader förlorar du din insats." << endl <<
    "Nu kör vi!"<< endl;

    //Användaren sätter in pengar som läggs till saldot
    cout << endl <<"Hur mycket pengar vill du sätta in? (100, 300 eller 500kr)" << endl;
    saldo = takeInput('i', saldo);

    //Spelloopen startar och fortsätter tills användaren vill avsluta.
    while(fortsättSpelet){
        //Linje som avgränsar spelomgångarna.
        cout << "_________________" << endl;

        //Be om insats och dra bort insatsen från saldot.
        cout << endl <<"Hur mycket pengar vill du satsa?" << endl;
        int satsa = takeInput('s', saldo);
        saldo -= satsa;
        cout << "Du har valt Insatsen: " << satsa << "kr" << endl << "Ditt saldo är nu: " << saldo << "kr" << endl << endl;

        //Skapa spelplanen och allokera symboler till spelfälten
        cout << "Här är omgångens spelplan:" << endl;
        int spelPlan[SPELPLANENS_STORLEK][SPELPLANENS_STORLEK];
        for (int i = 0; i < SPELPLANENS_STORLEK; i++){
            cout << "|–––";
        }
        cout << "|" << endl;

        for(int i = 0;i<SPELPLANENS_STORLEK ;i++){
            for(int j = 0; j<SPELPLANENS_STORLEK;j++){
                spelPlan[i][j] = slumpaSpelPlan(i, j);
                cout << "| " << spelPlan[i][j] << " ";
            }
            cout << "|" << endl;
            for (int i = 0; i < SPELPLANENS_STORLEK; i++){
                cout << "|–––";
            }
            cout << "|" << endl;
        }

        //Funktion som räknar ut hur många vinstrader det blev på brädet
        int vinstRader = räknaVinstRader(spelPlan);

        //Funktion som räknar ut vad vinsten blev sedan adderas den till saldot och användaren informeras.
        int vinst = räknaUtVinst(satsa, vinstRader);
        saldo += vinst;
        cout << endl << endl << "Du vann " << vinst << "kr. Ditt saldo är nu: " << saldo << "kr" << endl << endl;

        //Stämmer av om användaren har några pengar kvar, om inte får de möjlighet att sätta in nya pengar.
        if (saldo < 1){
            bool nyInsättning;
            cout << "Dina pengar är slut, vill du göra en ny insättning?(ja/nej)";
            nyInsättning = takeInput('y', saldo);
            while (cin.fail()){
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Insatsen ska vara 1 eller 0. ";
            }
            if(nyInsättning){
                cout << endl <<"Hur mycket pengar vill du sätta in?" << endl;
                saldo += takeInput('i', saldo);     
            }else{
                fortsättSpelet = false;
            }
        }else{
            //Om användaren har saldo ställs frågan om en ny spelomgång önskas.
            cout << endl << "Vill du fortsätta spelet?(ja/nej) ";
            fortsättSpelet = takeInput('y', saldo);
        }
    }

    return 0;
}

