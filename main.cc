#include <iostream>
#include <string>
#include "cell.h"
#include "textdisplay.h"
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  int count = 0;

  try {
  while (true) {
    cin >> cmd;
		try{
      if (cmd == "new") {
        int n;
        cin >> n;

			  g.init(n);
        cout << g;

      } 
      else if (cmd == "play") {
        int r = 0, c = 0;
        cin >> r >> c;
      
			  if (count % 2 == 0){
           // black move
				   g.setPiece(r,c,Colour::Black);
			  } else {
			     // white move
				   g.setPiece(r,c,Colour::White);
			  }
      
			  cout << g;

        if (g.isFull()){
          Colour winner = g.whoWon();
				  if (winner == Colour::Black){
				    cout << "Black wins!" << endl; 
				  } else if (winner == Colour::White) {
				    cout << "White wins!" << endl;
				  } else {
            cout << "Tie!" << endl;
					}
				  break;
			  }
     
		    ++count;
      }
		} 
		catch (InvalidMove &) {
		  continue;
		} 
		catch(out_of_range){
      continue;
		}
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}




