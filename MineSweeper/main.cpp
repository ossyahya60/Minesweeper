#include "Tile.h"

int main()
{
	//ShowWindow(::GetConsoleWindow(), SW_HIDE);  //Hides ConsoleWindow at the start.
	//MessageBox(NULL, "An exception has just occcured", "ERROR", MB_ICONERROR);
	sf::RenderWindow window(sf::VideoMode(450, 510), "MineSweeper", sf::Style::Close | sf::Style::Titlebar);  //window.
	window.setFramerateLimit(30);

	label:
	////////////////////////SetUp///////////////////////////////
	bool MineClicked = false;
	bool Won = false;
	int NoOfMines = 6*6;
	int NoOfActualMines = 0;
	int NoOfRemFlags = 0;
	Tile Tiles[15][15];
	Tiles[0][0].GameOver = false;
	srand(time(NULL));
	for (int i = 0; i < NoOfMines; i++)
		Tiles[rand() % 15][rand() % 15].SetType('B');

	sf::Vector2f Temp;
	for (int i = 2; i < 17; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Temp.x = j * 30.0;
			Temp.y = i * 30.0;
			Tiles[i - 2][j].SetPos(Temp);
			if (Tiles[i - 2][j].GetType() == 'B')
			{
				NoOfActualMines++;
				NoOfRemFlags++;
			}
		}
	}

	sf::Texture textures[22];
	textures[13].loadFromFile("minesweeper_00.png"); //Normal.
	textures[0].loadFromFile("minesweeper_01.png"); //Empty.
	textures[11].loadFromFile("minesweeper_02.png"); //Flag
	textures[10].loadFromFile("minesweeper_05.png"); //Mine
	//textures[12].loadFromFile("GameOver.png"); //GameOver!
	textures[15].loadFromFile("Idle.png"); //Idle
	textures[16].loadFromFile("Won.png"); //Won
	textures[17].loadFromFile("Lost.png"); //Lost
	textures[18].loadFromFile("Timer.png"); //Timer
	textures[19].loadFromFile("Mine.png"); //Mines Flagged
	textures[20].loadFromFile("minesweeper_06.png"); //Mine Clicked
	textures[21].loadFromFile("minesweeper_17.png"); //Flagged but not mine
	textures[14].loadFromFile("minesweeper_07.png"); //0
	textures[1].loadFromFile("minesweeper_08.png"); //1
	textures[2].loadFromFile("minesweeper_09.png"); //2
	textures[3].loadFromFile("minesweeper_10.png"); //3
	textures[4].loadFromFile("minesweeper_11.png"); //4
	textures[5].loadFromFile("minesweeper_12.png"); //5
	textures[6].loadFromFile("minesweeper_13.png"); //6
	textures[7].loadFromFile("minesweeper_14.png"); //7
	textures[8].loadFromFile("minesweeper_15.png"); //8
	textures[9].loadFromFile("minesweeper_16.png"); //9

	////////////////////////////////////////////////////////////////
	int Timer = 0;
	int t = 30;

	while (window.isOpen())
	{
		/////////////////////////Drawing////////////////////////////
		window.clear();

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (!Tiles[0][0].GameOver)
				{
					if (Tiles[i][j].IsFlagged()) //flagged
						Tiles[i][j].SetText(textures[11]);
					else if (Tiles[i][j].GetType() == 'B' && Tiles[i][j].IsClicked() && MineClicked == true) //mine!
						Tiles[i][j].SetText(textures[20]);
					else if (!Tiles[i][j].IsClicked()) //Idle
						Tiles[i][j].SetText(textures[13]);
					else if (Tiles[i][j].GetType() == 'E' && Tiles[i][j].IsClicked()) //empty or numbered.
					{
						int t = Tiles[i][j].CalculateNoOfBombs(Tiles, i, j);
						Tiles[i][j].SetText(textures[t]);
						if (t != 0)
						{
							Tiles[i][j].SetType('N');
							Tiles[i][j].SetNumberofSurrBombs(t);
						}
					}
				}
				else
				{
					if (Tiles[i][j].GetType() == 'E' && Tiles[i][j].IsClicked()) //empty or numbered.
					{
						int t = Tiles[i][j].CalculateNoOfBombs(Tiles, i, j);
						Tiles[i][j].SetText(textures[t]);
						if (t != 0)
						{
							Tiles[i][j].SetType('N');
							Tiles[i][j].SetNumberofSurrBombs(t);
						}
					}
				}
				Tiles[i][j].Draw(window);
			}
		}

		///////////////////////////Input///////////////////////////

		sf::Event eEvnt;
		while (window.pollEvent(eEvnt))
		{
			if (eEvnt.type != eEvnt.MouseButtonReleased)  //to avoid getting more than one input in a single click.
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))   //Mouse control
				{
					sf::Vector2i MousePos = sf::Mouse::getPosition(window);

					if (MousePos.x >= 195.0 && MousePos.x <= 255.0 && MousePos.y >= 0 && MousePos.y <= 60.0)
					{
						goto label;
					}

					for (int i = 0; i < 15; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							if (!Tiles[i][j].IsFlagged() && !Tiles[i][j].IsClicked() && (MousePos.x > Tiles[i][j].GetPos().x && MousePos.x < Tiles[i][j].GetPos().x + Tiles[0][0].GetSize().x) && (MousePos.y > Tiles[i][j].GetPos().y && MousePos.y < Tiles[i][j].GetPos().y + Tiles[0][0].GetSize().y))
							{
								Tiles[i][j].Click();
								if (Tiles[i][j].GetType() == 'B')
									Tiles[i][j].SetMineClicked();
							}
						}
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !Won)
				{
					sf::Vector2i MousePos = sf::Mouse::getPosition(window);

					for (int i = 0; i < 15; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							if (!Tiles[i][j].IsClicked() && (MousePos.x > Tiles[i][j].GetPos().x && MousePos.x < Tiles[i][j].GetPos().x + Tiles[0][0].GetSize().x) && (MousePos.y > Tiles[i][j].GetPos().y && MousePos.y < Tiles[i][j].GetPos().y + Tiles[0][0].GetSize().y))
							{
								if (Tiles[i][j].IsFlagged())
								{
									Tiles[i][j].DeFlag();
									NoOfRemFlags++;
								}
								else
								{
									Tiles[i][j].Flag();
									if (NoOfRemFlags > 0)
										NoOfRemFlags--;
								}
							}
						}
					}
				}
			}
			if (eEvnt.type == sf::Event::Closed)
				window.close();
		}
		////////////////////////////Logic//////////////////////////

		int WinningCondition = 0;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (Tiles[i][j].IsClicked() && Tiles[i][j].GetType() == 'B')  //Mine clicked!
					Tiles[i][j].GameOver = true;
				else if (Tiles[i][j].GetType() == 'E' && Tiles[i][j].IsClicked())  //chain clear.
				{
					int NoOfBombs = 0;
					if (i != 0 && j != 0 && i != 14 && j != 14)
					{
						for (int t = 0; t < 3; t++)
							for (int u = 0; u < 3; u++)
								if (!(t == 1 && u == 1))
									if (Tiles[i - 1 + t][j - 1 + u].GetType() == 'B')
										NoOfBombs++;
						if (NoOfBombs == 0)
							for (int t = 0; t < 3; t++)
								for (int u = 0; u < 3; u++)
									if (!(t == 1 && u == 1))
										Tiles[i - 1 + t][j - 1 + u].Click();
					}
					else if (i == 0 && j == 0)
					{
						if (Tiles[i][j + 1].GetType() == 'B')
							NoOfBombs++;
						if (Tiles[i + 1][j].GetType() == 'B')
							NoOfBombs++;
						if (Tiles[i + 1][j + 1].GetType() == 'B')
							NoOfBombs++;
						if (NoOfBombs == 0)
						{
							Tiles[i][j + 1].Click();
							Tiles[i + 1][j].Click();
							Tiles[i + 1][j + 1].Click();
						}
					}
					else if (i == 14 && j == 14)
					{
						if (Tiles[i][j - 1].GetType() == 'B')
							NoOfBombs++;
						if (Tiles[i - 1][j].GetType() == 'B')
							NoOfBombs++;
						if (Tiles[i - 1][j - 1].GetType() == 'B')
							NoOfBombs++;
						if (NoOfBombs == 0)
						{
							Tiles[i][j - 1].Click();
							Tiles[i - 1][j].Click();
							Tiles[i - 1][j - 1].Click();
						}
					}
					else if (i == 0 && j == 14)
					{
						if (Tiles[i + 1][j].GetType() == 'B')
							NoOfBombs++;
						if (Tiles[i][j - 1].GetType() == 'B')
							NoOfBombs++;
						if (Tiles[i + 1][j - 1].GetType() == 'B')
							NoOfBombs++;
						if (NoOfBombs == 0)
						{
							Tiles[i + 1][j].Click();
							Tiles[i][j - 1].Click();
							Tiles[i + 1][j - 1].Click();
						}
					}
					else if (i == 14 && j == 0)
					{
						if (Tiles[i][j + 1].GetType() == 'B')
							NoOfBombs++;
						if (Tiles[i - 1][j].GetType() == 'B')
							NoOfBombs++;
						if (Tiles[i - 1][j + 1].GetType() == 'B')
							NoOfBombs++;
						if (NoOfBombs == 0)
						{
							Tiles[i][j + 1].Click();
							Tiles[i - 1][j].Click();
							Tiles[i - 1][j + 1].Click();
						}
					}
					else if (i == 0)
					{
						for (int t = 0; t < 2; t++)
							for (int u = 0; u < 3; u++)
								if (!(t == 0 && u == 1))
									if (Tiles[i + t][j - 1 + u].GetType() == 'B')
										NoOfBombs++;
						if (NoOfBombs == 0)
						{
							for (int t = 0; t < 2; t++)
								for (int u = 0; u < 3; u++)
									if (!(t == 0 && u == 1))
										Tiles[i + t][j - 1 + u].Click();
						}
					}
					else if (i == 14)
					{
						for (int t = 0; t < 2; t++)
							for (int u = 0; u < 3; u++)
								if (!(t == 1 && u == 1))
									if (Tiles[i - 1 + t][j - 1 + u].GetType() == 'B')
										NoOfBombs++;
						if (NoOfBombs == 0)
						{
							for (int t = 0; t < 2; t++)
								for (int u = 0; u < 3; u++)
									if (!(t == 1 && u == 1))
										Tiles[i - 1 + t][j - 1 + u].Click();
						}
					}
					else if (j == 0)
					{
						for (int t = 0; t < 3; t++)
							for (int u = 0; u < 2; u++)
								if (!(t == 1 && u == 0))
									if (Tiles[i - 1 + t][j + u].GetType() == 'B')
										NoOfBombs++;
						if (NoOfBombs == 0)
						{
							for (int t = 0; t < 3; t++)
								for (int u = 0; u < 2; u++)
									if (!(t == 1 && u == 0))
										Tiles[i - 1 + t][j + u].Click();
						}
					}
					else if (j == 14)
					{
						for (int t = 0; t < 3; t++)
							for (int u = 0; u < 2; u++)
								if (!(t == 1 && u == 0))
									if (Tiles[i - 1 + t][j - 1 + u].GetType() == 'B')
										NoOfBombs++;
						if (NoOfBombs == 0)
						{
							for (int t = 0; t < 3; t++)
								for (int u = 0; u < 2; u++)
									if (!(t == 1 && u == 0))
										Tiles[i - 1 + t][j - 1 + u].Click();
						}
					}
				}
				if (Tiles[0][0].GameOver)
				{
					if (Tiles[i][j].GetType() == 'E' && Tiles[i][j].IsFlagged() == false)
						Tiles[i][j].SetText(textures[0]);
					else if (Tiles[i][j].GetType() == 'N' && Tiles[i][j].IsFlagged() == false)
						Tiles[i][j].SetText(textures[Tiles[i][j].GetNumberofSurrBombs()]);
					else if (Tiles[i][j].GetType() == 'B' && Tiles[i][j].IsClicked() == true && Tiles[i][j].GetMineClicked())
						Tiles[i][j].SetText(textures[20]);
					else if (Tiles[i][j].GetType() == 'B' && Tiles[i][j].IsClicked() == false && Tiles[i][j].IsFlagged() == false)
						Tiles[i][j].SetText(textures[10]);
					else if (Tiles[i][j].GetType() == 'B' && Tiles[i][j].IsFlagged() == true)
						Tiles[i][j].SetText(textures[11]);
					else if (Tiles[i][j].GetType() != 'B' && Tiles[i][j].IsFlagged() == true)
					{
						Tiles[i][j].SetText(textures[21]);
						Tiles[i][j].SetType('Z');
						Tiles[i][j].DeFlag();
					}
					t = 30;
					Tiles[i][j].Click();
				}
				if (Tiles[i][j].GetType() == 'B' && Tiles[i][j].IsFlagged() && !Tiles[i][j].GameOver)
					WinningCondition++;
			}
		}


		///////////////////////////Others//////////////////////////

		if (Tiles[0][0].GameOver) //GameOver! (I couldn't put it in the Drawing section).
		{
			sf::RectangleShape Lost;
			Lost.setSize(sf::Vector2f(60.0, 60.0));
			Lost.setPosition(195.0, 0.0);
			Lost.setTexture(&textures[17]);
			window.draw(Lost);
		}
		else if (WinningCondition == NoOfActualMines)
		{
			sf::RectangleShape Win;
			Win.setSize(sf::Vector2f(60.0, 60.0));
			Win.setPosition(195.0, 0.0);
			Win.setTexture(&textures[16]);
			window.draw(Win);
			Won = true;
			t = 30;
		}
		else
		{
			sf::RectangleShape Idle;
			Idle.setSize(sf::Vector2f(60.0, 60.0));
			Idle.setPosition(195.0, 0.0);
			Idle.setTexture(&textures[15]);
			window.draw(Idle);
		}

		///////////////////////////////////

		sf::RectangleShape Mine, No1, No2;  //Mines Flagged
		Mine.setSize(sf::Vector2f(40.0, 40.0));
		Mine.setPosition(30.0, 10.0);
		Mine.setTexture(&textures[19]);
		No1.setSize(sf::Vector2f(30.0, 30.0));
		No1.setPosition(90.0, 15.0);
		No2.setSize(sf::Vector2f(30.0, 30.0));
		No2.setPosition(120.0, 15.0);
		int N1 = NoOfRemFlags / 10;
		int N2 = NoOfRemFlags % 10;
		if (N1 != 0)
			No1.setTexture(&textures[N1]);
		else
			No1.setTexture(&textures[14]);
		if (N2 != 0)
			No2.setTexture(&textures[N2]);
		else
			No2.setTexture(&textures[14]);
		window.draw(Mine);
		window.draw(No1);
		window.draw(No2);


		sf::RectangleShape timer, NO1, NO2, NO3;  //Timer
		timer.setSize(sf::Vector2f(40.0, 40.0));
		timer.setPosition(375.0, 10.0);
		timer.setTexture(&textures[18]);
		NO1.setSize(sf::Vector2f(30.0, 30.0));
		NO1.setPosition(270.0, 15.0);
		NO2.setSize(sf::Vector2f(30.0, 30.0));
		NO2.setPosition(300.0, 15.0);
		NO3.setSize(sf::Vector2f(30.0, 30.0));
		NO3.setPosition(330.0, 15.0);
		int n1 = Timer / 100;
		int n2 = (Timer % 100) / 10;
		int n3 = (Timer % 100) % 10;
		if (n1 != 0)
			NO1.setTexture(&textures[n1]);
		else
			NO1.setTexture(&textures[14]);
		if (n2 != 0)
			NO2.setTexture(&textures[n2]);
		else
			NO2.setTexture(&textures[14]);
		if (n3 != 0)
			NO3.setTexture(&textures[n3]);
		else
			NO3.setTexture(&textures[14]);
		window.draw(NO1);
		window.draw(NO2);
		window.draw(NO3);
		window.draw(timer);

		///////////////////////////////////

		if (t == 0)
		{
			Timer++;
			t = 30;
		}
		else
			t--;

		window.display();
	}
	return 0;
}