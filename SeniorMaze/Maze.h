#pragma once
#include<iostream>
#include<list>
#include<stdexcept>

#define ErrorIndex index(-1,-1)
typedef std::pair<int, int> index;
typedef bool Wall;

std::ostream& operator<<(std::ostream& os, const index& i);
std::istream& operator>>(std::istream& is, index& i);
enum Orientation
{
	up,right,down,left
};

class Maze
{
	friend class UnitTests;
public:
	//调用者应保证maze指向一个长度至少为Height*Width的bool型数组。
	Maze(Wall* maze, int height, int width) :_maze(maze), _height(height), _width(width){}

	std::list<index> FindPath(const index& startIndex, const index& endIndex);
	Wall operator[](const index& i);
private:
	bool checkIndexIn(const index& i);
	static index getNeighborIndex(const index& i, const Orientation ori);
	index checkCanMove(const index& i, const Orientation ori);

	bool* _maze;
	int _height;
	int _width;
};

