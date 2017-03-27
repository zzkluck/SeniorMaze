#include"DEBUG.h"
#ifdef DEBUG
#include"UnitTests.h"
#include"Maze.h"
#include<random>
#include<ctime>

static Wall  SeniorTests[] = {
	1,1,1,1,1,1,1,1,1,1,
	1,0,1,1,1,0,1,1,1,1,
	1,0,0,1,0,1,1,1,1,1,
	1,0,0,0,0,0,0,0,1,1,
	1,0,0,1,1,0,1,1,1,1,
	1,1,0,0,0,1,0,0,0,1,
	1,0,1,1,0,0,0,1,0,1,
	1,1,1,1,1,1,1,1,1,1
};
static Maze TestMaze(SeniorTests, 8, 10);
static index StartIndex(1, 1);
static index EndIndex(3, 7);

class UnitTests {
public:
	static void Maze_CheckIndexIn_Test()
	{
		Maze testMaze = TestMaze;
		EXPECT_EQ_BASE(true, testMaze.checkIndexIn(index(0, 0)));
		EXPECT_EQ_BASE(true, testMaze.checkIndexIn(index(testMaze._height - 1, testMaze._width - 1)));

		int i = 10;
		srand((unsigned int)time(nullptr));
		while (i-- > 0)
		{
			int row = rand() % testMaze._height;
			int col = rand() % testMaze._width;
			EXPECT_EQ_BASE(true, testMaze.checkIndexIn(index(row, col)));
		}

		EXPECT_EQ_BASE(false, testMaze.checkIndexIn(index(testMaze._height, testMaze._width)));
	}
	static void Maze_Operator_Test()
	{
		Maze testMaze = TestMaze;
		EXPECT_EQ_BASE(true, testMaze[index(0, 0)]);
		EXPECT_EQ_BASE(true, testMaze[index(2, 5)]);
		EXPECT_EQ_BASE(false, testMaze[index(3, 1)]);
		EXPECT_EQ_BASE(false, testMaze[index(6, 8)]);
		CATCH_EXCEPTION(testMaze[index(100, 100)], std::invalid_argument);
	}
	static void Maze_GetNeighborIndex_Test()
	{
		Maze testMaze = TestMaze;
		//应当注意的是，GetNeighborIndex不做关于索引是否有效的检查，也因此，它是一个静态方法。
		EXPECT_EQ_BASE(index(1, 4), testMaze.getNeighborIndex(index(0, 4), Orientation::up));
		EXPECT_EQ_BASE(index(-1, 4), testMaze.getNeighborIndex(index(0, 4), Orientation::down));
		EXPECT_EQ_BASE(index(0, 3), testMaze.getNeighborIndex(index(0, 4), Orientation::left));
		EXPECT_EQ_BASE(index(0, 5), testMaze.getNeighborIndex(index(0, 4), Orientation::right));
		EXPECT_EQ_BASE(index(24152, 436347), Maze::getNeighborIndex(index(24151, 436347), Orientation::up));
		CATCH_EXCEPTION(testMaze.getNeighborIndex(index(0, 4), (Orientation)4), std::invalid_argument);
	}
	static void Maze_CheckCanMove_Test()
	{
		Maze testMaze = TestMaze;
		EXPECT_EQ_BASE(index(2, 1), testMaze.checkCanMove(index(1, 1), Orientation::up));
		EXPECT_EQ_BASE(ErrorIndex, testMaze.checkCanMove(index(1, 1), Orientation::down));
		EXPECT_EQ_BASE(ErrorIndex, testMaze.checkCanMove(index(2, 1), Orientation::left));
		EXPECT_EQ_BASE(index(3, 5), testMaze.checkCanMove(index(4, 5), Orientation::down));
		EXPECT_EQ_BASE(ErrorIndex, testMaze.checkCanMove(index(7, 9), Orientation::right));
		CATCH_EXCEPTION(testMaze.checkCanMove(index(7, 9), (Orientation)4), std::invalid_argument);
	}

	static void Maze_FindPath_Demo()
	{
		Maze testMaze = TestMaze;
		list<index> path = testMaze.FindPath(StartIndex, EndIndex);
		for (const index& i : path)
		{
			cout << i << " - - > ";
		}
		cout << endl;
	}

	static void tests()
	{
		Maze_CheckIndexIn_Test();
		Maze_Operator_Test();
		Maze_GetNeighborIndex_Test();
	}
};
int main()
{
	UnitTests::tests();

	cout << TestPass << " / " << TestCount << "  ( " << (double)TestPass / TestCount * 100 << " % )" << endl;

	cout << endl;
	UnitTests::Maze_FindPath_Demo();
	getchar();
}
#endif // DEBUG
