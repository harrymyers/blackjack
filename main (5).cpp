#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

class Deck {
private:
    vector<string> deck;

public:
    Deck() {
        string suits[4] = { "S", "D", "H", "C" };
        string faces[13] = { "A", "2", "3", "4", 
                             "5", "6", "7", "8", 
                             "9", "T", "J", "Q", "K" };
        for (const string& suit : suits) {
            for (const string& face : faces) {
                deck.push_back(face + suit);
            }
        }
    }

    void shuffle() {
        srand(static_cast<unsigned int>(time(nullptr))); 
        random_shuffle(deck.begin(), deck.end()); 
    }

      string dealCard() {
        string card = deck.back(); 
        deck.pop_back();
        return card;
    }
};

class Card {
private:
    string suit;
    string face;
    int value;
public:
    Card(string suit, string face, int value) : suit(suit), face(face), value(value) {}

    int getValue() const {
        return value;
    }

    void displayCard() const {
        cout << face << suit << " (" << value << " points)" << endl;
    }
};

class Player {
private:
    string name;
    vector<Card> hand;
    int score;

public:
    Player(string name) : name(name), score(0) {}

    void addCardToHand(const Card& card) {
        hand.push_back(card);
    }

    void calculateScore() {
        score = 0;
        int aceCount = 0; 

        for (const Card& card : hand) {
            score += card.getValue();

            // Check for Ace and adjust score if necessary
            if (card.getValue() == 11) {
                aceCount++;
            }
        }

       
        while (aceCount > 0 && score > 21) {
            score -= 10; 
            aceCount--;
        }
    }

    void displayHand() const {
        cout << endl << name << "'s hand:" << endl;
        for (const Card& card : hand) {
            card.displayCard();
        }
        cout << "Total score: " << score << endl;
    }

    int getScore() const {
        return score;
    }

    bool isBust() const {
        return score > 21;
    }

    void clearHand() {
        hand.clear();
        score = 0;
    }

    string getName() const {
      return name;
    }
};

class Dealer : public Player {
public:
Dealer() : Player("Dealer") {} 

void revealHand() const {
    cout << endl << endl;
    displayHand();
}

void playTurn(Deck& deck) {
    while (getScore() < 17) {
        cout << "Dealer hits." << endl;
      string cardString = deck.dealCard();
      string suit = cardString.substr(cardString.size() - 1, 1);
      string face = cardString.substr(0, cardString.size() - 1);
      int value;
      if (face == "A") {
          value = 11;
      } else if (face == "T" || face == "J" || face == "Q" || face == "K") {
          value = 10;
      } else {
          value = stoi(face); // Convert face to integer if it's a number
      }
      Card c1(suit, face, value); 
        addCardToHand(c1); 
        calculateScore(); 
        displayHand(); 
    }

    if (isBust()) {
        cout << "Dealer busts." << endl;
    } else {
        cout << "Dealer stands." << endl;
    }
}
};

class Game {
private:
    Deck deck;
    vector<Player> players;
    Dealer dealer;
    bool gameOver;

public:
    Game() : gameOver(false) {}

    void startGame(int numPlayers) {
        string playerName;
        for (int i = 0; i < numPlayers; ++i) {
            cout << "Enter player name: ";
            cin >> playerName;
            players.emplace_back(playerName);
        }
        deck.shuffle();
    }

    void playRound() {
        for (Player& player : players) {

          string cardString = deck.dealCard();
          string suit = cardString.substr(cardString.size() - 1, 1);
          string face = cardString.substr(0, cardString.size() - 1);
          int value;
          if (face == "A") {
              value = 11;
          } else if (face == "T" || face == "J" || face == "Q" || face == "K") {
              value = 10;
          } else {
              value = stoi(face); // Convert face to integer if it's a number
          }
          Card c1(suit, face, value); 
          
            player.addCardToHand(c1);

          cardString = deck.dealCard();
          suit = cardString.substr(cardString.size() - 1, 1);
          face = cardString.substr(0, cardString.size() - 1);
          if (face == "A") {
              value = 11;
          } else if (face == "T" || face == "J" || face == "Q" || face == "K") {
              value = 10;
          } else {
              value = stoi(face); // Convert face to integer if it's a number
          }
          Card c2(suit, face, value); 
            player.addCardToHand(c2);
            player.calculateScore();
            player.displayHand();
        }
        string cardString = deck.dealCard();
        string suit = cardString.substr(cardString.size() - 1, 1);
        string face = cardString.substr(0, cardString.size() - 1);
        int value;
        if (face == "A") {
            value = 11;
        } else if (face == "T" || face == "J" || face == "Q" || face == "K") {
            value = 10;
        } else {
            value = stoi(face); 
        }
        Card c1(suit, face, value); 
        dealer.addCardToHand(c1); 

        cardString = deck.dealCard();
        suit = cardString.substr(cardString.size() - 1, 1);
        face = cardString.substr(0, cardString.size() - 1);
        if (face == "A") {
            value = 11;
        } else if (face == "T" || face == "J" || face == "Q" || face == "K") {
            value = 10;
        } else {
            value = stoi(face); // Convert face to integer if it's a number
        }
        Card c2(suit, face, value); 
        dealer.addCardToHand(c2); 
        dealer.calculateScore();
        //dealer.revealHand();

        for (Player& player : players) {
            while (!player.isBust() && (player.getScore() < 21)) {
                char choice;
                cout << player.getName() << ", do you want to hit (Y or N)? " << endl;
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                  string cardString = deck.dealCard();
                  string suit = cardString.substr(cardString.size() - 1, 1);
                  string face = cardString.substr(0, cardString.size() - 1);
                  int value;
                  if (face == "A") {
                      value = 11;
                  } else if (face == "T" || face == "J" || face == "Q" || face == "K") {
                      value = 10;
                  } else {
                      value = stoi(face); // Convert face to integer if it's a number
                  }
                  Card c1(suit, face, value); 
                    player.addCardToHand(c1);
                    player.calculateScore();
                    player.displayHand();
                } else if (choice == 'N' || choice == 'n') {
                    break;
                } else {
                    cout << "Invalid input. Please enter Y or N." << endl;
                }
            }
        }

        dealer.playTurn(deck);

        displayWinners();

        resetGame();
    }


    void displayWinners() const {
        cout << "Game Over! Winners:" << endl;
        for (const Player& player : players) {
            if (!player.isBust()) {
                cout << player.getName() << ": Score - " << player.getScore();
                if (player.getScore() > dealer.getScore() || dealer.isBust()) {
                    cout << " (Winner)" << endl;
                } else if (player.getScore() < dealer.getScore()) {
                    cout << " (Loser)" << endl;
                } else {
                    cout << " (Tie)" << endl;
                }
            }
        }
    }

    void resetGame() {
        for (Player& player : players) {
            player.clearHand();
        }
        dealer.clearHand();
        gameOver = false;
    }

};

int main() {
  Game blackjackGame;
  int numPlayers;

  cout << "Welcome to Blackjack!" << endl;
  cout << "How many players (1-7)? ";
  cin >> numPlayers;

  blackjackGame.startGame(numPlayers);
  
  blackjackGame.playRound();
  blackjackGame.resetGame();
}
