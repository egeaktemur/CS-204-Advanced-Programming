#include "randgen.h"
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

//Ege Aktemur Homework 1

//Printing the board in the game Algorithm is same as we learned in the lecture

void PrintChar(const vector<vector<char>> & mat){//for printing char vector of vectors such as board
	for (unsigned int i=0; i < mat.size(); i++){   
		for (unsigned int j=0; j < mat[0].size(); j++){   
			cout << setw(4) << mat[i][j];
		}
		cout << endl;
	}
}

// Checks if the given location is in the already generated locations or not

bool DoesVectorContain(const vector<vector<int>> & MinesExist,const vector<int> & Mine){
	for (unsigned int i=0;i<MinesExist.size();i++){
		if (MinesExist[i][0]==Mine[0]&&MinesExist[i][1]==Mine[1]){
			return true;
		}
	}
	return false;
}

// I used this kind of algorithm because I thought that if i check around of the given point program will give out of range error

int BombsNearCoordinate(const vector<vector<int>> &BombLocations,const vector<int> & Coordinate){
	int number=0;
	int x,y;
	int CoordinateX=Coordinate[0];
	int CoordinateY=Coordinate[1];
	for (unsigned int i=0;i<BombLocations.size();i++){
		x = BombLocations[i][0];
		y = BombLocations[i][1];
		if     ((x == CoordinateX && y == CoordinateY - 1)     //top     
			|| (x == CoordinateX && y == CoordinateY + 1)      //bottom
			|| (x == CoordinateX - 1 && y == CoordinateY - 1)  //left top							         							
			|| (x == CoordinateX - 1 && y == CoordinateY)      //left	
			|| (x == CoordinateX - 1 && y == CoordinateY + 1)  //left bottom	
			|| (x == CoordinateX + 1 && y == CoordinateY - 1)  //right top                                  							 	
			|| (x == CoordinateX + 1 && y == CoordinateY)      //right
			|| (x == CoordinateX + 1 && y == CoordinateY + 1)) //right bottom	
		{
            number++;
		}
	}
	return number;
}

//This function returns false if the unopened box does not contain bomb which means the game won by the user

bool IsGameEnded(const vector<vector<int>> & BombLocations,const vector<vector<char>> & Board){
	vector< int > Coordinate;
	for (unsigned int j=0; j < Board.size(); j++){   
		for (unsigned int k=0; k < Board[0].size(); k++){   
			if (Board[j][k] == 'X'){
				bool SteepedOnABomb = false;
				for (unsigned int l=0; l < BombLocations.size(); l++){  
					if(j==BombLocations[l][0] && k==BombLocations[l][1]){
						SteepedOnABomb = true;
					}
				}
				if (SteepedOnABomb==false){
					return false;
				}
			}

		}
	}
	return true;
}

bool AreVectorsSame(const vector<vector<char>> & Board1,const vector<vector<char>> & Board2){
	if(Board1.size()!=Board2.size() || Board1[0].size()!=Board2[0].size()){
		return false;
	}
	for (unsigned int j=0; j < Board1.size(); j++){   
		for (unsigned int k=0; k < Board1[0].size(); k++){   
			if(Board1[j].at(k)!=Board2[j].at(k)){
				return false;
			}
		}
	}
	return true;
}

int GetOption(){
	cout<<endl<<"Press:"<<endl;
	cout<<"1. If you want to find out the surrounding of a cell"<<endl;
	cout<<"2. If you want to open the cell"<<endl;
	cout<<"3. If you want to exit."<<endl;
	int Option;
	cin >> Option;
	// Firstly I did define Option as an int but it did not work in '@' test
	// Then I tried defining it as char but It printed error message twice
	// When I enter 80. So I find this way as the best way. 
	while (Option!=1 && Option!=2 && Option!=3){ 
		cin.clear();
		cin.ignore();
		cout<<"Your input is wrong. Please select one of the options: 1, 2 or 3."<<endl;
		cin>>Option;
	}
	return Option;
}

vector<vector<char>> CopyVector (const vector<vector<char>> & Board){
	vector<vector< char >> NewBoard(Board.size(), vector< char >(Board[0].size()));
	for (unsigned int j=0; j < Board.size(); j++){   
		for (unsigned int k=0; k < Board[0].size(); k++){   
			NewBoard[j].at(k)=Board[j][k];
		}
	}
	return NewBoard;
}

void option1(const vector<vector<int>> & BombLocations,const vector<vector<char>> & Board){
	vector< int > Coordinate;
	unsigned int row,col;
	cout<<"Give the coordinates: ";cin>>row>>col; //Taking input
	while (row>Board.size()-1 || col>Board[0].size()-1){ //Validity check
		cout<<"It is out of range. Please give a valid coordinates: ";cin>>row>>col;
	}
	Coordinate.push_back(row);
	Coordinate.push_back(col);// Adding row and col to a Coordinate vector
	int BombAmount = BombsNearCoordinate(BombLocations,Coordinate);
	cout<<endl<<"Displaying the surrounding of ("<<row<<","<<col<<"): "<<endl;
	vector<vector< char >> NewBoard;
	NewBoard = CopyVector(Board);
	// Created a copy of the vector and print the copy vector so original board would not change.
	for (unsigned int j=0; j < NewBoard.size(); j++){   
		for (unsigned int k=0; k < NewBoard[0].size(); k++){   
			if(j==row && k==col){
				NewBoard[j].at(k)=BombAmount+48;
			}
		}
	}
	PrintChar(NewBoard);
	cout <<"Around ("<<row<<","<<col<<") you have "<<BombAmount<<" bomb(s)"<<endl;
}

vector<vector<char>> option2(const vector<vector<int>> & BombLocations,const vector<vector<char>> & Board){
	vector< int > Coordinate;
	unsigned int row,col;
	cout<<"Give the coordinates: ";cin>>row>>col;
	while (row>Board.size()-1 || col>Board[0].size()-1){//Validity check
		cout<<"It is out of range. Please give a valid coordinates: ";cin>>row>>col;
	}
	Coordinate.push_back(row);
	Coordinate.push_back(col);
	bool SteepedOnABomb = false;
	//Check if the given Coordinate contains a bomb or not.
	for (unsigned int i=0;i<BombLocations.size();i++){
		if (BombLocations[i][0]==row && BombLocations[i][1]==col){
			SteepedOnABomb=true;
		}
	}
	vector<vector< char >> NewBoard;
	NewBoard = CopyVector(Board);
	//Check the score of the cell if it does not contain a bomb.
	if (SteepedOnABomb == false){
		for (unsigned int j=0; j < NewBoard.size(); j++){   
			for (unsigned int k=0; k < NewBoard[0].size(); k++){   
				if(j==row && k==col){
					NewBoard[j].at(k)=BombsNearCoordinate(BombLocations,Coordinate)+'0';
				}
			}
		}
		cout << endl <<"Opening cell ("<<row<<","<<col<<"):"<<endl;
		PrintChar(NewBoard);
	}
	else{
		cout << "Opening cell ("<<row<<","<<col<<"):"<<endl;
		for (unsigned int j=0; j < NewBoard.size(); j++){   
			for (unsigned int k=0; k < NewBoard[0].size(); k++){   
				if(j==row && k==col){
					NewBoard[j].at(k)=66;
				}
			}
		}
		PrintChar(NewBoard);
		cout << endl << "Unfortunately, you stepped on a mine" << endl;
		cout << "Arrangement of mines:" << endl;
	}
	return NewBoard;
}

vector<vector<int>> BombLocationsGenerator(const int &row, const int &col ,const int &nrMines){
	vector<vector<int>> BombLocations;
	vector<int> BombLocation;
	RandGen generator;
	int rowofmine,colofmine;
	for (int bombs=0;bombs<nrMines;bombs++){
		rowofmine=generator.RandInt(0,row-1);
		colofmine=generator.RandInt(0,col-1);
		BombLocation.push_back(rowofmine);
		BombLocation.push_back(colofmine);
		//Then I check if this vector is in or not in the generated locatons
		while(DoesVectorContain(BombLocations,BombLocation)){//If DoesVector Contain returns true it generates a new point
			rowofmine = generator.RandInt(0,row-1);
			colofmine = generator.RandInt(0,col-1);
			BombLocation.clear();//I remove old point
			BombLocation.push_back(rowofmine);
			BombLocation.push_back(colofmine);//I add the new point
		}
		BombLocations.push_back(BombLocation);
		BombLocation.clear();
	}
	return BombLocations;
}

int main(){
	int row,col;
	cout<<"Give the dimensions of the matrix: ";cin>>row>>col;
	int	nrMines;
	cout<<"How many bombs: ";cin>>nrMines;
	while ( nrMines  > row * col - 1 || nrMines < 1) {
		if ( nrMines > row * col -1 ) { //Checking if bomb amount is smaller than the total Coordinates 
			cout<<"The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
		}
		if ( nrMines < 1) {//Checking if bomb amount is greater than 0
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
		}
		cin >> nrMines;
	}
	vector<vector< int >> BombLocations = BombLocationsGenerator(row,col,nrMines);
	vector<vector< char >> Board(row, vector< char >(col));
	
	for (unsigned int i = 0; i<BombLocations.size() ; i++) {// Add bombs to board with locations generated
		int x=(BombLocations[i][0]);
		Board[x].at(BombLocations[i][1])='B';
	}
	vector< int > Coordinate;
	//Here I add numbers to Coordinates on board which doesnt have bomb.
	for (unsigned int i = 0; i < Board.size(); i++){
		for (unsigned int j = 0; j<Board[0].size(); j++ ) {
			if (Board[i][j] != 'B'){//Checking if there is a bomb in given Coordinate
				Coordinate.push_back(i);
				Coordinate.push_back(j);
				//Then I check how many bombs are near the Coordinate and assign this int to its Coordinate in the board
				Board[i].at(j) = ( BombsNearCoordinate ( BombLocations,Coordinate ) + '0');
				//I clear the Coordinate vector so I can assign a new Coordinate to it
				Coordinate.clear();
			}
		}
	}
	vector<vector< char >> BoardToShow(row, vector< char >(col,'X'));
	vector<vector< char >> TempBoardToShow(row, vector< char >(col,'X'));
	cout<<endl;PrintChar(BoardToShow);//Print board
	//cout << endl ; PrintChar(Board); //Print Cheat Board
	int option = 0;
	bool SteepedOnABomb=false;
	while (option!=3 //If game is ended from the option menu 
		   && SteepedOnABomb==false //If game lost  
	       && (IsGameEnded(BombLocations,BoardToShow) == false )) {//If game won
		if (SteepedOnABomb==false && (IsGameEnded(BombLocations,TempBoardToShow) == false)) {
			option = GetOption();
		}
		if(option==1 && (IsGameEnded(BombLocations,BoardToShow)==false)){
			option1(BombLocations,BoardToShow);
		}
		if(option==2 && (IsGameEnded(BombLocations,BoardToShow)==false)){
			//Option2 function returns a opened board
			TempBoardToShow = option2(BombLocations,BoardToShow);
			//I check if opened vector contains a bomb which means player stepped on a bomb.
			for (unsigned int i = 0; i < TempBoardToShow.size(); i++){   
				for (unsigned int j = 0; j < TempBoardToShow[0].size(); j++){   
					if (TempBoardToShow[i][j] == 'B') {
						SteepedOnABomb = true;
					}
				}
			}
			if (SteepedOnABomb==false) {
				BoardToShow = TempBoardToShow;
			}
		}
	}
	if ((IsGameEnded(BombLocations,BoardToShow))) {
		cout << "Congratulations! All the non-mined cells opened successfully"<<endl<<"You won!"<<endl;
		cout << endl << ">>>>> Game Over! <<<<<" << endl;
	}
	if(SteepedOnABomb){
		PrintChar(Board);
		cout << endl << ">>>>> Game Over! <<<<<" << endl;
	}
	else if (option == 3) {
		cout << "Program exiting ..." << endl;
	}
	system("pause");
	return 0;
}