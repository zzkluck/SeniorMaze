#include"DEBUG.h"
#ifndef DEBUG
#include "Maze.h"
#include<windows.h>
#include<iostream>
#include<vector>
using namespace std;

Maze GetMaze();
bool GetYorN();
void PrintPath(const list<index>& path);

vector<Wall> myMaze;
static int UserIQ = 3;

int main()
{
	try
	{
		Maze myMaze = GetMaze();
		auto startAndEnd = GetStartAndEndIndex();
		list<index> path = myMaze.FindPath(startAndEnd.first,startAndEnd.second);
		PrintPath(path);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	system("pause");
}

Maze GetMaze()
{
	int i = 5;
	while (i-- > 0)
	{
		Sleep(1000);
		cout << "Hi~" << endl;
	}
	cout << "�ܺã��к������ˣ������������Թ��ĳ��Ϳ�����ĳ���е��������Ǳ���������������" << endl;
	int height, width;
	cin >> height >> width;
	cout << "���ĺܰ�����������Ҫ�������Թ����ý�ȥ����һ����Ҫ���볤*�����������Ӧ��ֻ��0��1" << endl;
	cout << "��������Կ�ʼ��" << endl;

	while (myMaze.size() < height*width)
	{
		char c;
		cin >> c;
		if (c == ' ' || c == '\n' || c == '\t')
			continue;
		else if (c == '1' || c == '0')
		{
			myMaze.push_back(c=='1'?true:false);
		}
		else
		{
			cout<<"�����������0,1����Ķ���"<<endl;
			cout << "����ʹ��һ��Ĭ�ϵ��Թ�����������룬�Դ˳ͷ�����ͼ��ս����Ա���̵��޴���Ϊ" << endl;
			myMaze = {
				1,1,1,1,1,1,1,1,1,1,
				1,0,1,1,1,0,1,1,1,1,
				1,0,0,1,0,1,1,1,1,1,
				1,0,0,0,0,0,0,0,1,1,
				1,0,0,1,1,0,1,1,1,1,
				1,1,0,0,0,1,0,0,0,1,
				1,0,1,1,0,0,0,1,0,1,
				1,1,1,1,1,1,1,1,1,1
			};
			height = 8;
			width = 10;
			break;
		}
	}
	cout << "����Ҫ���Թ���......." << endl;
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			cout << myMaze[r*width + c] << ' ';
		}
		cout << endl;
	}
	cout << "����~��Y / N)" << endl;
	if (GetYorN())
		return Maze((Wall*)&myMaze[0], height, width);
	else if (UserIQ-- > 0)
	{
		cout << "�ðɣ����������¿�ʼ" << endl;
		return GetMaze();
	}
	else
	{
		cout << "�޴��ķ��ˣ��㷸��̫��δ���" << endl;
		throw exception("�����쳣��ԭ��ʹ���߹����޴�");
	}
}
bool GetYorN()
{
	char c;
	while (true)
	{
		cin >> c;
		switch (c)
		{
		case 'Y':
			return true;
		case 'N':
			return false;
		case 'y':
		case 'n':
			cout << "��Ȼ����������ȷ����ĸ�����Ҿ����������д�ģ���~" << endl;
			break;
		default:
			cout << "[΢Ц]" << endl;
			break;
		}
	}
}
pair<index, index> GetStartAndEndIndex()
{
	cout << "������ʼ�����ֹ�����꣬һ���ĸ���" << endl;
	pair<index, index> result;;
	cin >> result.first >> result.second;
	return  result;
}
void PrintPath(const list<index>& path)
{
	for (const index& i : path)
	{
		cout << i << " - - > ";
	}
	cout << endl;
}
#endif // !DEBUG
