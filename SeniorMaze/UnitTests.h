#pragma once
#include<iostream>
#include<vector>
using namespace std;

#define SHOW_ERROR_BASE(expect,actual) \
	do{\
		cerr<<__FILE__<<": "<<__LINE__<<": expect: "<<expect<<" actual: "<<actual<<endl;\
	}while(0)
#define SHOW_ERROR_CONTAINER(expect,actual)\
	do{\
		cerr<<__FILE__<<": "<<__LINE__<<":\n"\
			<<"expect: ";\
		for(auto m:expect)\
			cerr<<m<<' ';\
		cerr<<"\nactual: ";\
		for(auto m:actual)\
			cerr<<m<<' ';\
		cerr<<'\n'<<endl;\
	}while(0)
#define EXPECT_EQ(equality,expect,actual,format) \
	do{\
		TestCount+=1;\
		if(equality)\
			TestPass += 1;\
		else{\
			format;\
			MainReturn=1;\
			}\
	} while (0)
#define CATCH_EXCEPTION(callSomeFunction,expectException)\
	do{\
		TestCount+=1;\
		try\
		{\
			callSomeFunction;\
			cerr<<__FILE__<<": "<<__LINE__<<": 未捕获指定的异常"<<endl;\
			MainReturn=1;\
		}\
		catch (const expectException&)\
		{\
			TestPass += 1;\
		}\
	}while (0);
#define EXPECT_EQ_BASE(expect,actual) EXPECT_EQ((expect==actual),expect,actual,SHOW_ERROR_BASE(expect,actual))
#define EXPECT_EQ_CONTAINER(expect,actual) EXPECT_EQ((expect==actual),expect,actual,SHOW_ERROR_CONTAINER(expect,actual))

static int MainReturn = 0;
static int TestCount = 0;
static int TestPass = 0;