#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <Windows.h>
#include <thread>
#include <chrono>
using namespace std;

class Tile
{
private:
	sf::RectangleShape body;
	char Type;  //B:Bomb, E:Empty.
	bool GotClicked, Flagged;
	int NumberOfSurrBombs;
	bool MineClicked;
public:
	Tile();
	static bool GameOver;
	void SetPos(sf::Vector2f Pos);
	sf::Vector2f GetPos();
	void SetType(char type);
	void Click();
	void Flag();
	void DeFlag();
	char GetType();
	bool IsClicked();
	bool IsFlagged();
	void Draw(sf::RenderWindow& window);
	void SetText(sf::Texture& text);
	int CalculateNoOfBombs(Tile(&tile)[15][15], int R, int C);
	sf::Vector2f GetSize();
	int GetNumberofSurrBombs();
	void SetNumberofSurrBombs(int N);
	void SetMineClicked();
	bool GetMineClicked();
};

Tile::Tile()
{
	MineClicked = false;
	NumberOfSurrBombs = 0;
	Type = 'E';
	Flagged = false;
	GotClicked = false;
	body.setSize(sf::Vector2f(30.0, 30.0));
}

bool Tile::GameOver = false;

void Tile::Click()
{
	GotClicked = true;
}

void Tile::SetMineClicked()
{
	MineClicked = true;
}

bool Tile::GetMineClicked()
{
	return MineClicked;
}

void Tile::SetNumberofSurrBombs(int N)
{
	NumberOfSurrBombs = N;
}

int Tile::GetNumberofSurrBombs()
{
	return NumberOfSurrBombs;
}

int Tile::CalculateNoOfBombs(Tile(&Tiles)[15][15], int R, int C)
{
	int NoOfBombs = 0;
	if (R == 0 && C == 0)
	{
		if (Tiles[R][C + 1].GetType() == 'B')
			NoOfBombs++;
		if (Tiles[R + 1][C].GetType() == 'B')
			NoOfBombs++;
		if (Tiles[R + 1][C + 1].GetType() == 'B')
			NoOfBombs++;
	}
	else if (R == 14 && C == 14)
	{
		if (Tiles[R][C - 1].GetType() == 'B')
			NoOfBombs++;
		if (Tiles[R - 1][C].GetType() == 'B')
			NoOfBombs++;
		if (Tiles[R - 1][C - 1].GetType() == 'B')
			NoOfBombs++;
	}
	else if (R == 0 && C == 14)
	{
		if (Tiles[R + 1][C].GetType() == 'B')
			NoOfBombs++;
		if (Tiles[R][C - 1].GetType() == 'B')
			NoOfBombs++;
		if (Tiles[R + 1][C - 1].GetType() == 'B')
			NoOfBombs++;
	}
	else if (R == 14 && C == 0)
	{
		if (Tiles[R][C + 1].GetType() == 'B')
			NoOfBombs++;
		if (Tiles[R - 1][C].GetType() == 'B')
			NoOfBombs++;
		if (Tiles[R - 1][C + 1].GetType() == 'B')
			NoOfBombs++;
	}
	else if (R == 0)
	{
		for (int t = 0; t < 2; t++)
			for (int u = 0; u < 3; u++)
				if (!(t == 0 && u == 1))
					if (Tiles[R + t][C - 1 + u].GetType() == 'B')
						NoOfBombs++;
	}
	else if (R == 14)
	{
		for (int t = 0; t < 2; t++)
			for (int u = 0; u < 3; u++)
				if (!(t == 1 && u == 1))
					if (Tiles[R - 1 + t][C - 1 + u].GetType() == 'B')
						NoOfBombs++;
	}
	else if (C == 0)
	{
		for (int t = 0; t < 3; t++)
			for (int u = 0; u < 2; u++)
				if (!(t == 1 && u == 0))
					if (Tiles[R - 1 + t][C + u].GetType() == 'B')
						NoOfBombs++;
	}
	else if (C == 14)
	{
		for (int t = 0; t < 3; t++)
			for (int u = 0; u < 2; u++)
				if (!(t == 1 && u == 1))
					if (Tiles[R - 1 + t][C - 1 + u].GetType() == 'B')
						NoOfBombs++;
	}
	else
	{
		for (int t = 0; t < 3; t++)
			for (int u = 0; u < 3; u++)
				if (!(t == 1 && u == 1))
					if (Tiles[R - 1 + t][C - 1 + u].GetType() == 'B')
						NoOfBombs++;
	}
	return NoOfBombs;
}

void Tile::DeFlag()
{
	Flagged = false;
}

bool Tile::IsFlagged()
{
	return Flagged;
}

sf::Vector2f Tile::GetSize()
{
	return body.getSize();
}

void Tile::SetText(sf::Texture& text)
{
	body.setTexture(&text);
}

void Tile::Flag()
{
	Flagged = true;
}

void Tile::SetType(char type)
{
	Type = type;
}

void Tile::SetPos(sf::Vector2f Pos)
{
	body.setPosition(Pos);
}

sf::Vector2f Tile::GetPos()
{
	return body.getPosition();
}

char Tile::GetType()
{
	return Type;
}

bool Tile::IsClicked()
{
	return GotClicked;
}

void Tile::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}