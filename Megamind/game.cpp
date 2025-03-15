#include "util.h"
#include <iostream>
#include <vector>

using namespace std;

int pegNum = 0;
int colorNum = 0;
bool correct = false;
int correctCount = 0;
int totalCount = 0;
int veryGood = 0;
int partiallyGood = 0;
int turns = 0;
bool multiplayer = false;
bool badNum = false;
vector<int> p1Col;
vector<int> p2Col;
bool winner = false;
int p2totalCount = 0;
int p2correctCount = 0;
int p1correctCount = 0;
int p1totalCount = 0;
bool backpackerings = false;
vector<int> p1Backpack{0, 0, 0, 0, 0, 0};
vector<int> p2Backpack{0, 0, 0, 0, 0, 0};
vector<string> itemCatalog{"Draag", "Sapper", "D.D. Dynamite", "Acme box", "Blink gun", "Showstopper"}; 
int p1ItemCounter = 0;
int p2ItemCounter = 0;
int p1ItemTot = 0;
int p2ItemTot = 0;
bool p1BugsBunny = false;
bool p2BugsBunny = false;
int p1CorrectAndPlaced = 0;
int p1CorrectTotal = 0;
int p2CorrectAndPlaced = 0;
int p2CorrectTotal = 0;
int p1Moves = 0;
int p2Moves = 0;
bool p1SapperUsed = false;
bool p2SapperUsed = false;
int showstop = 0;
vector<string> adjectives{"SHUT DOWN!", "TRASHED!", "DEFENESTRATED!", "BLUDGEONED!", "DEMOLISHED!", "DISMANTLED!", "CONFUISIFIED!"};
bool streetFighterStyle = false;
vector<int> SFP1Col;
vector<int> SFP2Col;
int p1HP = 20;
int p2HP = 20;
int p1Power = 15;
int p2Power = 15;
vector<int> powerIndex{2, 3, 5};

int correctSpot(vector<int> pGuess, vector<int> colors){
    for (int b = 0; b < pegNum; b++){
        if (pGuess[b] == colors[b]){
            veryGood ++;
        }
    }
    return veryGood;
}
int correctOverall(vector<int> pGuess, vector <int> colors){
    for (int c = 0; c < pegNum; c++){
        for (int d = c + 1; d < pegNum; d++){
            if (pGuess[c] == pGuess[d]){
                pGuess[c] = 10000;
            }
        }
    }
    for (int e = 0; e < pegNum; e++){
        for (int f = 0; f < pegNum; f++){
            if (colors[e] == pGuess[f]){
                partiallyGood ++;
            }
        }
    }
    return partiallyGood;
}

void guess (vector<int> colors){
    vector<int> pGuess;
    while (correct == false){
        for (int j = 1; j <= pegNum; j++){
            cout << "Please enter the color for peg " << j;
            int guess = readInt(": ");
            while (guess < 0 || guess > colorNum){
                cout << "Please enter the color for peg " << j;
                guess = readInt(": ");
            }
            pGuess.push_back(guess);
        }
        
        int correctAndPlaced = correctSpot(pGuess, colors);
        int correctTotal = correctOverall(pGuess, colors);
        
        for (int a = 0; a < pegNum; a++){
            if (pGuess[a] == colors[a]){
                correctCount ++;
            }
            totalCount ++;
        }
        if (correctCount == totalCount){
            correct = true;
        }
        else{
            cout << "You have " << correctAndPlaced << " peg/pegs correct and " << correctTotal - correctAndPlaced << " color/colors correct, but in the wrong place." << endl;
            turns ++;
            correctAndPlaced = 0;
            correctTotal = 0;
            totalCount = 0;
            correctCount = 0;
            veryGood = 0;
            partiallyGood = 0;
            for (int b = 1; b <= pegNum; b++){
                pGuess.pop_back();
            }
        }
    }
    cout << "Great Job! You solved the puzzle in " << turns + 1 << " turns!" << endl;
}

vector<int> addCol(){
    vector<int> num{1,2,3,4,5,6,7,8};
    vector<int> colors;
    int numMax = colorNum - 1;
    for (int i = 0; i < pegNum; i++){
        int randColor = randInt(0, numMax);
        colors.push_back(num[randColor]);
        num.erase(num.begin() + randColor);
        numMax --;
    }
    return colors;
}


vector<int> findP2(){
    vector<int> num{1,2,3,4,5,6,7,8};
    vector<int> p2Code;
    for (int k = 1; k <= pegNum; k++){
        cout << "P1: Please enter a unique color for peg " << k << " (1 - the number of colors)";
        int cColor = readInt(": ");
        cColor --;
        if (cColor < 0 || cColor > 7){
            badNum = true;
        }
        else if (num[cColor] == 100){
            badNum = true;
        }
        else if (cColor > colorNum - 1){
            badNum = true;
        }
        else{
            badNum = false;
        }
        while (badNum == true){
            cout << "P1: Please enter a unique color for peg " << k << " (1 - the number of colors)";
            cColor = readInt(": ");
            cColor --;
            if (cColor < 0 || cColor > 7){
                badNum = true;
            }
            else if (num[cColor] == 100){
                badNum = true;
            }
            else if (cColor > colorNum - 1){
                badNum = true;
            }
            else{
                badNum = false;
            }
        }
        p2Code.push_back(num[cColor]);
        num[cColor] = 100;
    }
    return p2Code;
}

vector<int> findP1(){
    vector<int> num{1,2,3,4,5,6,7,8};
    vector<int> p1Code;
    for (int k = 1; k <= pegNum; k++){
        cout << "P2: Please enter a unique color for peg " << k << " (1 - the number of colors)";
        int cColor = readInt(": ");
        cColor --;
        if (cColor < 0 || cColor > 7){
            badNum = true;
        }
        else if (num[cColor] == 100){
            badNum = true;
        }
        else if (cColor > colorNum - 1){
            badNum = true;
        }
        else{
            badNum = false;
        }
        while (badNum == true){
            cout << "P2: Please enter a unique color for peg " << k << " (1 - the number of colors)";
            cColor = readInt(": ");
            cColor --;
            if (cColor < 0 || cColor > 7){
                badNum = true;
            }
            else if (num[cColor] == 100){
                badNum = true;
            }
            else if (cColor > colorNum - 1){
                badNum = true;
            }
            else{
                badNum = false;
            }
        }
        p1Code.push_back(num[cColor]);
        num[cColor] = 100;
    }
    return p1Code;
}

void p1Items (){
    if (p1ItemCounter == 1){
        int randItem = randInt(0, 5);
        for (int l = 0; l < 6; l++){
            if (randItem == l){
                cout << endl;
                cout << "P1 has found a wild " << itemCatalog[l] << "!" << endl;
                p1Backpack[l]++;
            }
        }
        p1ItemCounter = 0;
    }
    for (int v = 0; v < 5; v++){
        p1ItemTot = p1ItemTot + p1Backpack[v];
    }
    if (p1ItemTot > 0){
        cout << endl;
        cout << "P1: You have an item available to use! Here are your options and how many of each you have:" << endl;
        for (int w = 0; w < 5; w++){
            cout << "Item #" << w + 1 << ": " << itemCatalog[w] << ". You have " << p1Backpack[w] << " of these." << endl;
        }
        int itemChoose = readInt(0, 5, "Choose the item number to use that item or 0 to use none: ", "Choose the item number to use that item or 0 to use none: ");
        while (p1Backpack[itemChoose - 1] == 0 && itemChoose != 0){
            itemChoose = readInt(0, 5, "You do not have that item. Please choose another one. ", "You do not have that item. Please choose another one. ");
        }
        if (itemChoose == 1){
            int draagChance = randInt(0, pegNum - 1);
            p1Backpack[0]--;
            cout << "You have chosen to use the Draag!";
            if (p2Backpack[5] > 0){
                cout << endl;
                cout << "P2: You have " << p2Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                cout << "The color of peg " << draagChance + 1 << " is " << p1Col[draagChance] << "!" << endl;
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT DRAAG HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
        if (itemChoose == 2){
            cout << "You have chosen to use the Sapper!";
            p1Backpack[1]--;
            if (p2Backpack[5] > 0){
                cout << endl;
                cout << "P2: You have " << p2Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                cout << "Your opponent's next guess will give information about your code!" << endl;
                p1SapperUsed = true;
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT SAPPER HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
        if (itemChoose == 3){
            cout << "You have chosen to use a stick of D.D. Dynamite!";
            p1Backpack[2]--;
            if (p2Backpack[5] > 0){
                cout << endl;
                cout << "P2: You have " << p2Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                cout <<  "Your opponent's code has been scrambled!" << endl;
                p2Col = addCol();
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT DYNAMITE HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
        if (itemChoose == 4){
            cout << "You have chosen to use an Acme box!";
            p1Backpack[3]--;
            if (p2Backpack[5] > 0){
                cout << endl;
                cout << "P2: You have " << p2Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                int acmeChance = randInt(1, 2);
                if (acmeChance == 1){
                    cout << " WUH OH! Looks like Bugs Bunny made you have a bad hare day (get it?). Your turn has been skipped so you can emotionally recover." << endl;
                    p1BugsBunny = true;
                }
                if (acmeChance == 2){
                    cout << " Lucky you! Bugs Bunny dropped an anvil on your opponent's toe. Their next turn has been skipped!" << endl;
                    p2BugsBunny = true;
                }
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT ACME BOX HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
        if (itemChoose == 5){
            cout << "You have chosen to use the blink gun! Both you and your opponent's codes have been shortened by one peg!" << endl;
            p1Backpack[4]--;
            if (p2Backpack[5] > 0){
                cout << endl;
                cout << "P2: You have " << p2Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                p1Col.pop_back();
                p2Col.pop_back();
                pegNum --;
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT BLINK GUN HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
    }
}

void p2Items (){
    if (p2ItemCounter == 1){
        int randItem = randInt(0, 5);
        for (int l = 0; l < 6; l++){
            if (randItem == l){
                cout << endl;
                cout << "P2 has found a wild " << itemCatalog[l] << "!" << endl;
                p2Backpack[l]++;
            }
        }
        p2ItemCounter = 0;
    }
    for (int v = 0; v < 5; v++){
        p2ItemTot = p2ItemTot + p2Backpack[v];
    }
    if (p2ItemTot > 0){
        cout << endl;
        cout << "P2: You have an item available to use! Here are your options and how many of each you have:" << endl;
        for (int w = 0; w < 5; w++){
            cout << "Item #" << w + 1 << ": " << itemCatalog[w] << ". You have " << p2Backpack[w] << " of these." << endl;
        }
        int itemChoose = readInt(0, 5, "Choose the item number to use that item or 0 to use none: ", "Choose the item number to use that item or 0 to use none: ");
        while (p2Backpack[itemChoose - 1] == 0 && itemChoose != 0){
            itemChoose = readInt(0, 5, "You do not have that item. Please choose another one. ", "You do not have that item. Please choose another one. ");
        }
        if (itemChoose == 1){
            int draagChance = randInt(0, pegNum - 1);
            p2Backpack[0]--;
            cout << "You have chosen to use the Draag!";
            if (p1Backpack[5] > 0){
                cout << endl;
                cout << "P1: You have " << p1Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                cout << "The color of peg " << draagChance + 1 << " is " << p2Col[draagChance] << "!" << endl;
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT DRAAG HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
        if (itemChoose == 2){
            cout << "You have chosen to use the Sapper!";
            p2Backpack[1]--;
            if (p1Backpack[5] > 0){
                cout << endl;
                cout << "P1: You have " << p1Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                cout << "Your opponent's next guess will give information about your code!" << endl;
                p2SapperUsed = true;
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT SAPPER HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
        if (itemChoose == 3){
            cout << "You have chosen to use a stick of D.D. Dynamite!";
            p2Backpack[2]--;
            if (p1Backpack[5] > 0){
                cout << endl;
                cout << "P1: You have " << p1Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                cout <<  "Your opponent's code has been scrambled!" << endl;
                p1Col = addCol();
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT DYNAMITE HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
        if (itemChoose == 4){
            cout << "You have chosen to use an Acme box!";
            p2Backpack[3]--;
            if (p1Backpack[5] > 0){
                cout << endl;
                cout << "P1: You have " << p1Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                int acmeChance = randInt(1, 2);
                if (acmeChance == 1){
                    cout << " WUH OH! Looks like Bugs Bunny made you have a bad hare day (get it?). Your turn has been skipped so you can emotionally recover." << endl;
                    p2BugsBunny = true;
                }
                if (acmeChance == 2){
                    cout << " Lucky you! Bugs Bunny dropped an anvil on your opponent's toe. Their next turn has been skipped!" << endl;
                    p1BugsBunny = true;
                }
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT ACME BOX HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
        if (itemChoose == 5){
            cout << "You have chosen to use the blink gun! Both you and your opponent's codes have been shortened by one peg!" << endl;
            p2Backpack[4]--;
            if (p1Backpack[5] > 0){
                cout << endl;
                cout << "P1: You have " << p1Backpack[5] << " Showstoppers!";
                showstop = readInt(" Please enter 1 to use one or 0 to not: ", "Enter 1 to use one or 0 to not: ");
            }
            if (showstop == 0){
                p1Col.pop_back();
                p2Col.pop_back();
                pegNum --;
            }
            else{
                int adj = randInt(0, 6);
                cout << "OOOHHH! AND THAT BLINK GUN HAS BEEN " << adjectives[adj] << " THE EFFECTS HAVE BEEN NEGATED!!!" << endl;
                showstop = 0;
            }
        }
    }
}

void p1BeatEmUp(){
    cout << "1 - Jab - PowerCost/DMG = 2" << endl;
    cout << "2 - Hook - PowerCost/DMG = 3" << endl;
    cout << "3 - Kick - PowerCost/DMG = 5" << endl;
    int p1Move = readInt(1, 3, "Choose a move to use: ", "Choose a move to use: ");
    while (p1Power < powerIndex[p1Move - 1]){
        p1Move = readInt(1, 3, "You do not have enough power. Please choose a different move: ", "You do not have enough power. Please choose a different move: ");
    }
    if (p1Move == 1){
        p1Power = p1Power - 2;
        if (p1Power >= 3){
            int combo2 = readInt(0, 1, "Would you like to combo a hook? (1 = Yes 0 = No) ", "Would you like to combo a hook? (1 = Yes 0 = No) ");
            if (combo2 == 1){
                p1Power = p1Power - 3;
                if (p1Power >= 5){
                    int combo3 = readInt(0, 1, "Would you like to finish the combo with a kick? (1 = Yes 0 = No) ", "Would you like to finish the combo with a kick? (1 = Yes 0 = No) ");
                    if (combo3 == 1){
                        p1Power = p1Power - 5;
                        if (p2Power >= 15){
                            cout << "P1 is about to full combo P2!" << endl;
                            int blockCombo3 = readInt(0, 1, "P2: Would you like to block this attack? (1 = Yes 0 = No) ", "P2: Would you like to block this attack? (1 = Yes 0 = No) ");
                            if (blockCombo3 == 0){
                                p2HP = p2HP - 10;
                                cout << "You full comboed your opponent! They have " << p2HP << " HP left!" << endl;
                                cout << "You have " << p1Power << " power left." << endl;
                            }
                            else{
                                p2Power = p2Power - 15;
                                cout << "P2 has blocked the attack!" << endl;
                                cout << "P2 has " << p2Power << " power left!" << endl;
                                cout << "P1 has " << p1Power << " power left!" << endl;
                            }
                        }
                        else{
                            p2HP = p2HP - 10;
                            cout << "You full comboed your opponent! They have " << p2HP << " HP left!" << endl;
                            cout << "You have " << p1Power << " power left." << endl;
                        }
                    }
                    else{
                        if (p2Power >= 5){
                            cout << "P1 is about to jab-hook P2!" << endl;
                            int blockCombo2 = readInt(0, 1, "P2: Would you like to block this attack? (1 = Yes 0 = No) ", "P2: Would you like to block this attack? (1 = Yes 0 = No) ");
                            if (blockCombo2 == 0){
                                p2HP = p2HP - 5;
                                cout << "You jab-hooked your opponent! They have " << p2HP << " HP left!" << endl;
                                cout << "You have " << p1Power << " power left." << endl;
                            }
                            else{
                                p2Power = p2Power - 5;
                                cout << "P2 has blocked the attack!" << endl;
                                cout << "P2 has " << p2Power << " power left!" << endl;
                                cout << "P1 has " << p1Power << " power left!" << endl;
                            }
                        }
                        else{
                            p2HP = p2HP - 5;
                            cout << "You jab-hooked your opponent! They have " << p2HP << " HP left!" << endl;
                            cout << "You have " << p1Power << " power left." << endl;   
                        }
                    }
                }
                else{
                    if (p2Power >= 5){
                        cout << "P1 is about to jab-hook P2!" << endl;
                        int blockCombo21 = readInt(0, 1, "P2: Would you like to block this attack? (1 = Yes 0 = No) ", "P2: Would you like to block this attack? (1 = Yes 0 = No) ");
                        if (blockCombo21 == 0){
                            p2HP = p2HP - 5;
                            cout << "You jab-hooked your opponent! They have " << p2HP << " HP left!" << endl;
                            cout << "You have " << p1Power << " power left." << endl;
                        }
                        else{
                            p2Power = p2Power - 5;
                            cout << "P2 has blocked the attack!" << endl;
                            cout << "P2 has " << p2Power << " power left!" << endl;
                            cout << "P1 has " << p1Power << " power left!" << endl;
                        }
                    }
                    else{
                        p2HP = p2HP - 5;
                        cout << "You jab-hooked your opponent! They have " << p2HP << " HP left!" << endl;
                        cout << "You have " << p1Power << " power left." << endl;
                    }
                }
            }
            else{
                if (p2Power >= 2){
                    cout << "P1 is about to jab P2!" << endl;
                    int blockJab = readInt(0, 1, "P2: Would you like to block this attack? (1 = Yes 0 = No) ", "P2: Would you like to block this attack? (1 = Yes 0 = No) ");
                    if (blockJab == 0){
                        p2HP = p2HP - 2;
                        cout << "You jabbed your opponent! They have " << p2HP << " HP left!" << endl;
                        cout << "You have " << p1Power << " power left." << endl;
                    }
                    else{
                        p2Power = p2Power - 2;
                        cout << "P2 has blocked the attack!" << endl;
                        cout << "P2 has " << p2Power << " power left!" << endl;
                        cout << "P1 has " << p1Power << " power left!" << endl;
                    }
                }
                else{
                    p2HP = p2HP - 2;
                    cout << "You jabbed your opponent! They have " << p2HP << " HP left!" << endl;
                    cout << "You have " << p1Power << " power left." << endl;
                }
            }
        }
        else{
            if (p2Power >= 2){
                cout << "P1 is about to jab P2!" << endl;
                int blockJab2 = readInt(0, 1, "P2: Would you like to block this attack? (1 = Yes 0 = No) ", "P2: Would you like to block this attack? (1 = Yes 0 = No) ");
                if (blockJab2 == 0){
                    p2HP = p2HP - 2;
                    cout << "You jabbed your opponent! They have " << p2HP << " HP left!" << endl;
                    cout << "You have " << p1Power << " power left." << endl;
                }
                else{
                    p2Power = p2Power - 2;
                    cout << "P2 has blocked the attack!" << endl;
                    cout << "P2 has " << p2Power << " power left!" << endl;
                    cout << "P1 has " << p1Power << " power left!" << endl;
                }
            }
            else{
                p2HP = p2HP - 2;
                cout << "You jabbed your opponent! They have " << p2HP << " HP left!" << endl;
                cout << "You have " << p1Power << " power left." << endl;
            }
        }
    }
    else if (p1Move == 2){
        p1Power = p1Power - 3;
        if (p2Power >= 3){
            cout << "P1 is about to hook P2!" << endl;
            int blockHook = readInt(0, 1, "P2: Would you like to block this attack? (1 = Yes 0 = No) ", "P2: Would you like to block this attack? (1 = Yes 0 = No) ");
            if (blockHook == 0){
                p2HP = p2HP - 3;
                cout << "You hooked your opponent! They have " << p2HP << " HP left!" << endl;
                cout << "You have " << p1Power << " power left." << endl;
            }
            else{
                p2Power = p2Power - 3;
                cout << "P2 has blocked the attack!" << endl;
                cout << "P2 has " << p2Power << " power left!" << endl;
                cout << "P1 has " << p1Power << " power left!" << endl;
            }
        }
        else{
            p2HP = p2HP - 3;
            cout << "You hooked your opponent! They have " << p2HP << " HP left!" << endl;
            cout << "You have " << p1Power << " power left." << endl;
        }
    }
    else if (p1Move == 3){
        p1Power = p1Power - 5;
        if (p2Power >= 5){
            cout << "P1 is about to kick P2!" << endl;
            int blockKick = readInt(0, 1, "P2: Would you like to block this attack? (1 = Yes 0 = No) ", "P2: Would you like to block this attack? (1 = Yes 0 = No) ");
            if (blockKick == 0){
                p2HP = p2HP - 5;
                cout << "You kicked your opponent! They have " << p2HP << " HP left!" << endl;
                cout << "You have " << p1Power << " power left." << endl;
            }
            else{
                p2Power = p2Power - 5;
                cout << "P2 has blocked the attack!" << endl;
                cout << "P2 has " << p2Power << " power left!" << endl;
                cout << "P1 has " << p1Power << " power left!" << endl;
            }
        }
        else{
            p2HP = p2HP - 5;
            cout << "You kicked your opponent! They have " << p2HP << " HP left!" << endl;
            cout << "You have " << p1Power << " power left." << endl;
        }
    }
}

void p2BeatEmUp(){
    cout << "1 - Jab - PowerCost/DMG = 2" << endl;
    cout << "2 - Hook - PowerCost/DMG = 3" << endl;
    cout << "3 - Kick - PowerCost/DMG = 5" << endl;
    int p2Move = readInt(1, 3, "Choose a move to use: ", "Choose a move to use: ");
    while (p2Power < powerIndex[p2Move - 1]){
        p2Move = readInt(1, 3, "You do not have enough power. Please choose a different move: ", "You do not have enough power. Please choose a different move: ");
    }
    if (p2Move == 1){
        p2Power = p2Power - 2;
        if (p2Power >= 3){
            int p2Combo2 = readInt(0, 1, "Would you like to combo a hook? (1 = Yes 0 = No) ", "Would you like to combo a hook? (1 = Yes 0 = No) ");
            if (p2Combo2 == 1){
                p2Power = p2Power - 3;
                if (p2Power >= 5){
                    int p2Combo3 = readInt(0, 1, "Would you like to finish the combo with a kick? (1 = Yes 0 = No) ", "Would you like to finish the combo with a kick? (1 = Yes 0 = No) ");
                    if (p2Combo3 == 1){
                        p2Power = p2Power - 5;
                        if (p1Power >= 15){
                            cout << "P2 is about to full combo P1!" << endl;
                            int p1BlockCombo3 = readInt(0, 1, "P1: Would you like to block this attack? (1 = Yes 0 = No) ", "P1: Would you like to block this attack? (1 = Yes 0 = No) ");
                            if (p1BlockCombo3 == 0){
                                p1HP = p1HP - 10;
                                cout << "You full comboed your opponent! They have " << p1HP << " HP left!" << endl;
                                cout << "You have " << p2Power << " power left." << endl;
                            }
                            else{
                                p1Power = p1Power - 15;
                                cout << "P1 has blocked the attack!" << endl;
                                cout << "P1 has " << p1Power << " power left!" << endl;
                                cout << "P2 has " << p2Power << " power left!" << endl;
                            }
                        }
                        else{
                            p1HP = p1HP - 10;
                            cout << "You full comboed your opponent! They have " << p1HP << " HP left!" << endl;
                            cout << "You have " << p2Power << " power left." << endl;
                        }
                    }
                    else{
                        if (p1Power >= 5){
                            cout << "P2 is about to jab-hook P1!" << endl;
                            int p1BlockCombo2 = readInt(0, 1, "P1: Would you like to block this attack? (1 = Yes 0 = No) ", "P1: Would you like to block this attack? (1 = Yes 0 = No) ");
                            if (p1BlockCombo2 == 0){
                                p1HP = p1HP - 5;
                                cout << "You jab-hooked your opponent! They have " << p1HP << " HP left!" << endl;
                                cout << "You have " << p2Power << " power left." << endl;
                            }
                            else{
                                p1Power = p1Power - 5;
                                cout << "P1 has blocked the attack!" << endl;
                                cout << "P1 has " << p1Power << " power left!" << endl;
                                cout << "P2 has " << p2Power << " power left!" << endl;
                            }
                        }
                        else{
                            p1HP = p1HP - 5;
                            cout << "You jab-hooked your opponent! They have " << p1HP << " HP left!" << endl;
                            cout << "You have " << p2Power << " power left." << endl;
                        }
                    }
                }
                else{
                    if (p1Power >= 5){
                        cout << "P2 is about to jab-hook P1!" << endl;
                        int p1BlockCombo21 = readInt(0, 1, "P1: Would you like to block this attack? (1 = Yes 0 = No) ", "P1: Would you like to block this attack? (1 = Yes 0 = No) ");
                        if (p1BlockCombo21 == 0){
                            p2HP = p2HP - 5;
                            cout << "You jab-hooked your opponent! They have " << p1HP << " HP left!" << endl;
                            cout << "You have " << p2Power << " power left." << endl;
                        }
                        else{
                            p1Power = p1Power - 5;
                            cout << "P1 has blocked the attack!" << endl;
                            cout << "P1 has " << p1Power << " power left!" << endl;
                            cout << "P2 has " << p2Power << " power left!" << endl;
                        }
                    }
                    else{
                        p2HP = p2HP - 5;
                        cout << "You jab-hooked your opponent! They have " << p1HP << " HP left!" << endl;
                        cout << "You have " << p2Power << " power left." << endl;
                    }
                }
            }
            else{
                if (p1Power >= 2){
                    cout << "P2 is about to jab P1!" << endl;
                    int blockJab = readInt(0, 1, "P1: Would you like to block this attack? (1 = Yes 0 = No) ", "P1: Would you like to block this attack? (1 = Yes 0 = No) ");
                    if (blockJab == 0){
                        p1HP = p1HP - 2;
                        cout << "You jabbed your opponent! They have " << p1HP << " HP left!" << endl;
                        cout << "You have " << p2Power << " power left." << endl;
                    }
                    else{
                        p1Power = p1Power - 2;
                        cout << "P1 has blocked the attack!" << endl;
                        cout << "P1 has " << p1Power << " power left!" << endl;
                        cout << "P2 has " << p2Power << " power left!" << endl;
                    }
                }
                else{
                    p1HP = p1HP - 2;
                    cout << "You jabbed your opponent! They have " << p1HP << " HP left!" << endl;
                    cout << "You have " << p2Power << " power left." << endl;
                }
            }
        }
        else{
            if (p1Power >= 2){
                cout << "P2 is about to jab P1!" << endl;
                int blockJab1 = readInt(0, 1, "P1: Would you like to block this attack? (1 = Yes 0 = No) ", "P1: Would you like to block this attack? (1 = Yes 0 = No) ");
                if (blockJab1 == 0){
                    p1HP = p1HP - 2;
                    cout << "You jabbed your opponent! They have " << p1HP << " HP left!" << endl;
                    cout << "You have " << p2Power << " power left." << endl;
                }
                else{
                    p1Power = p1Power - 2;
                    cout << "P1 has blocked the attack!" << endl;
                    cout << "P1 has " << p1Power << " power left!" << endl;
                    cout << "P2 has " << p2Power << " power left!" << endl;
                }
            }
            else{
                p1HP = p1HP - 2;
                cout << "You jabbed your opponent! They have " << p1HP << " HP left!" << endl;
                cout << "You have " << p2Power << " power left." << endl;
            }
        }
    }
    else if (p2Move == 2){
        p2Power = p2Power - 3;
        if (p1Power >= 3){
            cout << "P2 is about to hook P1!";
            int blockHook = readInt(0, 1, "P1: Would you like to block this attack? (1 = Yes 0 = No) ", "P1: Would you like to block this attack? (1 = Yes 0 = No) ");
            if (blockHook == 0){
                p1HP = p1HP - 3;
                cout << "You hooked your opponent! They have " << p1HP << " HP left!" << endl;
                cout << "You have " << p2Power << " power left." << endl;
            }
            else{
                p1Power = p1Power - 3;
                cout << "P1 has blocked the attack!" << endl;
                cout << "P1 has " << p1Power << " power left!" << endl;
                cout << "P2 has " << p2Power << " power left!" << endl;
            }
        }
        else{
            p1HP = p1HP - 3;
            cout << "You hooked your opponent! They have " << p1HP << " HP left!" << endl;
            cout << "You have " << p2Power << " power left." << endl;
        }
    }
    else if (p2Move == 3){
        p2Power = p2Power - 5;
        if (p1Power >= 5){
            cout << "P2 is about to kick P1!";
            int blockKick = readInt(0, 1, "P1: Would you like to block this attack? (1 = Yes 0 = No) ", "P1: Would you like to block this attack? (1 = Yes 0 = No) ");
            if (blockKick == 0){
                p1HP = p1HP - 5;
                cout << "You kicked your opponent! They have " << p1HP << " HP left!" << endl;
                cout << "You have " << p2Power << " power left." << endl;
            }
            else{
                p2Power = p2Power - 5;
                cout << "P1 has blocked the attack!" << endl;
                cout << "P1 has " << p1Power << " power left!" << endl;
                cout << "P2 has " << p2Power << " power left!" << endl;
            }
        }
        else{
            p1HP = p1HP - 5;
            cout << "You kicked your opponent! They have " << p1HP << " HP left!" << endl;
            cout << "You have " << p2Power << " power left." << endl;
        }
    }
}

void multiGuess (vector<int> p1Col, vector<int> p2Col){
    vector<int> p1Guesses;
    vector<int> p2Guesses;
    for (int m = 1; m <= 1; m++){
        if (backpackerings == true){
            p1Items();
        }
        if (p1BugsBunny == true){
            break;
        }
        for (int y = 1; y <= pegNum; y++){
            cout << "P1: Please enter the color for peg " << y;
            int p1Guess = readInt(": ");
            while (p1Guess < 0 || p1Guess > colorNum){
                cout << "P1: Please enter the color for peg " << y;
                p1Guess = readInt(": ");
            }
            p1Guesses.push_back(p1Guess);
        }
        if (p2SapperUsed == true){
            p1CorrectAndPlaced = correctSpot(p1Guesses, p2Col);
            p1CorrectTotal = correctOverall(p1Guesses, p2Col);
            p2SapperUsed = false;
        }
        else{
            p1CorrectAndPlaced = correctSpot(p1Guesses, p1Col);
            p1CorrectTotal = correctOverall(p1Guesses, p1Col);
        }
        for (int a = 0; a < pegNum; a++){
            if (p1Guesses[a] == p1Col[a]){
                p1correctCount ++;
            }
            p1totalCount ++;
        }
        if (p1correctCount == p1totalCount){
            cout << "Player 1 Wins! They took " << p1Moves + 1 << " turns!" << endl;
            winner = true;
            break;
        }
    }
    if (p1BugsBunny == false && winner == false){
            cout << "You have " << p1CorrectAndPlaced << " peg/pegs correct and " << p1CorrectTotal - p1CorrectAndPlaced << " color/colors correct, but in the wrong place." << endl;
        }
    if (winner == false && streetFighterStyle == true){
        p1Power = p1Power + p1CorrectAndPlaced + (p1CorrectTotal - p1CorrectAndPlaced) / 2;
        cout << "P1 has " << p1Power << " power." << endl;
        if (p1Power >= 2){
            int battleAsk = readInt(0, 1, "Would you like to battle? (1 = Yes 0 = No): ", "Would you like to battle? (1 = Yes 0 = No): ");
            if (battleAsk == 1){
                p1BeatEmUp();
            }
            if (p2HP <= 0){
                winner = true;
                cout << "Player 1 Wins! They won by beat down!" << endl;
            }
        }
    }
    if (winner == false && p2HP > 0){
        p1Moves++;
        p1CorrectAndPlaced = 0;
        p1CorrectTotal = 0;
        p1BugsBunny = false;
        p1ItemCounter++;
        p1totalCount = 0;
        p1correctCount = 0;
        veryGood = 0;
        partiallyGood = 0;
        p1ItemTot = 0;
        for (int b = 1; b <= pegNum; b++){
            p1Guesses.pop_back();
        }
    }
    for (int m = 1; m <= 1; m++){
        if (winner == true){
            break;
        }
        if (backpackerings == true){
            p2Items();
        }
        if (p2BugsBunny == true){
            break;
        }
        for (int x = 1; x <= pegNum; x++){
            cout << "P2: Please enter the color for peg " << x;
            int p2Guess = readInt(": ");
            while (p2Guess < 0 || p2Guess > colorNum){
                cout << "P2: Please enter the color for peg " << x;
                p2Guess = readInt(": ");
            }
            p2Guesses.push_back(p2Guess);
        }
        if (p1SapperUsed == true){
            p2CorrectAndPlaced = correctSpot(p2Guesses, p1Col);
            p2CorrectTotal = correctOverall(p2Guesses, p1Col);
            p1SapperUsed = false;
        }
        else{
            p2CorrectAndPlaced = correctSpot(p2Guesses, p2Col);
            p2CorrectTotal = correctOverall(p2Guesses, p2Col);
        }
        for (int a = 0; a < pegNum; a++){
            if (p2Guesses[a] == p2Col[a]){
                p2correctCount ++;
            }
            p2totalCount ++;
        }
        if (p2correctCount == p2totalCount){
            cout << "Player 2 Wins! They took " << p2Moves + 1 << " turns!" << endl;
            winner = true;
            break;
        }
    }
    if (p2BugsBunny == false && winner == false){
        cout << "You have " << p2CorrectAndPlaced << " peg/pegs correct and " << p2CorrectTotal - p2CorrectAndPlaced << " color/colors correct, but in the wrong place." << endl;
    }
    if (winner == false && streetFighterStyle == true){
        p2Power = p2Power + p2CorrectAndPlaced + (p2CorrectTotal - p2CorrectAndPlaced) / 2;
        cout << "P2 has " << p2Power << " power." << endl;
        if (p2Power >= 2){
            int p2BattleAsk = readInt(0, 1, "Would you like to battle? (1 = Yes 0 = No): ", "Would you like to battle? (1 = Yes 0 = No): ");
            if (p2BattleAsk == 1){
                p2BeatEmUp();
            }
            if (p1HP <= 0){
                winner = true;
                cout << "Player 2 Wins! They won by beat down!" << endl;
            }
        }
    }
    if (winner == false && p1HP > 0){
        p2Moves ++;
        p2CorrectAndPlaced = 0;
        p2CorrectTotal = 0;
        p2BugsBunny = false;
        p2ItemCounter++;
        p2totalCount = 0;
        p2correctCount = 0;
        veryGood = 0;
        partiallyGood = 0;
        p2ItemTot = 0;
        for (int b = 1; b <= pegNum; b++){
            p2Guesses.pop_back();
        }
    }
}

int main()
{
    int multiplayerAsk = readInt(0, 1, "Would you like to play against a person? (1 = Yes 0 = No): ", "Would you like to play against a person? (1 = Yes 0 = No): ");
    if (multiplayerAsk == 1){
        multiplayer = true;
        int streetFighterAsk = readInt(0, 1, "Would you like to play street fighter style? (1 = Yes 0 = No): ", "Would you like to play street fighter style? (1 = Yes 0 = No): ");
        if (streetFighterAsk == 1){
            streetFighterStyle = true;
        }
        int backpackAsk = readInt(0, 1, "Would you like to play with items? (1 = Yes 0 = No): ", "Would you like to play with items? (1 = Yes 0 = No): ");
        if (backpackAsk == 1){
            backpackerings = true;
        }
    }
    if (streetFighterStyle == false){
        pegNum = readInt(1, 8, "Please select the number of pegs (1-8): ", "Please select the number of pegs (1-8): ");
        colorNum = readInt(pegNum, 8, "Please select the number of colors (the number of pegs - 8): ", "Please select the number of colors (the number of pegs - 8): ");
    }
    if (multiplayer == false){
        vector<int> colors = addCol();
        guess(colors);
    }
    if (multiplayer == true && streetFighterStyle == false){
        p2Col = findP2();
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl<< endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        p1Col = findP1();
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl<< endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        while (winner == false){
            multiGuess(p1Col, p2Col);
        }
    }
    if (streetFighterStyle == true && multiplayer == true){
        pegNum = 5;
        colorNum = 5;
        SFP1Col = addCol();
        SFP2Col = addCol();
        while (winner == false){
            multiGuess(SFP1Col, SFP2Col);
        }
    }
    return 0;
}