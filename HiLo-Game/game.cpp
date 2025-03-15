#include "util.h"
using namespace std;

int cheeseCredit = 10;
int coins = 100;
bool reallyScummyDealer = false;
bool partiallyScummyDealer = false;
bool gang = false;
bool sideHustle = false;

void printWin(int answer){
    cout << "The number is " << answer << endl;
    cout << "You win!" << endl;
    cout << endl;
}

void printLoss(int answer){
    cout << "The number is " << answer << endl;
    cout << "You Lost!" << endl;
    cout << endl;
}

string randNum(int answer){
    if (answer <= 6){
        return "LO";
    }
    else if (answer == 7){
        return "MID";
    }
    else{
        return "HI";
    }
}

string getGuess(int wager, int coins){
    cout << "Enter LO to guess numbers 1-6" << endl;
    cout << "Enter HI to guess numbers 8-13" << endl;
    string guess = "";
    while(guess == ""){
        guess = readLine("Your guess: ");
    }
    return guess;
}

void gameTime(string guess, string correct, int answer, int wager){
    
    if (guess == correct){
        coins += wager;
        printWin(answer);
    }
    else{
        coins -= wager;
        printLoss(answer);
    }
}

void reallyScummyTime(string guess, string correct, int answer, int wager){
    if(guess == correct && correct == "HI"){
        answer = randInt(1, 6);
        coins -= wager;
        printLoss(answer);
    }
    else if (guess == correct && correct == "LO"){
        answer = randInt(8, 13);
        coins -= wager;
        printLoss(answer);
    }
    else{
        coins -= wager;
        printLoss(answer);
    }
}

void bigGunMod(string gun, string guess, string correct, int answer, int wager, int chance){
    if (chance == 3 && gun == "F"){
        coins += (2 * wager);
        cout << "You shot the dealer and he was a known cheater. The police thank you and double your wager and adds it right to your bank!" << endl;
        cout << endl;
    }
    else{
        coins -= 200;
        cout << "You shot the dealer and he innocent. The police fine you for 200 coins." << endl;
        cout << endl;
    }
}

void partiallyScummyTime(string guess, string correct, int answer, int wager){
    int chance = randInt(1, 3);
    string gun = readLine("Click F and enter to shoot gun. Click anything else and enter to not shoot gun. ");
    if (chance == 3 && gun != "F"){
        reallyScummyTime(guess, correct, answer, wager);
    }
    else if (chance != 3 && gun != "F"){
        gameTime(guess, correct, answer, wager);
    }
    else{
        bigGunMod(gun, guess, correct, answer, wager, chance);
    }
}

void scummyGangTime(string guess, string correct, int answer, int wager){
    int gChance = randInt(1, 2);
    if (gChance == 2){
        int pNum = readInt(1, 2, "A gang challenges you to a game. Guess their number and nothing will happen. Guess wrong and there will be consequences... Guess 1 or 2: ", "Guess 1 or 2: ");
        int gNum = randInt(1, 2);
        if (pNum == gNum){
            cout << "The number was " << gNum << endl;
            cout << "You guessed the number! Continue on!" << endl;
            cout << endl;
        }
        else{
            cout << "The number was " << gNum << endl;
            cout << "You guessed wrong. You now loose double the amount you wagered." << endl;
            coins -= (wager * 2);
            cout << endl;
        }
    }
    else{
        partiallyScummyTime(guess, correct, answer, wager);
    }
}

void chillGangTime(string guess, string correct, int answer, int wager){
    int gChance = randInt(1, 2);
    if (gChance == 2){
        int pNum = readInt(1, 2, "A gang challenges you to a game. Guess their number and nothing will happen. Guess wrong and there will be consequences... Guess 1 or 2: ", "Guess 1 or 2: ");
        int gNum = randInt(1, 2);
        if (pNum == gNum){
            cout << "The number was " << gNum << endl;
            cout << "You guessed the number! Continue on!" << endl;
            cout << endl;
        }
        else{
            cout << "The number was " << gNum << endl;
            cout << "You guessed wrong. You now loose double the amount you wagered." << endl;
            coins -= (wager * 2);
            cout << endl;
        }
    }
    else{
        gameTime(guess, correct, answer, wager);
    }
}

void chillSideHustle(string guess, string correct, int answer, int wager){
    int Cchance = randInt(1, 3);
    if (Cchance == 2){
        cout << "Your illegal cheese manufacturing company has made " << cheeseCredit << " coins for you!" << endl;
        string invest = readLine("Would you like to invest 10 coins to double productin speeds? Click F and enter for yes, or click something else and enter for no: ");
        if (invest == "F"){
            coins += cheeseCredit;
            coins -= 10;
            cheeseCredit *= 2;
            cout << endl;
        }
        else{
            coins += cheeseCredit;
            gameTime(guess, correct, answer, wager);
        }
    }
    else if(Cchance == 3){
        cout << "OH NO! The Beetroot company has discombobulated the internal cheese matrix and blew up the cheese liquidizer!" << endl;
        string uhOh = readLine("You need to invest 100 coins, or else your company will have to restart! Click F and enter to do it, or click something else and enter to not do it: ");
        if (uhOh == "F"){
            coins -= 100;
            cout << endl;
        }
        else{
            cheeseCredit = 10;
            gameTime(guess, correct, answer, wager);
        }
    }
    else{
        gameTime(guess, correct, answer, wager);
    }
}

void scummyGangSideHustle(string guess, string correct, int answer, int wager){
    int Cchance = randInt(1, 3);
    if (Cchance == 2){
        cout << "Your illegal cheese manufacturing company has made " << cheeseCredit << " coins for you!" << endl;
        string invest = readLine("Would you like to invest 10 coins to double productin speeds? Click F and enter for yes, or click something else and enter for no: ");
        if (invest == "F"){
            coins += cheeseCredit;
            coins -= 10;
            cheeseCredit *= 2;
            cout << endl;
        }
        else{
            coins += cheeseCredit;
            scummyGangTime(guess, correct, answer, wager);
        }
    }
    else if(Cchance == 3){
        cout << "OH NO! The Beetroot company has discombobulated the internal cheese matrix and blew up the cheese liquidizer!" << endl;
        string uhOh = readLine("You need to invest 100 coins, or else your company will have to restart! Click F and enter to do it, or click something else and enter to not do it: ");
        if (uhOh == "F"){
            coins -= 100;
            cout << endl;
        }
        else{
            cheeseCredit = 10;
            scummyGangTime(guess, correct, answer, wager);
        }
    }
    else{
        scummyGangTime(guess, correct, answer, wager);
    }
}

void scummySideHustle(string guess, string correct, int answer, int wager){
    int Cchance = randInt(1, 3);
    if (Cchance == 2){
        cout << "Your illegal cheese manufacturing company has made " << cheeseCredit << " coins for you!" << endl;
        string invest = readLine("Would you like to invest 10 coins to double productin speeds? Click F and enter for yes, or click something else and enter for no: ");
        if (invest == "F"){
            coins += cheeseCredit;
            coins -= 10;
            cheeseCredit *= 2;
            cout << endl;
        }
        else{
            coins += cheeseCredit;
            partiallyScummyTime(guess, correct, answer, wager);
        }
    }
    else if(Cchance == 3){
        cout << "OH NO! The Beetroot company has discombobulated the internal cheese matrix and blew up the cheese liquidizer!" << endl;
        string uhOh = readLine("You need to invest 100 coins, or else your company will have to restart! Click F and enter to do it, or click something else and enter to not do it: ");
        if (uhOh == "F"){
            coins -= 100;
            cout << endl;
        }
        else{
            cheeseCredit = 10;
            partiallyScummyTime(guess, correct, answer, wager);
        }
    }
    else{
        partiallyScummyTime(guess, correct, answer, wager);
    }
}

void gangSideHustle(string guess, string correct, int answer, int wager){
    int Cchance = randInt(1, 3);
    if (Cchance == 2){
        cout << "Your illegal cheese manufacturing company has made " << cheeseCredit << " coins for you!" << endl;
        string invest = readLine("Would you like to invest 10 coins to double productin speeds? Click F and enter for yes, or click something else and enter for no: ");
        if (invest == "F"){
            coins += cheeseCredit;
            coins -= 10;
            cheeseCredit *= 2;
            cout << endl;
        }
        else{
            coins += cheeseCredit;
            chillGangTime(guess, correct, answer, wager);
        }
    }
    else if(Cchance == 3){
        cout << "OH NO! The Beetroot company has discombobulated the internal cheese matrix and blew up the cheese liquidizer!" << endl;
        string uhOh = readLine("You need to invest 100 coins, or else your company will have to restart! Click F and enter to do it, or click something else and enter to not do it: ");
        if (uhOh == "F"){
            coins -= 100;
            cout << endl;
        }
        else{
            cheeseCredit = 10;
            chillGangTime(guess, correct, answer, wager);
        }
    }
    else{
        chillGangTime(guess, correct, answer, wager);
    }
}

int main(){
    int scumMod = readInt(0, 1, "Would you like to play with the really scummy mod? Click 1 for yes and 0 for no: ", "Click 1 for yes and 0 for no: ");
    if (scumMod == 0){
        int parScumMod = readInt(0, 1, "Would you like to play with the partially scummy/ big gun mod? Click 1 for yes and 0 for no: ", "Click 1 for yes and 0 for no: ");
        if (parScumMod == 1){
            partiallyScummyDealer = true;
        }
        int gangMod = readInt(0, 1, "Would you like to play with the gang mod? Click 1 for yes and 0 for no: ", "Click 1 for yes and 0 for no: ");
        if (gangMod == 1){
            gang = true;
        }
        int sideMod = readInt(0, 1, "Would you like to play with the side hustle mod? Click 1 for yes and 0 for no: ", "Click 1 for yes and 0 for no: ");
        if (sideMod == 1){
            sideHustle = true;
        }
    }
    else{
        reallyScummyDealer = true;
    }
    
    while (coins > 0){
        cout << "You have " << coins << " coins." << endl;
        int wager = readInt(1, coins, "How much would you like to wager? ", "How much would you like to wager? ");
        int answer = randInt(1, 13);
        string guess = getGuess(wager, coins);
        string correct = randNum(answer);

        if (reallyScummyDealer){
            reallyScummyTime(guess, correct, answer, wager);
        }
        else if(partiallyScummyDealer == true && gang != true && sideHustle != true){
            partiallyScummyTime(guess, correct, answer, wager);
        }
        else if (partiallyScummyDealer == true && gang == true && sideHustle != true){
            scummyGangTime(guess, correct, answer, wager);
        }
        else if (partiallyScummyDealer != true && gang == true && sideHustle != true){
            chillGangTime(guess, correct, answer, wager);
        }
        else if(partiallyScummyDealer != true && gang != true && sideHustle == true){
            chillSideHustle(guess, correct, answer, wager);
        }
        else if(partiallyScummyDealer == true && gang == true && sideHustle == true){
            scummyGangSideHustle(guess, correct, answer, wager);
        }
        else if(partiallyScummyDealer == true && gang != true && sideHustle == true){
            scummySideHustle(guess, correct, answer, wager);
        }
        else if(partiallyScummyDealer != true && gang == true && sideHustle == true){
            gangSideHustle(guess, correct, answer, wager);
        }
        else{
            gameTime(guess, correct, answer, wager);
        }
    }
    
    cout << "Good Game! The House Always Wins!" << endl;
    
    return 0;
}