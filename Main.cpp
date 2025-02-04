//Arnold Rocha


#include <iostream>

using namespace std;

//Card Class
class Card { 

public:
  // Constructors
  Card(string s, string r, int v) : suit(s), rank(r), value(v) {}
  
  // Empty Intialization  
  Card( ) : suit(""), rank(""), value(0) {}


  /* Class Function - print_card
    Input: NONE 
    Output: print card information
  */
  void print_card(){
    cout << rank << " of " << suit << " (" << value << ")" << endl;
  }

  // Setters
  void setSuit(string s){suit = s;}
  void setRank(string r){rank = r;}
  void setValue(int v){value = v;}

  // Getters
  string get_suit(){return suit;}
  string get_rank(){return rank;}
  int get_value( ){return value;}

// By default doesnt need to be stated, Struct is public by default
private:

  // Private class variables
  string suit;
  string rank;
  int value;
};

// Deck Data
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3",  "4",    "5",     "6",    "7",  "8",
                        "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

Card deck[52];
int currentCardIndex = 0;
/* 
Deck Functions - initializeDeck
  Input: NONE 
  Output: Void; Initializes a standard 52-card deck
*/
void initializeDeck() {
  int deckIndex = 0;
  for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
    for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
      // Card(string suit, string rank, int value);
      deck[deckIndex++] =
          Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
    }
  }
}

/* 
shuffleDeck
  Input: NONE 
  Output: Void; Shuffles deck randonly
*/
void shuffleDeck() {
  srand((time(0)));
  for (int i = 0; i < 52; i++) {
    int index = rand() % 52;
    Card temp = deck[i]; // these next three lines are a swap function
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

Card dealCard() { 
  return deck[currentCardIndex++]; 
}

int dealInitialPlayerCards() {
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Your cards: ";
  card1.print_card();
  card2.print_card();
  //cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13]
     //<< " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
  return card1.get_value() + card2.get_value();
  //return cardValue(card1) + cardValue(card2);
}

int playerTurn(int playerTotal) {
  while (true) {
    cout << "Your total is " << playerTotal << ". Do you want to hit or stand?"
         << endl;
    string action;
    getline(cin, action);
    if (action == "hit") {
      Card newCard = dealCard();
      //playerTotal += cardValue(newCard);
      playerTotal += newCard.get_value();
      cout << "You drew a ";
      newCard.print_card();
      //cout << "You drew a " << RANKS[newCard % 13] << " of "
           //<< SUITS[newCard / 13] << endl;
      if (playerTotal > 21) {
        break;
      }
      else if(playerTotal==21){
        return playerTotal;
      }
    } else if (action == "stand") {
      cout<< "User stands with "<< playerTotal << endl;
      break;
    } else {
      cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
    }
  }
  return playerTotal;
}

int dealerTurn(int dealerTotal) {

    cout << "Dealer's total is " << dealerTotal << endl;
    
    while (dealerTotal<18) {
      cout << "Dealer hits " <<endl;

      Card newCard = dealCard();
      //playerTotal += cardValue(newCard);
      dealerTotal += newCard.get_value();
      cout << "Dealer drew a ";
      newCard.print_card();
      //cout << "You drew a " << RANKS[newCard % 13] << " of "
           //<< SUITS[newCard / 13] << endl;
      if (dealerTotal > 21) {
        break;
      }
    }
    if (dealerTotal<21){
        cout << "Dealer stands with "<< dealerTotal <<endl;
      }
  return dealerTotal;
}

void determineWinner(int playerTotal, int dealerTotal){
  if (playerTotal > 21) {
    cout << "You busted! Dealer wins." << endl;
    }
  else if(dealerTotal > 21){
    cout << "Dealer busted with " << dealerTotal<<"! You win." << endl;
    }
  else if(dealerTotal == 21){
    cout << "Dealer wins with " << dealerTotal << endl;
    }  
  else if(playerTotal > dealerTotal){
    cout << "You win." << endl;
    }
    else if(playerTotal < dealerTotal){
    cout << "Dealer wins." << endl;
    }
    else{
    cout << "It's a tie." << endl;
    }        
};

int main() {
  bool game_loop = true;
  while (game_loop){
    
    // Reset and shuffle deck after each round
    currentCardIndex=0;
    initializeDeck();  
    shuffleDeck();
 
    // Deal Intial Player Cards
    int playerTotal = dealInitialPlayerCards();
    cout << "The playerTotal is " << playerTotal << endl;
    
    // Deal Intial Dealer Cards
    int dealerTotal = dealInitialPlayerCards();
    cout << "The dealerTotal is " << dealerTotal << endl;

    // Player turn
    playerTotal = playerTurn(playerTotal);

    // PlayerTotal over 21 Ends round
    if (playerTotal >21){
      cout<< "Player busted with " << playerTotal << ". Dealer wins"<<endl;
    }
    // PlayerTotal at 21 Ends round
    else if (playerTotal == 21){
      cout<< "Player wins with " << playerTotal << endl;
    }
    // else Dealer Turn
    else{
      // Dealer turn
      dealerTotal = dealerTurn(dealerTotal);
      // Pick and Print winner
      determineWinner(playerTotal, dealerTotal);
    }

    // Ask if user wants to play again
    cout << "Play Again? ";
    
    string actionz;
    getline(cin, actionz);

    if (actionz == "No"){
      game_loop = false;
    }
  }// Ends gameLoop
   return 0;
}// Ends main