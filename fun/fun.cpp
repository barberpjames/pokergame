//Directory text files must be placed in the /directory relative directory

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctime>


////////////////////////////testing github
struct card{
    int value;
    char suite;
    bool dealt = false;
    bool discarded = false;
};
void initializeDeck(card deck[]);
void firstHand(card first[], card deck[]);
void printCards(card hand[]);
void askForHold(card first[], card deck[]);
void secondHand(card first[], card deck[]);
int checkIfWinner(card first[]);
bool checkPair(card first[]);
bool check3(card first[]);




using namespace std;
int main(int argc, char** argv){

    srand(time(NULL));
    card deck[54];
    initializeDeck(deck);
    card first[5];
    firstHand(first, deck);
    printCards(first);
    askForHold(first, deck);
    secondHand(first, deck);


    first[2].value = first[3].value = first[4].value = 5;
    printCards(first);





    //testing cases
    int check = checkIfWinner(first);

    cout << "\n\nHighest Hand: ";
    switch(check){
    case 0 :
        cout << "Nothing\n\n";
        break;
    case 1 :
        cout << "A Pair!!\n\n";
        break;
    case 2 :
        cout << "Three of a kind!!\n\n";
    }

/*    for(int i = 1; i < 53; i++){
        cout << deck[i].value << " " << deck[i].suite << " " << deck[i].dealt << endl;
    }*/








	return 0;
}



//This is the initialize deck function. It will initialize the
//deck with 52 cards, each with 1-13, S, D, H, C.
void initializeDeck(card deck[]){
    for(int i = 1; i < 53; i++){
        if(i < 14){
            deck[i].value = i;
            deck[i].suite = 'S';
        }
        else if(i >= 14 && i < 27){
            deck[i].value = i - 13;
            deck[i].suite = 'C';
        }
        else if(i >= 27 && i < 40){
            deck[i].value = i - 26;
            deck[i].suite = 'D';
        }
        else{
            deck[i].value = i - 39;
            deck[i].suite = 'H';
        }
    }
}

//This is the first hand function. It will keep pulling
//random cards from the deck until none of them are the same
//Receives an array of 5 elements and the card array
void firstHand(card first[], card deck[]){
/*    card c1, c2, c3, c4, c5;
    c1.value = 0;
    c2.value = 0;
    c3.value = 0;
    c4.value = 0;
    c5.value = 0;
    c1.suite = 'A';
    c2.suite = 'A';
    c3.suite = 'A';
    c4.suite = 'A';
    c5.suite = 'A';
    int randomForSelection1;
    int randomForSelection2;
    int randomForSelection3;
    int randomForSelection4;
    int randomForSelection5;

    while(((c1.value == c2.value) && (c1.suite == c2.suite)) ||
          ((c1.value == c3.value) && (c1.suite == c3.suite)) ||
          ((c1.value == c4.value) && (c1.suite == c4.suite)) ||
          ((c1.value == c5.value) && (c1.suite == c5.suite)) ||
          ((c2.value == c3.value) && (c2.suite == c3.suite)) ||
          ((c2.value == c4.value) && (c2.suite == c4.suite)) ||
          ((c2.value == c5.value) && (c2.suite == c5.suite)) ||
          ((c3.value == c4.value) && (c3.suite == c4.suite)) ||
          ((c3.value == c5.value) && (c3.suite == c5.suite)) ||
          ((c4.value == c5.value) && (c4.suite == c5.suite))){
        randomForSelection1 = rand() % 53;
        while(randomForSelection1 == 0)
            randomForSelection1 = rand() % 53;
        c1 = deck[randomForSelection1];
        randomForSelection2 = rand() % 53;
        while(randomForSelection2 == 0)
            randomForSelection2 = rand() % 53;
        c2 = deck[randomForSelection2];
        randomForSelection3 = rand() % 53;
        while(randomForSelection3 == 0)
            randomForSelection3 = rand() % 53;
        c3 = deck[randomForSelection3];
        randomForSelection4 = rand() % 53;
        while(randomForSelection4 == 0)
            randomForSelection4 = rand() % 53;
        c4 = deck[randomForSelection4];
        randomForSelection5 = rand() % 53;
        while(randomForSelection5 == 0)
            randomForSelection5 = rand() % 53;
        c5 = deck[randomForSelection5];
    }
    first[0].value = c1.value;
    first[1].value = c2.value;
    first[2].value = c3.value;
    first[3].value = c4.value;
    first[4].value = c5.value;
    first[0].suite = c1.suite;
    first[1].suite = c2.suite;
    first[2].suite = c3.suite;
    first[3].suite = c4.suite;
    first[4].suite = c5.suite;
    deck[randomForSelection1].dealt = true;
    deck[randomForSelection2].dealt = true;
    deck[randomForSelection3].dealt = true;
    deck[randomForSelection4].dealt = true;
    deck[randomForSelection5].dealt = true;*/
    card newCard;
    for(int i = 0; i < 5; i++){
        int randomForSelection = rand() % 53;
        while(randomForSelection == 0 || deck[randomForSelection].dealt == true)
            randomForSelection = rand() % 53;
        deck[randomForSelection].dealt = true;
        newCard = deck[randomForSelection];
        first[i].value = newCard.value;
        first[i].suite = newCard.suite;
    }
}

//Function to print out hand
void printCards(card hand[]){
        cout << endl << endl;
        for(int i = 0; i < 5; i++){
            cout << " CARD ";
            cout << (i + 1);
            cout.width(7);
            cout << left << ":";
        }
        cout << endl;
        cout << endl;
        cout << "----------" << "    " << "----------" << "    "
             << "----------" << "    " << "----------" << "    "
             << "----------" << endl;
        for(int i = 0; i < 5; i++){
            cout << "|      ";
            if(hand[i].value == 1){

                cout << "A";
            }
            else if(hand[i].value == 11){
                cout << "J";
            }
            else if(hand[i].value == 12){
                cout << "Q";
            }
            else if(hand[i].value == 13){
                cout << "K";
            }
            else
                cout << hand[i].value;
            if(hand[i].value == 10)
                cout << "|" << "    ";
            else
                cout << " |" << "    ";
        }
        cout << endl;
        /////////////////////end of first row/////////////////////////////
        for(int i = 0; i < 5; i++){
            cout << "|        |    ";
        }
        cout << endl;
        ////////////////////end of second row////////////////////////////
        for(int i = 0; i < 5; i++){
            if(hand[i].suite == 'D')
                cout << "|Diamond |    ";
            else if(hand[i].suite == 'C')
                cout << "|  Club  |    ";
            else if(hand[i].suite == 'H')
                cout << "|  Heart |    ";
            else if(hand[i].suite == 'S')
                cout << "|  Spade |    ";
        }
        cout << endl;
        ////////////////////end of third row///////////////////////////
        for(int i = 0; i < 5; i++){
            cout << "|        |    ";
        }
        cout << endl;
        /////////////////////end of fourth row/////////////////////////////
        for(int i = 0; i < 5; i++){
            cout << "|";
            if(hand[i].value == 1){

                cout << "A      ";
            }
            else if(hand[i].value == 11){
                cout << "J      ";
            }
            else if(hand[i].value == 12){
                cout << "Q      ";
            }
            else if(hand[i].value == 13){
                cout << "K      ";
            }
            else
                cout << hand[i].value << "      ";
            if(hand[i].value == 10)
                cout << "|" << "    ";
            else
                cout << " |" << "    ";
        }
        cout << endl;
        cout << "----------" << "    " << "----------" << "    "
             << "----------" << "    " << "----------" << "    "
             << "----------" << endl;
    cout << endl << endl << endl << endl;

        // ofstream output;
        // output.open("test.txt");
        // int largest = 0;
        // for(int i = 0; i < 100000; i++)
        // {
        //     int j = rand() % 1000000;
        //     if(largest < j)
        //         largest = j;
        //     output << j;
        //     output << endl;
        // }
}

//Function that asks if you would like to discard any cards
void askForHold(card first[], card deck[]){
    bool holding = false;//To determine if holding cards
    char willYouHold;//To determine if holding
    bool done = false;
    int numberDiscarded = 0;
    char cardNumber = 'A';//to hold card number or D
    int intToHoldCard;//to be able to subscript with the card number

    //Check to see if holding any cards
    while(holding == false){
        cout << "Would you like to discard any cards? Enter y or n: ";
        cin >> willYouHold;
        while(willYouHold != 'y' && willYouHold != 'n'){
            cout << endl << "You Must enter y or n: ";
            cin >> willYouHold;
        }



        if(willYouHold == 'y'){/////////////////////////Holding Cards
            holding = true;
            while(done == false && numberDiscarded != 5 && cardNumber != 'd'){
                cout << "Please enter card number to discard or d for done: ";
                cin >> cardNumber;
                if(cardNumber != 'd'){
                    intToHoldCard = cardNumber - '1';
                    while(first[intToHoldCard].discarded == true && cardNumber != 'd'){
                        cout << "\nYou already discarded this card!!!";
                        cout << "Enter card number or d for done: ";
                        cin >> cardNumber;
                        intToHoldCard = cardNumber - '1';
                    }
                    if(cardNumber != 'd'){
                        first[intToHoldCard].discarded = true;
                        numberDiscarded++;
                    }
                }
                else if(cardNumber == 'd')
                    done = true;
            }
            cout << "You have chosen to discard cards: " << endl;
            for(int i = 0; i < 5; i++){
                if(first[i].discarded == true)
                    cout << i + 1<< " ";
            }
            cout << endl;
            cout << "Would you like to change your mind? y or N: ";
            char changeMind = 'A';
            cin >> changeMind;
            while(changeMind != 'y' && changeMind != 'n'){
                cout << endl << "You Must enter y or n: ";
                cin >> changeMind;
            }
            if(changeMind == 'Y'){
                for(int i = 0; i < 5; i++){
                    first[i].discarded = false;
                }
                numberDiscarded = 0;
                holding = false;
                cardNumber = 'A';
                done = false;
            }
        }
        else/////////////////////////////////////////////////Not holding cards
            holding = true;
    }
}

//Function that will check for discarded cards, and deal new ones when appropriate
void secondHand(card first[], card deck[]){
    card newCard;
    for(int i = 0; i < 5; i++){
        if(first[i].discarded == true){
            int randomForSelection = rand() % 53;
            while(randomForSelection == 0 || deck[randomForSelection].dealt == true)
                randomForSelection = rand() % 53;
            deck[randomForSelection].dealt = true;
            newCard = deck[randomForSelection];
            first[i].value = newCard.value;
            first[i].suite = newCard.suite;
        }
    }
}

/*This function will return an int corresponding to the following winning hands:
0 Nothing
1 pair
2 3 of a kind
3 2 pairs
4 straight
5 flush
6 full house
7 4oak
8 straight flush
9 royal flush*/
int checkIfWinner(card first[]){
    int holder = 0;
    if(checkPair(first) == true){
        holder = 1;
    }
    if(check3(first) == true){
        holder = 2;
    }
    return holder;
}

//This function checks for a pair
bool checkPair(card first[]){
    for(int i = 1; i < 5; i++){
        if(first[0].value == first[i].value)
            return true;
    }
    for(int i = 2; i < 5; i++){
        if(first[1].value == first[i].value)
            return true;
    }
    for(int i = 3; i < 5; i++){
        if(first[2].value == first[i].value)
            return true;
    }
    if(first[3].value == first[4].value)
        return true;
    return false;
 }

//This function checks for 3 of a kind
bool check3(card first[]){
    for(int i = 1; i < 5; i++){
        if(first[0].value == first[i].value)
            if(i < 4)
                for(int j = (i + 1); j < 5; j++)
                    if(first[j].value == first[0].value)
                        return true;

    }
    for(int i = 2; i < 5; i++){
        if(first[1].value == first[i].value)
            if(i < 4)
                for(int j = (i + 1); j < 5; j++)
                    if(first[j].value == first[1].value)
                        return true;

    }
    if(first[2].value == first[3].value && first[3].value == first[4].value)
        return true;
    return false;
}
