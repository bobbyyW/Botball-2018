Notes:
The #include goes first
You MUST define the states before constructing the menuitem
Each state must have its own unique number
Calling next(s_END); will end the program
All code within the while loop must be inside a state
Including newmenu without defining the menu and states in this program will cause an error

Basic sample program with menu code. You can copy and paste this and it will work:

//Included files
#include "newmenu.h"

//side programs
#define s_SIDE1 101
#define s_SIDE2 102
//etc.

//main programs
#define s_START 1
#define s_MID 2
#define s_FINAL 3
//etc.

#define s_END 0

struct menuitem menu[]=
{
	{s_START,"Start"},
	{s_MID,"Mid"},
	{s_FINAL,"Final"},
	{s_SIDE1,"Side 1"},
	{s_SIDE2,"Side 2"},
{s_END,"END"}};

int main()
{
	Get_Mode();
	//initializations, such as enable_servos();
	while(currstate!=s_END)
	{
		state(s_START)
		{
			//code
			next(s_MID);
		}
		state(s_MID)
		{
			//code
			next(s_FINAL);
		}
		state(s_FINAL)
		{
			//code
			next(s_END);
		}
		state(s_SIDE1)
		{
			//test code
			next(s_END);
		}
		state(s_SIDE2)
		{
			//test code
			next(s_END);
		}
	}
	return 0;
}