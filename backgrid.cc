#include "grid.h"


// dtor
Grid::~Grid(){
   delete td;
	 delete ob;
}


// setObserver
void Grid::setObserver(Observer<Info, State> *ob){
   this->ob = ob;
}


// isFull
bool Grid::isFull() const {
   bool result = true;
	 for(int i = 0; i < dimension; ++i){
      for(int j = 0; j < dimension; ++j){
			   Cell c = theGrid.at(i).at(j);
				 Info i = c.getInfo();
				 if (i.colour == Colour::NoColour){
				     result = false;
				 }
			}
	 }

	 return result;
}

// whoWon
Colour Grid::whoWon() const {
  int b = 0;
	int w = 0;
	for(int i = 0; i < dimension; ++i){
     for(int j = 0; j < dimension; ++j){
       Cell c = theGrid.at(i).at(j);
			 Info i =  c.getInfo();
			 if(i.colour == Colour::Black){
         ++b;
			 } else if (i.colour == Colour::White){
			   ++w;
			 }
		 }
	}

	if (b > w){
    return Colour::Black;
	} else if (w > b){
    return Colour::White;
	} else {
    return Colour::NoColour;
	}
}  


// init
void Grid::init(size_t n){
   dimension = n;
	 
	 // clear the old Grid
	 for(size_t i = 0; i < n; ++i){
     theGrid[i].clear();   
	 }

   theGrid.clear();

	 delete td;
   
	 // create the new Grid
   for(size_t i = 0; i < n; ++i){
      for(size_t j = 0; j < n; ++j){
			   Cell cell = Cell{i,j};
         theGrid[i].emplace_back(cell);
			}
	 }
   

	 td = new TextDisplay(dimension);
}


// setPiece
void Grid::setPiece(size_t r, size_t c, Colour colour){
   Cell & cell = theGrid.at(c).at(r);
	 cell.setPiece(colour);
	 State s = State{StateType::NewPiece, colour};

   // set newpiece state
	 cell.setState(s);

	 // set neighbour state
	 
	 // NW
	 Cell & c1 = theGrid.at(c+1).at(r+1);
	 Info i1 = c1.getInfo();
   State s1 = State{StateType::Relay, i1.colour, Direction::NW};
   c1.setState(s1);

	 // N
	 Cell & c2 = theGrid.at(c).at(r+1);
	 Info i2 = c2.getInfo();
   State s2 = State{StateType::Relay, i2.colour, Direction::N};
	 c2.setState(s2);
	 
	 // NE
	 Cell & c3 = theGrid.at(c-1).at(r+1);
	 Info i3 = c3.getInfo();
   State s3 = State{StateType::Relay, i3.colour, Direction::NE};
	 c3.setState(s3);
	 
	 // W
	 Cell & c4 = theGrid.at(c+1).at(r);
	 Info i4 = c4.getInfo();
   State s4 = State{StateType::Relay, i4.colour, Direction::W};
	 c4.setState(s4);
	 
	 // E
	 Cell & c5 = theGrid.at(c-1).at(r);
	 Info i5 = c5.getInfo();
   State s5 = State{StateType::Relay, i5.colour, Direction::E};
	 c5.setState(s5);
	 
	 // SW
	 Cell & c6 = theGrid.at(c+1).at(r-1);
	 Info i6 = c6.getInfo();
   State s6 = State{StateType::Relay, i6.colour, Direction::SW};
	 c6.setState(s6);
	 
	 // S
	 Cell & c7 = theGrid.at(c).at(r-1);
	 Info i7 = c7.getInfo();
   State s7 = State{StateType::Relay, i7.colour, Direction::S};
	 c7.setState(s7);

	 // SE
	 Cell & c8 = theGrid.at(c-1).at(r-1);
	 Info i8 = c8.getInfo();
   State s8 = State{StateType::Relay, i8.colour, Direction::SE};
   
   

   
	 cell.notifyObservers(); // notifies neighbour cells
	 td->notify(cell); // notifies textdisplay
}


// toggle
void Grid::toggle(size_t r, size_t c){
   Cell & cell = theGrid.at(c).at(r);
	 cell.toggle();
   
	 // notifies cell?
	 td->notify(cell);
}

// output operator
std::ostream & operator<< (std::ostream &out, const Grid &g){
    out << *(g.td);
		return out;
}







