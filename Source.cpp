//Name: Keyan Raahemifar, Austin Jabari
//Date: May 21, 2014
//Course: ICS 3UI
//Exercise: Summative
#include "Header.h"

game::game(int x)
{
	int threes = x;
}
void game::printScores () {	
	string temp;
	ifstream scores ("Scores.txt");

	if (scores.eof()) {
		cout << "No scores exist - play and record your score!" << endl;
	} else {
		//       1234567890123451234567890123456
		cout << "Player             Wins        Losses" << endl;
	}
	string garb;
	/*scores >> garb;
	scores >> garb;*/
	while (!scores.eof()) {
		scores >> temp;
		cout << setw(15) << temp;		// player name
		scores >> temp;
		cout << setw(13) << temp;		// wins
		scores >> temp;
  cout << setw(9) << temp;		// losses
		cout << endl;
	}

	scores.close();
}

void game::updateScore(string player, bool win) {
	vector<Player> players;
	Player tempPlayer;
	bool entry_exists = false;

	// read players into vector
	ifstream in_scores ("Scores.txt");
	while (!in_scores.eof()) {
		in_scores >> tempPlayer.name;
		in_scores >> tempPlayer.wins;
		in_scores >> tempPlayer.losses;
		players.push_back(tempPlayer);
	}
	in_scores.close();

	// check if there's already an entry
	for (int i=0; i<players.size(); i++) {
		if (players[i].name == player) entry_exists = true;
	}

	// update vector accordingly
	if (entry_exists) {
		for (int i=0; i<players.size(); i++) {
			if (players[i].name == player) {
				if (win) {
					players[i].wins++;
				} else {
					players[i].losses++;
				}
			}
		}
	} else {
		tempPlayer.name = player;
		tempPlayer.wins = win;
		tempPlayer.losses = !win;
		players.push_back(tempPlayer);
	}

	// write vector to scores file
	ofstream out_scores ("Scores.txt");
	for (int i=0; i<players.size(); i++) {
		out_scores << players[i].name << " " << players[i].wins << " " << players[i].losses;
		if (i != players.size()-1) out_scores << endl;
	}
	out_scores.close();
}

void game::display(){ //to display the board
	cout<<" 1   2   3   4   5   6   7\n"; //header for rows
	for(int a = 0; a<= 5; a++) //the board
	{
		for(int b =0; b <= 6; b++) cout<<char(218)<<char(196)<<char(191)<<" ";
		cout<<'\n';
		for(int b =0; b <= 6; b++) cout<<char(179)<<place[a][b]<<char(179)<<" ";
		cout<<'\n';
		for(int b =0; b <= 6; b++) cout<<char(192)<<char(196)<<char(217)<<" ";
		cout<<'\n';
	}
}
bool game::check(int a, int b){
	int vertical = 1;//(|), checking for vertical
	int horizontal = 1;//(-), checking for horizontal
	int diagonal1 = 1;//(\), checking diagonal left
	int diagonal2 = 1;//(/), checking diagonal right
	char player = place[a][b]; //fill the place with the character value
	int i;//vertical
	int ii;//horizontal
	//check for vertical(|)
	for(i = a + 1;place[i][b] == player && i <= 5;i++,vertical++);//Check down, see if there are player pieces
	for(i = a - 1;place[i][b] == player && i >= 0;i--,vertical++);//Check up, see if there are player pieces
	if(vertical >= 4)return true; // if four in a row, you win!
	//check for horizontal(-)
	for(ii = b -1;place[a][ii] == player && ii >= 0;ii--,horizontal++);//Check left, see if there are player pieces
	for(ii = b +1;place[a][ii] == player && ii <= 6;ii++,horizontal++);//Check right, see if there are player pieces
	if(horizontal >= 4) return true; // if four in a row, you win!
	//check for diagonal 1 (\)
	for(i = a -1, ii= b -1;place[i][ii] == player && i>=0 && ii >=0; diagonal1 ++, i --, ii --);//up and left, see if there are player pieces
	for(i = a +1, ii = b+1;place[i][ii] == player && i<=5 && ii <=6;diagonal1 ++, i ++, ii ++);//down and right, see if there are player pieces
	if(diagonal1 >= 4) return true; // if four in a row, you win!
	//check for diagonal 2(/)
	for(i = a -1, ii= b +1;place[i][ii] == player && i>=0 && ii <= 6; diagonal2 ++, i --, ii ++);//up and right, see if there are player pieces
	for(i = a +1, ii= b -1;place[i][ii] == player && i<=5 && ii >=0; diagonal2 ++, i ++, ii --);//up and left, see if there are player pieces
	if(diagonal2 >= 4) return true; // if four in a row, you win!
	return false; //otherwise we are still playing!
}


int game::drop(int b, char player){
	if(b >=0 && b<= 6) //all available rows
	{
		if(place[0][b] == ' ')
        { //sees if the places have been filled
			int i;
			for(i = 0;place[i][b] == ' ';i++)
				if(i == 5)
                {place[i][b] = player;
			return i;}
			i--;
			place[i][b] =player; //the place is now filled by the player counter
			return i;

		}
		else
			return -1;

	}
	else
		return -1;
}

bool game::checkWin(int pl)
{
     char player = (char)pl;
	// check (|)
	for (int j=0; j<=6; j++) {
		for (int i=0; i<=2; i++) {
			if (place[i][j] == player && place[i+1][j] == player && place[i+2][j] == player && place[i+3][j] == player) {
				return true;
			}
		}
	}

	// (-)
	for (int i=0; i<=5; i++) {
		for (int j=0; j<=3; j++) {
			if (place[i][j] == player && place[i][j+1] == player && place[i][j+2] == player && place[i][j+3] == player) {
				return true;
			}
		}
	}

	// check (\)
	for (int i=0; i<=2; i++) {
		for (int j=0; j<=3; j++) {
			if (place[i][j] == player && place[i+1][j+1] == player && place[i+2][j+2] == player && place[i+3][j+3] == player) {
				return true;
			}
		}
	}

	// check(/)
	for (int i=3; i<=5; i++) {
		for (int j=0; j<=3; j++) {
			if (place[i][j] == player && place[i-1][j+1] == player && place[i-2][j+2] == player && place[i-3][j+3] == player) {
				return true;
			}
		}
	}
	return false;
}
//checks for 3 in a row
int game::check3inrow(int pl)
{
    char player = (char)pl;
	int threes = 0;

	// check horizontal rows
	for (int j=0; j<=6; j++) {
		for (int i=0; i<=2; i++) {
			if (place[i][j] == ' ' && place[i+1][j] == player && place[i+2][j] == player && place[i+3][j] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i+1][j] == ' ' && place[i+2][j] == player && place[i+3][j] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i+1][j] == player && place[i+2][j] == ' ' && place[i+3][j] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i+1][j] == player && place[i+2][j] == player && place[i+3][j] == ' ') {
				threes++;
			}
		}
	}

	// check vertical rows with space in middle
	for (int i=0; i<=5; i++) {
		for (int j=0; j<=3; j++) {
			if (place[i][j] == ' ' && place[i][j+1] == player && place[i][j+2] == player && place[i][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i][j+1] == ' ' && place[i][j+2] == player && place[i][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i][j+1] == player && place[i][j+2] == ' ' && place[i][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i][j+1] == player && place[i][j+2] == player && place[i][j+3] == ' ') {
				threes++;
			}
		}
	}

	// check left-down right-up diagonal
	for (int i=0; i<=2; i++) {
		for (int j=0; j<=3; j++) {
			if (place[i][j] == ' ' && place[i+1][j+1] == player && place[i+2][j+2] == player && place[i+3][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i+1][j+1] == ' ' && place[i+2][j+2] == player && place[i+3][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i+1][j+1] == player && place[i+2][j+2] == ' ' && place[i+3][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i+1][j+1] == player && place[i+2][j+2] == player && place[i+3][j+3] == ' ') {
				threes++;
			}
		}
	}


	// check left-down right-up diagonals
	for (int i=3; i<=5; i++) {
		for (int j=0; j<=3; j++) {
			if (place[i][j] == ' ' && place[i-1][j+1] == player && place[i-2][j+2] == player && place[i-3][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i-1][j+1] == ' ' && place[i-2][j+2] == player && place[i-3][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i-1][j+1] == player && place[i-2][j+2] == ' ' && place[i-3][j+3] == player) {
				threes++;
			}
			if (place[i][j] == player && place[i-1][j+1] == player && place[i-2][j+2] == player && place[i-3][j+3] == ' ') {
				threes++;
			}
		}
	}

	return threes;
}

bool game::EOG()
{
	// game over if somone has one
	if (checkWin(2)) return true;
	if (checkWin(1)) return true;

	// game over but draw
	bool noDraw = true;
	for (int j=0; j<=6; j++)
    {
		if (place[0][j] == ' ') noDraw = false;
	}
	return noDraw;
}

int game::score ()
{
	if(checkWin(1)) {
		return 100;
	} else if (checkWin(2)) {
		return -100;
	} else {
		return check3inrow(1)-check3inrow(2);
	}
}

int game::Height(int j)
{
	for (int i=5; i>=0; i--) {
		if (place[i][j]== ' ') return i;
	}
	return -1;
}

// returns the best move for the ai
Move game::minimax (int depth)
{
	cout << "Computer calculating \n";
	int bestScore = -1000;
	Move bestMove = {0,5};

	for (int j=0; j<=6; j++) {
		if (Height(j) != -1)
        {
			int i = Height(j);
			place[i][j] = 1;

			int tempScore = min(depth);// evaluate based on what would happen if that move was chosen
			if (tempScore >= bestScore) {
				bestScore = tempScore;
				bestMove.x = j;
				bestMove.y = i;
			}
			place[i][j] = ' ';
		}
	}
	return bestMove;
}
// maximize score
int game::max(int depth)
{
	if(EOG() || depth == d) return score();

	int bestScore = -1000;
	for (int j=0; j<=6; j++) {
		if (Height(j) != -1) {

			int i = Height(j);
			place[i][j] = 1;			// set the tile to an ai piece
			int tempScore = min(depth+1);	// evaluate based on what would happen if that move was chosen
			if (tempScore >= bestScore) {
				bestScore = tempScore;
			}
			place[i][j] = ' ';
		}
	}
	return bestScore;
}
// minimizes score
int game::min(int depth)
{
	if(EOG() || depth == d) return score();

	int bestScore = 1000;
	for (int j=0; j<=6; j++) {
		if (Height(j) != -1)
        {
			int i = Height(j);
			place[i][j] = 2;// set the tile to an ai piece
			int tempScore = max(depth+1);// evaluate based on what would happen if that move was chosen
			if (tempScore <= bestScore) {
				bestScore = tempScore;
			}
			place[i][j] = ' ';// set the tile back to being ' ', because the move hasn't been chosen yet
		}
	}
	return bestScore;
}
int checkMove;
int game::AI ()
{
    int j;
    int saveDrop;
    for (j = 0; j < 7; j ++)
    {
        saveDrop = drop (j, 1);
        if (saveDrop == -1)
           j ++;
        else
        {
        if (check (saveDrop, j) == true)
        {
           place [saveDrop][j] = ' ';
           return j;
        }
        place [saveDrop][j] = ' ';
        }
        saveDrop = drop (j, 2);
        if (saveDrop == -1)
           j ++;
        else
        {
        if (check (saveDrop, j) == true)
        {
           place [saveDrop][j] = ' ';
           return j;
        }
        place [saveDrop][j] = ' ';
        }
    }
    int x = rand () % 7;
    saveDrop = drop (x, 1);
    while (saveDrop == -1)
    {
     x = rand () % 7;
     saveDrop = drop (x, 1);
    }
    place [saveDrop][x] = ' ';
    return x;
}
void game::RunGame()
{
    cout << "Connect 4 - It's your turn to play!" << endl;
    int playerNum; //number of players
    cout << "How many players (1 or 2)?" << endl;
    cout << "(You can also enter 3 to view scores.)" << endl;
    cin >> playerNum; //get number of players
    while (playerNum < 1 || playerNum > 3)
    {
          cout << "That is not an appropriate player number." << endl;
          cout << "How many players (1 or 2)?" << endl;
          cout << "(You can also enter 3 to view scores.)" << endl;
          cin >> playerNum;
    }
    if (playerNum==1)
    {
    cout << "Which level?" << endl << "1 - Easy" << endl << "2 - Medium"<<endl<<"3 - Hard"<<endl;
    int x;
    cin >> x;
    while (x > 3 || x < 1)
    {
        cout << "That is not an appropriate level number." << endl;
        cout << "Which level?" << endl << "1 - Easy" << endl << "2 - Medium"<<endl<<"3 - Hard"<<endl; 
        cin >> x;
    } 
    if (x==1)
    {
             d=1;
    }
    else if (x==2)
    {
      d=3;   
    }
    else if (x==3)
    {
      d=8;   
    }
}
if (playerNum==2)
{
   cout<<"Player 1: Please enter your name: "<<endl;
   cin>>name1;
   cout<<"Player 2: Please enter your name: "<<endl;
   cin>>name2;
}
if (playerNum != 3)
{
    cout << endl;
    system("CLS");
    
{
	for(int a =0;a <= 5; a++)
    {		//fill place array with a bunch of blanks
		for(int b = 0; b<=6; b++)	
			place[a][b] = ' ';		
   }								
	display();//display the place
	int holdRow;//Will hold user row choice
	int holdDrop = 0;//will hold drop value
	int piecesPlaced = 0;//counts number of pieces dropped
	bool gameWon = false;//Will be changed to true when game is won and will exit while loop
	char player = 15;//character value in ASCII for player 2
	while(!gameWon)//will stop when gameWon = true
    {
		if(holdDrop != -1)//bulletproof
        {
			if(player == 15)//if it was player 2's turn b4, then we are going to have player 1 drop
			{
            	cout<<"Player 1 - enter a row to drop: ";
				player = 254;//char of players piece
			}
			else //otherwise player 2 drops
            {
                if (playerNum == 2)
		              cout<<"Player 2 - enter a row to drop: ";
				player = 15;//char of player piece
			}
		}
		while(true){//infinite loop until 'break'
			if(piecesPlaced == 42) break;//if draw, game over
			if (playerNum == 2 || (playerNum == 1 && player != 15))
			{
			cin>>holdRow;//get user input
			holdRow--;//arrays start at 0
            }
            if (playerNum == 1 && player == 15) //if one player and it is not the single player's turn, do the CPU move
            {
               holdRow = minimax(1).x;
            }
			if(holdRow <=6 && holdRow >= 0) break;//if within valid range stop loop
			else cout<< "\nPlease enter a value between 1 and 7 :";//ask for input and loop again
		}
		if(piecesPlaced == 42) break;//if draw
		holdDrop = drop(holdRow,player);//drop the player store the row in holdRow
		counter [holdDrop] ++;
		if(holdDrop == -1)	cout<<"Colomn is full\nPlease enter another number between 1 and 7:";//if error -1 row is full
		else{
			gameWon = check(holdDrop,holdRow);//check if game is won
			piecesPlaced ++;//another character has been succesfully placed
			system("cls");//This clears the screen works with windows, not nesscery to run game
			display();//displayed updated place
		}
	}
	//system("cls");//this clears the screen
	if(piecesPlaced == 42){//if draw
		cout<<"No winner, Game was drawn\n";
		////FIX THIS!////
		cin.get();
		cin.get();
		////FIX THIS!////
	}
	if (playerNum == 1)
	{
	if(player == 15)//if won by player 2
	{
		cout<<"PLAYER 2 WINS YO!!!\n";
    }
	else 
    {
         cout<<"PLAYER 1 WINS YO!!!\n";//Else won by player 1
    }
    }
    else if (playerNum == 2)
    {
   	if(player == 15)//if won by player 2
	{
		cout<<"PLAYER 2 WINS YO!!!\n";
		updateScore(name1, false);
		cout << "DONE one!" << endl;
        updateScore(name2, true);
        cout << "DONE both!" << endl;		
    }
	else 
    {
         cout<<"PLAYER 1 WINS YO!!!\n";//Else won by player 1
         updateScore(name1, true);
         cout << "DONE one!" << endl;
         updateScore(name2, false);
         cout << "DONE both!" << endl;
    }
    }
}
}
else {

		printScores();

	}
////FIX THIS!////
	cin.get();
	cin.get();
}
