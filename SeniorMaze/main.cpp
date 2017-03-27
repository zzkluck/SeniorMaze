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
	cout << "很好，招呼打完了，现在请输入迷宫的长和宽。由于某人有点懒，它们必须是整数，必须" << endl;
	int height, width;
	cin >> height >> width;
	cout << "做的很棒，你现在需要把整个迷宫都敲进去，你一共需要输入长*宽个数，它们应该只是0或1" << endl;
	cout << "现在你可以开始了" << endl;

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
			cout<<"你真的输入了0,1以外的东西"<<endl;
			cout << "我们使用一个默认的迷宫代替你的输入，以此惩罚你试图挑战程序员智商的愚蠢行为" << endl;
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
	cout << "你想要的迷宫是......." << endl;
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			cout << myMaze[r*width + c] << ' ';
		}
		cout << endl;
	}
	cout << "是嘛~（Y / N)" << endl;
	if (GetYorN())
		return Maze((Wall*)&myMaze[0], height, width);
	else if (UserIQ-- > 0)
	{
		cout << "好吧，那我们重新开始" << endl;
		return GetMaze();
	}
	else
	{
		cout << "愚蠢的凡人，你犯了太多次错误" << endl;
		throw exception("出现异常，原因：使用者过于愚蠢");
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
			cout << "虽然你输入了正确的字母，可我就想让你输大写的，哼~" << endl;
			break;
		default:
			cout << "[微笑]" << endl;
			break;
		}
	}
}
pair<index, index> GetStartAndEndIndex()
{
	cout << "输入起始点和终止点坐标，一共四个数" << endl;
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
