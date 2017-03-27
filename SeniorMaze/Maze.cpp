#include "Maze.h"
#include<stack>
#include<set>
#include<list>
using namespace std;
typedef pair<index, index> edge;

//这是一个在FindPath中使用的辅助函数
list<index> getBackWay(stack<edge>& possiblePath, const index& startIndex, const index& endIndex)
{
	list<index> result;
	result.push_front(endIndex);
	while (!possiblePath.empty())
	{
		edge temp = possiblePath.top();
		possiblePath.pop();
		if (temp.second == result.front())
		{
			result.push_front(temp.first);
		}
	}
	result.remove(ErrorIndex);
	if (result.front() != startIndex)
		throw exception("Something error");
	return result;
}
list<index> Maze::FindPath(const index& startIndex, const index& endIndex)
{
	if (((*this)[startIndex] && (*this)[endIndex]))
		throw invalid_argument("传入了无法到达的起始或终止点坐标");
	
	//使用一个散列表来管理所有已经被检查过的节点，避免循环
	set<index> whereHaveChecked;
	//管理待查找的节点的集合
	stack<edge> whereCanMove;
	//这个栈用于在找到endIndex后确定路径。/*总感觉这样实现有点蠢*/
	stack<edge> possiblePath;

	whereCanMove.push(edge(ErrorIndex,startIndex));
	whereHaveChecked.insert(startIndex);
	while (!whereCanMove.empty())
	{
		edge nowChecking = whereCanMove.top();
		index nowPosition = nowChecking.second;
		possiblePath.push(nowChecking);
		whereCanMove.pop();
		for (int i = Orientation::up; i < Orientation::left; i++)
		{
			index neighbor = checkCanMove(nowPosition, (Orientation)i);
			if (neighbor != ErrorIndex&&whereHaveChecked.find(neighbor) == whereHaveChecked.end()) 
			{
				whereCanMove.push(edge(nowPosition, neighbor));
				whereHaveChecked.insert(neighbor);
			}
			if (neighbor == endIndex)
			{
				possiblePath.push(edge(nowPosition, neighbor));
				return getBackWay(possiblePath, startIndex, endIndex);
			}
		}
	}
	return list<index>();	//C++不能返回null真的好不开心
}

Wall Maze::operator[](const index& i)
{
	if (!checkIndexIn(i))
		throw invalid_argument("无效的坐标");
	return *(_maze + i.first*_width + i.second);
}
inline index Maze::getNeighborIndex(const index& i, const Orientation ori)
{
	//应当注意的是，GetNeighborIndex不做关于索引是否有效的检查，也因此，它是一个静态方法。
	switch (ori)
	{
	case Orientation::up:
		return index(i.first + 1, i.second);
	case Orientation::right:
		return index(i.first, i.second + 1);
	case Orientation::down:
		return index(i.first - 1, i.second);
	case Orientation::left:
		return index(i.first, i.second - 1);
	default:
		throw std::invalid_argument("无效的方向参数");
	}
}
inline index Maze::checkCanMove(const index& i,const Orientation ori)
{
	if((*this)[i]==true)
		throw invalid_argument("貌似因为一些意外，你站到墙上去了");
	//在getNeighorIndex函数中进行ori参数的合法化检查
	index neighbor = getNeighborIndex(i, ori);
	if (checkIndexIn(neighbor) && (*this)[neighbor] == 0)
		return neighbor;
	else
		return ErrorIndex;
}
inline bool Maze::checkIndexIn(const index& i)
{
	return i.first < _height&&i.second < _width;
}
std::ostream& operator<<(std::ostream& os, const index& i) {
	return os << "( " << i.first << " , " << i.second << " )";
}

std::istream& operator>>(std::istream& is, index& i) {
	int a, b;
	is >> a >> b;
	i = index(a, b);
	return is;
}