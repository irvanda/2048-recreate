#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

/*
2048
objective:
	- grid array
	- random spawner
	- shifting number (left, right, top, down)
	- key pressed
	- adding number
	- end game checker
	- score
	- win / lose 
additional
	- display: grid, help screen, winer screen, loser screen, try again

*/

//Global variable
int i, j, k;

class gameLogic {
	private:
	
		int grid[4][4];
		int bgrid[4][4];
		int key;
		bool end;
		int max;
		int prob;
		int score;
		string name;
	
	public:
		
		void startGame();
		void setGrid();
		void spawn();
		void printGrid();
		void shiftNum();
		void addNumber();
		void operate();
		void keyPressed();
		void displayGrid();
		int getKey();
		void backupGrid();
		bool gridChanged();
		bool gridFull();
		void endGame();
		bool getEnd();
		void maxNumber();
		void winner();
		void gameSave();
		void printHighScore();
		
};

int main(){
	srand(time(NULL));
	
	gameLogic exec;
	
	exec.setGrid();
	
	exec.startGame();
	
	while(1){
		exec.displayGrid();
		exec.keyPressed();
		if(exec.getKey()==4) break;
		exec.operate();
		if(exec.getEnd())
			break;
	}
	
	return 0;
	
}

void gameLogic::operate(){
	backupGrid();
	shiftNum();
	addNumber();
	shiftNum();
	if(gridChanged())
		spawn();
	else if(gridFull())
		endGame();
	maxNumber();
	if(max==2048)
		winner();
}

void gameLogic::startGame(){
	end = false;
	max = 0;
	prob = 0;
	score = 0;
}

void gameLogic::setGrid(){	
	for ( i=0; i<4; ++i)
		for ( j=0; j<4; ++j)
			grid[i][j]=0;
		
	spawn();
	spawn();
	
	
}

void gameLogic::spawn(){
	do{
		i=rand()%4;
		j=rand()%4;
		k=rand()%150;
	}while(grid[i][j]);
	
	if (k<prob)
		grid[i][j] = 4;
	else
		grid[i][j] = 2;
}

int gameLogic::getKey(){
	return key;
}

void gameLogic::shiftNum(){
	int dir = key;
	// to left direction --> dir = 0	
	if(dir==0){
		for ( i=0; i<4; i++){
			for ( j=0; j<3; j++){
				if(!grid[i][j]){
					for(k=j+1; k<4; k++){
						
						if(grid[i][k]){
							
							grid[i][j]=grid[i][k];
							grid[i][k]=0;
							break;
								
						}	
					}
				}
			}
		}
	}
	
	// to right direction --> dir = 1
	else if(dir==1){
		for ( i=0; i<4; i++){
			for ( j=3; j>0; j--){
				if(!grid[i][j]){
					for(k=j-1; k>=0; k--){
						
						if(grid[i][k]){
							
							grid[i][j]=grid[i][k];
							grid[i][k]=0;
							break;
								
						}	
					}
				}
			}
		}
	}
	
	// to up direction --> dir = 2
	else if(dir==2){
		for ( i=0; i<4; i++){
			for ( j=0; j<3; j++){
				if(!grid[j][i]){
					for(k=j+1; k<4; k++){
						
						if(grid[k][i]){
							
							grid[j][i]=grid[k][i];
							grid[k][i]=0;
							break;
								
						}	
					}
				}
			}
		}
	}
	
	// to down direction --> dir = 3
	else{
		for ( i=0; i<4; i++){
			for ( j=3; j>0; j--){
				if(!grid[j][i]){
					for(k=j-1; k>=0; k--){
						
						if(grid[k][i]){
							
							grid[j][i]=grid[k][i];
							grid[k][i]=0;
							break;
								
						}	
					}
				}
			}
		}
	}
	

}	

void gameLogic::addNumber(){
	int dir = key;
	// to left direction --> dir = 0	
	if(dir==0){
		for ( i=0; i<4; i++){
			for ( j=0; j<3; j++){
				if(grid[i][j]&&grid[i][j]==grid[i][j+1]){
					grid[i][j]+=grid[i][j+1];
					grid[i][j+1]=0;
					score += (((log2(grid[i][j]))-1)*grid[i][j]);
				}
			}
		}
	}
	
	// to right direction --> dir = 1
	else if(dir==1){
		for ( i=0; i<4; i++){
			for ( j=3; j>0; j--){
				if(grid[i][j]&&grid[i][j]==grid[i][j-1]){
					grid[i][j]+=grid[i][j-1];
					grid[i][j-1]=0;
					score += (((log2(grid[i][j]))-1)*grid[i][j]);
				}
			}
		}
	}
	
	// to up direction --> dir = 2
	else if(dir==2){
		for ( i=0; i<4; i++){
			for ( j=0; j<3; j++){
				if(grid[j][i]&&grid[j][i]==grid[j+1][i]){
					grid[j][i]+=grid[j+1][i];
					grid[j+1][i]=0;
					score += (((log2(grid[j][i]))-1)*grid[j][i]);
				}
			}
		}
	}
	
	// to down direction --> dir = 3
	else{
		for ( i=0; i<4; i++){
			for ( j=3; j>0; j--){
				if(grid[j][i]&&grid[j][i]==grid[j-1][i]){
					grid[j][i]+=grid[j-1][i];
					grid[j-1][i]=0;
					score += (((log2(grid[j][i]))-1)*grid[j][i]);
				}
			}
		}
	}
}



void gameLogic::printGrid(){
	cout << "Game 2048" << endl;
	cout << "=========" << endl << endl;
	for ( i=0; i<4; ++i){
		cout << "\t|";
		for ( j=0; j<4; ++j){
			if(grid[i][j])
				cout << setw(4) << grid[i][j] << "|";
			else
				cout << "    |";
			
			//cout <<"(" << i << "," << j <<")"<< "|"; 
		}
		cout << endl << endl;
	}
	
	cout << "score: " << score << ", max: " << max << endl << endl;
	
	cout << "control: w             ^" << endl;
	cout << "       a s d         < v >" << endl << endl;
	
	cout << "q: quit" << endl;
			
}

void gameLogic::displayGrid(){
	system("clear");
	
	printGrid();
}

void gameLogic::keyPressed(){
	char control;
	system("stty raw");
	cin>>control;
	system("stty cooked");
	
	if (control == 'a') //left arrow
		key = 0;
	else if (control == 'd') //right arrow
		key = 1;
	else if (control == 'w') //up
		key = 2;
	else if (control == 's') //down
		key = 3;
	else key = 4; // quit
}

void gameLogic::backupGrid(){
	for ( i=0; i<4; ++i)
		for ( j=0; j<4; ++j)
			bgrid[i][j]=grid[i][j];
}

bool gameLogic::gridChanged(){
	for ( i=0; i<4; ++i)
		for ( j=0; j<4; ++j)
			if(bgrid[i][j]!=grid[i][j])
				return true;
			
	return false;
}

bool gameLogic::gridFull(){
	for ( i=0; i<4; ++i)
		for ( j=0; j<4; ++j)
			if(grid[i][j] == 0)
				return false;
			
	return true;
}

void gameLogic::endGame(){
	end = true;
	system("clear");
	cout << "Game Over -- You Lose" << endl;
	cout << "Score: " << score << endl << endl;
	cout << "Try to win to save your high score." << endl << endl;
	
	printHighScore();
}

bool gameLogic::getEnd(){
	return end;
}

void gameLogic::maxNumber(){
	for ( i=0; i<4; ++i)
		for ( j=0; j<4; ++j){
			if(grid[i][j] > max){
				max = grid[i][j];
				prob += 5;
			}
			
		}
}

void gameLogic::winner(){
	end = true;
	system("clear");
	cout << "Game Over -- You Win" << endl;
	cout << "Score: " << score;
	cout << "Name: " ;
	cin >> name;
	gameSave();
	system("./operate.sh");
	
	cout << endl << endl;
	printHighScore();
}

void gameLogic::gameSave(){
	ofstream output;
	output.open ("highscore",ofstream::app);
	output << score << "," << name << endl;
	output.close();
}

void gameLogic::printHighScore(){
	cout << "High Score" << endl;
	cout << "Name,Score;" << endl;
	cout << "===========" << endl;
	system("cat highscore");
}