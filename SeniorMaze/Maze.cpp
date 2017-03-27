#include "Maze.h"
#include<stack>
#include<set>
#include<list>
using namespace std;
typedef pair<index, index> edge;

//����һ����FindPath��ʹ�õĸ�������
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
		throw invalid_argument("�������޷��������ʼ����ֹ������");
	
	//ʹ��һ��ɢ�б������������Ѿ��������Ľڵ㣬����ѭ��
	set<index> whereHaveChecked;
	//��������ҵĽڵ�ļ���
	stack<edge> whereCanMove;
	//���ջ�������ҵ�endIndex��ȷ��·����/*�ܸо�����ʵ���е��*/
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
	return list<index>();	//C++���ܷ���null��ĺò�����
}

Wall Maze::operator[](const index& i)
{
	if (!checkIndexIn(i))
		throw invalid_argument("��Ч������");
	return *(_maze + i.first*_width + i.second);
}
inline index Maze::getNeighborIndex(const index& i, const Orientation ori)
{
	//Ӧ��ע����ǣ�GetNeighborIndex�������������Ƿ���Ч�ļ�飬Ҳ��ˣ�����һ����̬������
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
		throw std::invalid_argument("��Ч�ķ������");
	}
}
inline index Maze::checkCanMove(const index& i,const Orientation ori)
{
	if((*this)[i]==true)
		throw invalid_argument("ò����ΪһЩ���⣬��վ��ǽ��ȥ��");
	//��getNeighorIndex�����н���ori�����ĺϷ������
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