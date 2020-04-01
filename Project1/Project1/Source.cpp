#include <windows.h>
#include <iostream>;
#include <thread>
#include <chrono>

using namespace std;

wstring tetronimo[7];
wstring tetronimoB[7];

int gameFieldWidth = 12;
int gameFieldHeight = 18;
unsigned char *gameField = nullptr;

int consoleWidth = 80;
int consoleHeight = 30;

int score = 0 ;
int scoreMilestone = 1000;

wstring messages[10];

//returns the value of the block in x and y of a tetromino in one of four angles rotation
int PieceRotate(int posX, int posY, int rot)
{
	switch (rot % 4)
	{
	case 0: return posY * 4 + posX;
	case 1: return 12 + posY - (4 * posX);
	case 2: return 15 - (4 * posY) - posX;
	case 3: return 3 - posY + (4 * posX);
	}

	return 0;
}

//check for overlap of tetronimo
bool PieceMove(int _tetronimo, int _rotation, int _posX, int _posY)
{
	for (int posY = 0; posY < 4; posY++)
	{
		for (int posX = 0; posX < 4; posX++)
		{
			int PieceBlockValue = PieceRotate(posX, posY, _rotation);

			int FieldBlockValue = (_posY + posY) * gameFieldWidth + (_posX + posX);

			if (_posX + posX >= 0 && _posX + posX < gameFieldWidth)
			{
				if (_posY + posY >= 0 && _posY + posY < gameFieldHeight)
				{
					if ( tetronimo[_tetronimo][PieceBlockValue] == L'X' && gameField[FieldBlockValue] != 0 ) return false;
				}
			}
		}
	}

	return true;
}


int main()
{
#pragma region tetronimos

	tetronimo[0].append(L"..X.");
	tetronimo[0].append(L"..X.");
	tetronimo[0].append(L"..X.");
	tetronimo[0].append(L"..X.");

	tetronimo[1].append(L"..X.");
	tetronimo[1].append(L".XX.");
	tetronimo[1].append(L".X..");
	tetronimo[1].append(L"....");

	tetronimo[2].append(L".X..");
	tetronimo[2].append(L".XX.");
	tetronimo[2].append(L"..X.");
	tetronimo[2].append(L"....");

	tetronimo[3].append(L"....");
	tetronimo[3].append(L".XX.");
	tetronimo[3].append(L".XX.");
	tetronimo[3].append(L"....");

	tetronimo[4].append(L"..X.");
	tetronimo[4].append(L".XX.");
	tetronimo[4].append(L"..X.");
	tetronimo[4].append(L"....");

	tetronimo[5].append(L"....");
	tetronimo[5].append(L".XX.");
	tetronimo[5].append(L"..X.");
	tetronimo[5].append(L"..X.");

	tetronimo[6].append(L"....");
	tetronimo[6].append(L".XX.");
	tetronimo[6].append(L".X..");
	tetronimo[6].append(L".X..");

	//tetronimoB
	tetronimoB[0].append(L"..X.");
	tetronimoB[0].append(L".XX.");
	tetronimoB[0].append(L".X..");
	tetronimoB[0].append(L"....");
			 
	tetronimoB[1].append(L"XXX.");
	tetronimoB[1].append(L".X..");
	tetronimoB[1].append(L".X..");
	tetronimoB[1].append(L"....");
			 
	tetronimoB[2].append(L"..X.");
	tetronimoB[2].append(L".XXX");
	tetronimoB[2].append(L"..X.");
	tetronimoB[2].append(L"....");
			 
	tetronimoB[3].append(L"....");
	tetronimoB[3].append(L".XX.");
	tetronimoB[3].append(L"..X.");
	tetronimoB[3].append(L"....");
			 
	tetronimoB[4].append(L"..X.");
	tetronimoB[4].append(L".X.X");
	tetronimoB[4].append(L"..X.");
	tetronimoB[4].append(L"....");
			 
	tetronimoB[5].append(L"....");
	tetronimoB[5].append(L".XX.");
	tetronimoB[5].append(L"..X.");
	tetronimoB[5].append(L"..X.");
			 
	tetronimoB[6].append(L"....");
	tetronimoB[6].append(L".XX.");
	tetronimoB[6].append(L".X..");
	tetronimoB[6].append(L".X..");

#pragma endregion

#pragma region messages

	messages[0].append(L"Welcome to experiment number 0991. Lets start with a simple logic puzzles.");
	messages[1].append(L"Your mother is worried. I think you should call her.");
	messages[2].append(L"Repot 433: It was not or intent\x0320\x0565\x0468\x0258");
	messages[3].append(L"The way you play this it will not take long to finish");
	messages[5].append(L"Press any key...\x0432\x0362\x0322\x0532");
	messages[6].append(L"I hope you like rainbows");
	messages[7].append(L"Are you taking the medication we gave you?");
	messages[8].append(L"\x0432\x0362\x0322\x0532\x0062\x0102\x0112\x0132\x0532\x0172\x0182\x0232\x0332\x0132");
	messages[9].append(L"Devorat loves you.");
	messages[10].append(L"This is not a game of Tetris");
	messages[11].append(L"Rebooting....");
	messages[12].append(L"Your are loosing your time you should quit now.");

#pragma endregion

	gameField = new unsigned char[gameFieldHeight * gameFieldWidth]; //creates game area

	for (int y = 0; y < gameFieldHeight; y++)
	{
		for (int x = 0; x < gameFieldWidth; x++)
		{
			gameField[y * gameFieldWidth + x] = ( x == 0 || x == gameFieldWidth - 1 || y == gameFieldHeight - 1 ) ? 9 : 0;
		}
	}

	int screenCharacter = consoleWidth * consoleHeight;

	wchar_t *titleScreen = new wchar_t[screenCharacter];
	for (int i = 0; i < screenCharacter; i++) titleScreen[i] = L' ';

	std::swprintf(&titleScreen[8 * consoleWidth + gameFieldWidth + 23], 20, L"COGNI LABS", NULL);
	std::swprintf(&titleScreen[10 * consoleWidth + gameFieldWidth + 25], 20, L"project", NULL);
	std::swprintf(&titleScreen[12 * consoleWidth + gameFieldWidth + 21], 20, L"\x0022\Fun With Tetris\x0022", NULL);

	wchar_t *gameScreen = new wchar_t[screenCharacter];
	for (int i = 0; i < screenCharacter; i++) gameScreen[i] = L' ';
	
	WORD *attributeScreen = new WORD[screenCharacter];
	for (int i = 0; i < screenCharacter; i++) attributeScreen[i] = FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

	wchar_t *endScreen = new wchar_t[screenCharacter];
	for (int i = 0; i < screenCharacter; i++) endScreen[i] = L' ';


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 132);

	HANDLE consoleBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL,
		CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(consoleBuffer);

	DWORD dwBytesWritten = 0;

	// STATE =================================================
	bool gameOver = false;
	int currentPiece = 1;
	int currentRotation = 0;
	int currentPieceX = ( gameFieldWidth / 2 ) - 2;
	int currentPieceY = 0;

	bool pressKey[4];
	bool rotateHold = false;

	int dropRate = 20; //the lower the faster
	int dropCounter = 0;
	bool dropPiece = false;

	int dropPieceColor = 0;

	bool firstMessage = true;
	bool replaceMessage = true;
	bool blackScreenGlitch = false;

	// TITLE =================================================
	WriteConsoleOutputCharacter(consoleBuffer, titleScreen, screenCharacter, { 0,0 }, &dwBytesWritten);
	std::system("pause");

	// MAIN LOOP =============================================
	while (!gameOver)
	{
		// TIME ==============================================
		this_thread::sleep_for(50ms); // GAME TICK
		
		dropCounter++;
		if ( dropCounter >= dropRate )
		{
			dropPiece = true;
			dropCounter = 0;
		}

		// INPUT ==============================================
		for (int k = 0; k < 4; k++)
		{
			pressKey[k] = (0x8000 & GetAsyncKeyState ( (unsigned char) ("\x27\x25\x28\x20"[k]) ) ) != 0; //this one is a pickle
		}

		// LOGIC ==============================================
		if (pressKey[0] && PieceMove(currentPiece, currentRotation, currentPieceX + 1, currentPieceY))
		{
			if (score > 4000 && (int)rand() % 20 == 0)
			{
				currentPieceX -= 1;
			}
			else 
			{
				currentPieceX += 1;
			}
		}
		if (pressKey[1] && PieceMove(currentPiece, currentRotation, currentPieceX - 1, currentPieceY))
		{
			if (score > 4000 && (int)rand() % 20 == 0)
			{
				currentPieceX += 1;
			}
			else
			{
				currentPieceX -= 1;
			}
		}
		if (pressKey[2] && PieceMove(currentPiece, currentRotation, currentPieceX , currentPieceY + 1))
		{
			currentPieceY += 1;
		}
		if ( pressKey[3] )
		{
			if (!rotateHold && PieceMove(currentPiece, currentRotation + 1, currentPieceX, currentPieceY))
			{
				currentRotation++;
				rotateHold = true;
			}
		}
		else 
		{
			rotateHold = false;
		}

		// COLOR LOOP
		dropPieceColor--;
		
		// DROP
		if (dropPiece)
		{
			dropPiece = false;

			if ( PieceMove( currentPiece, currentRotation, currentPieceX, currentPieceY + 1 ))
			{
				if (score > 1000 && (int)rand()%20 == 0)
				{
					currentPieceY -= 2;
				}else if(score > 2000 && (int)rand() % 20 == 0)
				{
					currentPieceY += 2;
				
				}
				else
				{
					currentPieceY += 1;
				}
			}
			else
			{
				//Pass piece information to gameField array
				for (int posY = 0; posY < 4; posY++)
				{
					for (int posX = 0; posX < 4; posX++)
					{
						int PieceBlockValue = PieceRotate(posX, posY, currentRotation);

						int FieldBlockValue = (currentPieceY + posY) * gameFieldWidth + (currentPieceX + posX);

						if (tetronimo[currentPiece][PieceBlockValue] == L'X'){
							gameField[FieldBlockValue] = currentPiece + 1;//if is 0 then is transparent
						}
					}
				}

				int completeLinesMultiplier = 0;
				//check for complete horizontal lines
				for (int y = 0; y < gameFieldHeight-1; y++)
				{
					bool lineComplete = true;
					for (int x = 1; x < gameFieldWidth-1; x++)
					{
						if (gameField[y * gameFieldWidth + x] == 0)
						{
							lineComplete = false;
							break;
						}
						
					}

					//delete the lines that are complete and collapse the ones above
					if (lineComplete == true)
					{
						replaceMessage = true;

						completeLinesMultiplier++;
						for (int z = y; z >= 1; z--)
						{
							for (int x = 1; x < gameFieldWidth - 1; x++)
							{
								gameField[z * gameFieldWidth + x] = gameField[( z - 1 ) * gameFieldWidth + x];
								

							}
						}
					}
				}
				
				//set bug different tetronimo group
				if ( score > 30 )
				{
					tetronimo[0] = tetronimoB[0];
				}
				else if(score > 5000)
				{
					tetronimo[1] = tetronimoB[1];
				}
				else if (score > 6000)
				{
					tetronimo[2] = tetronimoB[2];
				}
				else if (score > 7000)
				{
					tetronimo[3] = tetronimoB[3];
				}
				else if (score > 8000)
				{
					tetronimo[4] = tetronimoB[4];
				}


				score += 10*completeLinesMultiplier^2;

				score += 100;//for each new piece

				//choose next piece
				if ( 2600 < score && score < 2900 || 
					4300 < score && score < 4700 || 
					6600 < score && score < 7300 || 
					9000 < score && score < 9900)
				{

				}
				else
				{
					currentPiece = rand() % 7;
				}
				currentRotation = 0;
				currentPieceX = (gameFieldWidth / 2) - 2;
				currentPieceY = 0;


				//set velocity
				if (score > scoreMilestone)
				{
					dropRate -= 4;//increment pieces drop speed
					scoreMilestone *= 2;
				}
				dropRate = dropRate < 1 ? 1 : dropRate;//increment pieces drop speed


				//if not able to fit any more pieces game over
				gameOver = !PieceMove(currentPiece, currentRotation, currentPieceX, currentPieceY) || score > 13131;

			}
		}

		// RENDER =============================================
		
		//draw field
		for (int y = 0; y < gameFieldHeight; y++)
		{
			for (int x = 0; x < gameFieldWidth; x++)
			{
				gameScreen[ ( y + 2 ) * consoleWidth  + ( x + 3 ) ] = L'\x2588';
				
				int colorPick = gameField[y * gameFieldWidth + x];
				WORD attribute;
				switch (colorPick)
				{
					case 0: attribute = 0; break;
					case 1: attribute = FOREGROUND_BLUE; break;
					case 2: attribute = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
					case 3: attribute = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
					case 4: attribute = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
					case 5: attribute = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY; break;
					case 6: attribute = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY; break;
					case 7: attribute = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
					case 8: attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
					case 9: attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE ; break;
				}
				attributeScreen[(y + 2) * consoleWidth + (x + 3)] = attribute;
				//WriteConsoleOutputAttribute( consoleBuffer , &attribute , 1 , positionCoord , &written);
			}
		}

		//draw current piece
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (tetronimo[currentPiece][PieceRotate( x , y , currentRotation )] == L'X')
				{
					gameScreen[( currentPieceY + y + 2) * consoleWidth + ( currentPieceX + x + 3)] = L'\x2588';
					WORD attribute;
					dropPieceColor = dropPieceColor < 0 ? 5 : dropPieceColor;
						switch (dropPieceColor)
						{
							case 0 : attribute = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
							case 1 : attribute = FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_INTENSITY; break;
							case 2 : attribute = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
							case 3 : attribute = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
							case 4 : attribute = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
							case 5 : attribute = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
						}
					
						if (score<1000)
						{
							attribute = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
						}

					attributeScreen[(currentPieceY + y + 2) * consoleWidth + (currentPieceX + x + 3)] = attribute;

					//WriteConsoleOutputAttribute(consoleBuffer, &attribute, 1, positionCoord, &written);
				}
			}
		}

		//draw score
		if (rand() % 100 > 98)
		{
			std::swprintf(&gameScreen[ 2 * consoleWidth + gameFieldWidth + 8 ], 20 , L"SCORE: %10d", score );
		}
		else {
			std::swprintf(&gameScreen[2 * consoleWidth + gameFieldWidth + 8], 30, L"SCORE: %ls", L"Results Unavailable");
		}

		if (replaceMessage)
		{
			replaceMessage = false;

			int selectRandomMessage;
			if (firstMessage)
			{
				firstMessage = false;
				selectRandomMessage = 0;
			}
			else 
			{
				selectRandomMessage = (rand() % (sizeof(messages) / sizeof(messages[0]) - 1) ) + 1;

			}

			wchar_t* messageC = _wcsdup(messages[selectRandomMessage].c_str());
			int messageLines = ceil((messages[selectRandomMessage].length())/40.0f);
			for (int i = 0; i < 8; i++)
			{
				std::swprintf(&gameScreen[(4 + i) * consoleWidth + gameFieldWidth + 8], 41, L"%ls", L"                                          ");
			}
			for (int i = 0; i < messageLines; i++)
			{
				std::swprintf(&gameScreen[(4 + i) * consoleWidth + gameFieldWidth + 8], 41, L"%ls", &messageC[40*i]);
			}

		}

		//bug departement
		if (score > 1000)
		{
			if ( (int)rand()%10 == 0 )
			{
				int randomLocation = 80 * (rand() % 30) + (rand() % 80);
				gameScreen[randomLocation] = L'\x2588';
				attributeScreen[randomLocation] = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
			}
		}

		if (score > 2000) 
		{
			if ((int)rand() % 10 == 0)
			{
				attributeScreen[80 * (rand() % 30) + (rand() % 80)] = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
				attributeScreen[80 * (rand() % 30) + (rand() % 80)] = 0;
			}
			//gameScreen[80 * (rand() % 30) + (rand() % 80)] = L' ';
			
			if (blackScreenGlitch == true)
			{
				blackScreenGlitch = false;
				for (int i = 0; i < screenCharacter; i++) attributeScreen[i] = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
			}
			else if ((int)rand() % 30 == 0)
			{	
				blackScreenGlitch = true;
				for (int i = 0; i < screenCharacter; i++) attributeScreen[i] = 0;
			}
		}

		if (score > 10000)
		{
			int randomShift = rand() % 6 - 3 ;
			for (size_t i = 0; i < 80*30; i++)
			{
				int selectedShift = i + randomShift;
				selectedShift = randomShift > 80 * 60 ? randomShift - 80 * 60 : selectedShift;
				selectedShift = randomShift < 0? 80 * 60 - randomShift : selectedShift;
				attributeScreen[i] = attributeScreen[selectedShift];
			}
		}

		// DISPLAY ============================================
		WriteConsoleOutputCharacter(consoleBuffer, gameScreen, screenCharacter, { 0,0 }, &dwBytesWritten);
		WriteConsoleOutputAttribute(consoleBuffer, attributeScreen, screenCharacter, { 0,0 }, &dwBytesWritten);
	}

	// GAME OVER ==============================================
	std::swprintf(&endScreen[4 * consoleWidth + gameFieldWidth + 8], 20, L"Data Corrupted...", NULL);
	std::swprintf(&endScreen[6 * consoleWidth + gameFieldWidth + 8], 60, L"System Reboot from unknown crash 0x%d", score);
	std::swprintf(&endScreen[8 * consoleWidth + gameFieldWidth + 8], 60, L"Please contact us at Unicore Systems", NULL);
	std::swprintf(&endScreen[10 * consoleWidth + gameFieldWidth + 8], 40, L"@crankyunicorn", NULL);
	WriteConsoleOutputCharacter(consoleBuffer, endScreen, 80 * 30, { 0,0 }, &dwBytesWritten);
	
	this_thread::sleep_for(1000ms); // wait to exit


	std::system("pause");

	CloseHandle(consoleBuffer);

	return 0;
}

