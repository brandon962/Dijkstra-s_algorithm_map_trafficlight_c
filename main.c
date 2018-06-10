//branodn962@gmail.com 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node *path_ptr;											//我用類似於上次作業的方法來建立我的地圖					
typedef struct Node 
{							
	char road;															//紀錄S, O, D, @ 
	path_ptr come;														//紀錄上一個點, 在find涵式中可以移路從中點找回起點 
	path_ptr go[4];														//紀錄該點四個方向連結到的點是誰, 0向右, 1向下, 2向左, 3向上 
	int goCost[4];														//紀錄該點往四個方向的costㄝ, 規則同上 
	int nowCost;														//起點到該點的cost, 預設9999 
	int d2Td1;															//將二維座標轉一維, EX: node[1][2]->d2Td3 = 12; 
	
	int noTraffic;														//預設為一, 表示該點沒有紅綠燈 
	int firstTraffic;													//最初紅綠燈的倒數 
	char initialTraffic;												//最初紅綠燈的狀態 
	int traffic;														//紅綠燈的循環時間 
}; 

path_ptr node [10][10];													//二維地圖 
int list[100][2];														//搭配演算法用的一維地圖 
path_ptr theEnd;														//該次移動的終點 
path_ptr theStart;														//該次移動的起點 
int startTime = 0;														//該次移動的起始時間(在第三題每次移動的起始時間會累加 

void question1();														//第一題的內容 
void question2();														//第二題的內容 
void question3();														//第三題的內容 
path_ptr initial1();													//第一題的初始化 
path_ptr initial2();													//第二題的初始化 
path_ptr initial3();													//第三題的初始化 
void walk(path_ptr);													//從起點往終點走的涵式 
void find(path_ptr);													//從終點往起點走的涵式 
void printMap(int);														//把地圖印出來的涵式 
int printCost(path_ptr);												//把目前的cost印出來的涵式 
int traffic(path_ptr);													//計算該點紅綠燈狀態的涵式 
path_ptr newStart(int,int);												//更新起點的涵式 
path_ptr newEnd(int,int);												//更新終點的涵式 
void clean (int);														//歸零每點路徑的涵式 
 
int main(int argc, char *argv[]) 
{
	question1();														//第一題 
	question2();														//第二題 
	question3();														//第三題 

	return 0;
}

void question1()														//第一題的內容 
{
	printf("第一題\n");
	theStart = initial1();												//初始化起點 
	printf("目前地圖\n");
	printMap(10);														//列印出走路前的起點 
	walk(theStart);														//實際行走 (順便尋找從中點往起點的路 
	printf("\n路徑地圖\n");
	printMap(10);														//列印走完後的圖 
	printCost(theEnd);													//列印cost 
	system("PAUSE");
	system("CLS");
}

void question2()														//第二題的內容 
{
	printf("第二題\n");
	theStart = initial2();												//初始化起點 
	printf("目前地圖\n");
	printMap(5);														//列印出走路前的起點 
	walk(theStart);														//實際行走 (順便尋找從中點往起點的路 
	printf("\n路徑地圖\n");
	printMap(5);														//列印走完後的圖 
	printCost(theEnd);													//列印cost 
	system("PAUSE");
	system("CLS");
}

void question3()														//第三題的內容 
{
	printf("第三題\n");
	int tempCost = 0;
	theStart = initial3();												//初始化起點 
	printf("目前地圖\n");												
	printMap(6);														//列印出走路前的起點 
	theStart = newStart(0,0);											//設立起點 
	theEnd = newEnd(2,0);												//設立終點 
	clean(6);															//清空之前計算的路線 
	walk(theStart);														//實際行走 
	printf("\n此段路徑地圖\n");
	printMap(6);														//列印路徑 
	tempCost += theEnd->nowCost;										//計算總cost 
	startTime = tempCost;												//調整起始時間(每走一段起始時間就要加上段路的總cost) 
	printCost(theEnd);													//列印cost 
	printf("目前花費為 : %d\n\n", tempCost);
	
	theStart = newStart(2,0);											//接下來同上 
	theEnd = newEnd(1,1);
	clean(6);
	walk(theStart);
	printf("\n此段路徑地圖\n");
	printMap(6);
	tempCost += theEnd->nowCost;
	startTime = tempCost;
	printCost(theEnd);
	printf("目前花費為 : %d\n", tempCost);

	theStart = newStart(1,1);
	theEnd = newEnd(0,5);
	clean(6);
	walk(theStart);
	printf("\n此段路徑地圖\n");
	printMap(6);
	tempCost += theEnd->nowCost;
	startTime = tempCost;
	printCost(theEnd);
	printf("目前花費為 : %d\n", tempCost);

	theStart = newStart(0,5);
	theEnd = newEnd(1,1);
	clean(6);
	walk(theStart);
	printf("\n此段路徑地圖\n");
	printMap(6);
	tempCost += theEnd->nowCost;
	startTime = tempCost;
	printCost(theEnd);
	printf("目前花費為 : %d\n", tempCost);

	theStart = newStart(1,1);
	theEnd = newEnd(5,5);
	clean(6);
	walk(theStart);
	printf("\n此段路徑地圖\n");
	printMap(6);
	tempCost += theEnd->nowCost;
	startTime = tempCost;
	printCost(theEnd);
	printf("目前花費為 : %d\n", tempCost);
}

path_ptr initial1()														//第一題的初始化
{
	int i, j, k;
	for(i = 0; i < 100; i++)											//把list做初始化的動作 
	{
		list[i][0] = 9999;												//list的第一列存放起點到該點(list[一維座標][0])的距離 
		list[i][1] = 0;													//第二列紀錄是否有找到該點的最小值(Dijkstra’s algorithm演算法中的上色) 
	}
	for(i = 0; i < 10; i++)
		for(j = 0; j < 10; j++)
			node[i][j] = NULL;											//歸零地圖 
	
	for(i = 0; i < 10; i++)
		for(j = 0; j < 10; j++)
		{
			node[i][j] = malloc(sizeof(*node[i][j]));					//將地圖初始化 
			node[i][j]->road = 'O';										//預設都是路('O') 
			node[i][j]->nowCost = 9999;									//預設和起點的距離都是9999 
			node[i][j]->d2Td1 = 10*i+j;									//設定二維轉一維的值 
			node[i][j]->noTraffic = 1;									//預設都沒有紅綠燈 
		}
	
	//以下是使用subime的多行同時編寫來標準化輸入 
	//0表示往左, 1表示往下, 2表示往右, 3表示往上 
	node[0][0]->go[0] = node[0][1];	node[0][0]->goCost[0] = 8 ;		node[0][0]->go[1] = node[1][0];	node[0][0]->goCost[1] = 29;		node[0][1]->go[2] = node[0][0];	node[0][1]->goCost[2] = 8; 		node[1][0]->go[3] = node[0][0];	node[1][0]->goCost[3] = 29;
	node[0][1]->go[0] = node[0][2];	node[0][1]->goCost[0] = 25;		node[1][0]->go[1] = node[2][0];	node[1][0]->goCost[1] = 33;		node[0][2]->go[2] = node[0][1];	node[0][2]->goCost[2] = 25;		node[2][0]->go[3] = node[1][0];	node[2][0]->goCost[3] = 33;
	node[0][2]->go[0] = node[0][3];	node[0][2]->goCost[0] = 26;		node[2][0]->go[1] = node[3][0];	node[2][0]->goCost[1] = 46;		node[0][3]->go[2] = node[0][2];	node[0][3]->goCost[2] = 26;		node[3][0]->go[3] = node[2][0];	node[3][0]->goCost[3] = 46;
	node[0][3]->go[0] = node[0][4];	node[0][3]->goCost[0] = 15;		node[3][0]->go[1] = node[4][0];	node[3][0]->goCost[1] = 15;		node[0][4]->go[2] = node[0][3];	node[0][4]->goCost[2] = 15;		node[4][0]->go[3] = node[3][0];	node[4][0]->goCost[3] = 15;
	node[0][4]->go[0] = node[0][5];	node[0][4]->goCost[0] = 23;		node[4][0]->go[1] = node[5][0];	node[4][0]->goCost[1] = 39;		node[0][5]->go[2] = node[0][4];	node[0][5]->goCost[2] = 23;		node[5][0]->go[3] = node[4][0];	node[5][0]->goCost[3] = 39;
	node[0][5]->go[0] = node[0][6];	node[0][5]->goCost[0] = 12;		node[5][0]->go[1] = node[6][0];	node[5][0]->goCost[1] = 49;		node[0][6]->go[2] = node[0][5];	node[0][6]->goCost[2] = 12;		node[6][0]->go[3] = node[5][0];	node[6][0]->goCost[3] = 49;
	node[0][6]->go[0] = node[0][7];	node[0][6]->goCost[0] = 30;		node[6][0]->go[1] = node[7][0];	node[6][0]->goCost[1] = 18;		node[0][7]->go[2] = node[0][6];	node[0][7]->goCost[2] = 30;		node[7][0]->go[3] = node[6][0];	node[7][0]->goCost[3] = 18;
	node[0][7]->go[0] = node[0][8];	node[0][7]->goCost[0] = 5 ;		node[7][0]->go[1] = node[8][0];	node[7][0]->goCost[1] = 33;		node[0][8]->go[2] = node[0][7];	node[0][8]->goCost[2] = 5 ;		node[8][0]->go[3] = node[7][0];	node[8][0]->goCost[3] = 33;
	node[0][8]->go[0] = node[0][9];	node[0][8]->goCost[0] = 20;		node[8][0]->go[1] = node[9][0];	node[8][0]->goCost[1] = 17;		node[0][9]->go[2] = node[0][8];	node[0][9]->goCost[2] = 20;		node[9][0]->go[3] = node[8][0];	node[9][0]->goCost[3] = 17;
	node[1][0]->go[0] = node[1][1];	node[1][0]->goCost[0] = 24;		node[0][1]->go[1] = node[1][1];	node[0][1]->goCost[1] = 5 ;		node[1][1]->go[2] = node[1][0];	node[1][1]->goCost[2] = 24;		node[1][1]->go[3] = node[0][1];	node[1][1]->goCost[3] = 5; 
	node[1][1]->go[0] = node[1][2];	node[1][1]->goCost[0] = 48;		node[1][1]->go[1] = node[2][1];	node[1][1]->goCost[1] = 26;		node[1][2]->go[2] = node[1][1];	node[1][2]->goCost[2] = 48;		node[2][1]->go[3] = node[1][1];	node[2][1]->goCost[3] = 26;
	node[1][2]->go[0] = node[1][3];	node[1][2]->goCost[0] = 50;		node[2][1]->go[1] = node[3][1];	node[2][1]->goCost[1] = 23;		node[1][3]->go[2] = node[1][2];	node[1][3]->goCost[2] = 50;		node[3][1]->go[3] = node[2][1];	node[3][1]->goCost[3] = 23;
	node[1][3]->go[0] = node[1][4];	node[1][3]->goCost[0] = 15;		node[3][1]->go[1] = node[4][1];	node[3][1]->goCost[1] = 15;		node[1][4]->go[2] = node[1][3];	node[1][4]->goCost[2] = 15;		node[4][1]->go[3] = node[3][1];	node[4][1]->goCost[3] = 15;
	node[1][4]->go[0] = node[1][5];	node[1][4]->goCost[0] = 10;		node[4][1]->go[1] = node[5][1];	node[4][1]->goCost[1] = 14;		node[1][5]->go[2] = node[1][4];	node[1][5]->goCost[2] = 10;		node[5][1]->go[3] = node[4][1];	node[5][1]->goCost[3] = 14;
	node[1][5]->go[0] = node[1][6];	node[1][5]->goCost[0] = 41;		node[5][1]->go[1] = node[6][1];	node[5][1]->goCost[1] = 41;		node[1][6]->go[2] = node[1][5];	node[1][6]->goCost[2] = 41;		node[6][1]->go[3] = node[5][1];	node[6][1]->goCost[3] = 41;
	node[1][6]->go[0] = node[1][7];	node[1][6]->goCost[0] = 42;		node[6][1]->go[1] = node[7][1];	node[6][1]->goCost[1] = 15;		node[1][7]->go[2] = node[1][6];	node[1][7]->goCost[2] = 42;		node[7][1]->go[3] = node[6][1];	node[7][1]->goCost[3] = 15;
	node[1][7]->go[0] = node[1][8];	node[1][7]->goCost[0] = 66;		node[7][1]->go[1] = node[8][1];	node[7][1]->goCost[1] = 42;		node[1][8]->go[2] = node[1][7];	node[1][8]->goCost[2] = 66;		node[8][1]->go[3] = node[7][1];	node[8][1]->goCost[3] = 42;
	node[1][8]->go[0] = node[1][9];	node[1][8]->goCost[0] = 18;		node[8][1]->go[1] = node[9][1];	node[8][1]->goCost[1] = 39;		node[1][9]->go[2] = node[1][8];	node[1][9]->goCost[2] = 18;		node[9][1]->go[3] = node[8][1];	node[9][1]->goCost[3] = 39;
	node[2][0]->go[0] = node[2][1];	node[2][0]->goCost[0] = 29;		node[0][2]->go[1] = node[1][2];	node[0][2]->goCost[1] = 32;		node[2][1]->go[2] = node[2][0];	node[2][1]->goCost[2] = 29;		node[1][2]->go[3] = node[0][2];	node[1][2]->goCost[3] = 32;
	node[2][1]->go[0] = node[2][2];	node[2][1]->goCost[0] = 49;		node[1][2]->go[1] = node[2][2];	node[1][2]->goCost[1] = 52;		node[2][2]->go[2] = node[2][1];	node[2][2]->goCost[2] = 49;		node[2][2]->go[3] = node[1][2];	node[2][2]->goCost[3] = 52;
	node[2][2]->go[0] = node[2][3];	node[2][2]->goCost[0] = 74;		node[2][2]->go[1] = node[3][2];	node[2][2]->goCost[1] = 61;		node[2][3]->go[2] = node[2][2];	node[2][3]->goCost[2] = 74;		node[3][2]->go[3] = node[2][2];	node[3][2]->goCost[3] = 61;
	node[2][3]->go[0] = node[2][4];	node[2][3]->goCost[0] = 13;		node[3][2]->go[1] = node[4][2];	node[3][2]->goCost[1] = 26;		node[2][4]->go[2] = node[2][3];	node[2][4]->goCost[2] = 13;		node[4][2]->go[3] = node[3][2];	node[4][2]->goCost[3] = 26;
	node[2][4]->go[0] = node[2][5];	node[2][4]->goCost[0] = 35;		node[4][2]->go[1] = node[5][2];	node[4][2]->goCost[1] = 50;		node[2][5]->go[2] = node[2][4];	node[2][5]->goCost[2] = 35;		node[5][2]->go[3] = node[4][2];	node[5][2]->goCost[3] = 50;
	node[2][5]->go[0] = node[2][6];	node[2][5]->goCost[0] = 44;		node[5][2]->go[1] = node[6][2];	node[5][2]->goCost[1] = 7; 		node[2][6]->go[2] = node[2][5];	node[2][6]->goCost[2] = 44;		node[6][2]->go[3] = node[5][2];	node[6][2]->goCost[3] = 7; 
	node[2][6]->go[0] = node[2][7];	node[2][6]->goCost[0] = 10;		node[6][2]->go[1] = node[7][2];	node[6][2]->goCost[1] = 61;		node[2][7]->go[2] = node[2][6];	node[2][7]->goCost[2] = 10;		node[7][2]->go[3] = node[6][2];	node[7][2]->goCost[3] = 61;
	node[2][7]->go[0] = node[2][8];	node[2][7]->goCost[0] = 19;		node[7][2]->go[1] = node[8][2];	node[7][2]->goCost[1] = 63;		node[2][8]->go[2] = node[2][7];	node[2][8]->goCost[2] = 19;		node[8][2]->go[3] = node[7][2];	node[8][2]->goCost[3] = 63;
	node[2][8]->go[0] = node[2][9];	node[2][8]->goCost[0] = 21;		node[8][2]->go[1] = node[9][2];	node[8][2]->goCost[1] = 29;		node[2][9]->go[2] = node[2][8];	node[2][9]->goCost[2] = 21;		node[9][2]->go[3] = node[8][2];	node[9][2]->goCost[3] = 29;
	node[3][0]->go[0] = node[3][1];	node[3][0]->goCost[0] = 50;		node[0][3]->go[1] = node[1][3];	node[0][3]->goCost[1] = 41;		node[3][1]->go[2] = node[3][0];	node[3][1]->goCost[2] = 50;		node[1][3]->go[3] = node[0][3];	node[1][3]->goCost[3] = 41;
	node[3][1]->go[0] = node[3][2];	node[3][1]->goCost[0] = 32;		node[1][3]->go[1] = node[2][3];	node[1][3]->goCost[1] = 11;		node[3][2]->go[2] = node[3][1];	node[3][2]->goCost[2] = 32;		node[2][3]->go[3] = node[1][3];	node[2][3]->goCost[3] = 11;
	node[3][2]->go[0] = node[3][3];	node[3][2]->goCost[0] = 22;		node[2][3]->go[1] = node[3][3];	node[2][3]->goCost[1] = 15;		node[3][3]->go[2] = node[3][2];	node[3][3]->goCost[2] = 22;		node[3][3]->go[3] = node[2][3];	node[3][3]->goCost[3] = 15;
	node[3][3]->go[0] = node[3][4];	node[3][3]->goCost[0] = 14;		node[3][3]->go[1] = node[4][3];	node[3][3]->goCost[1] = 40;		node[3][4]->go[2] = node[3][3];	node[3][4]->goCost[2] = 14;		node[4][3]->go[3] = node[3][3];	node[4][3]->goCost[3] = 40;
	node[3][4]->go[0] = node[3][5];	node[3][4]->goCost[0] = 15;		node[4][3]->go[1] = node[5][3];	node[4][3]->goCost[1] = 6; 		node[3][5]->go[2] = node[3][4];	node[3][5]->goCost[2] = 15;		node[5][3]->go[3] = node[4][3];	node[5][3]->goCost[3] = 6; 
	node[3][5]->go[0] = node[3][6];	node[3][5]->goCost[0] = 12;		node[5][3]->go[1] = node[6][3];	node[5][3]->goCost[1] = 44;		node[3][6]->go[2] = node[3][5];	node[3][6]->goCost[2] = 12;		node[6][3]->go[3] = node[5][3];	node[6][3]->goCost[3] = 44;
	node[3][6]->go[0] = node[3][7];	node[3][6]->goCost[0] = 15;		node[6][3]->go[1] = node[7][3];	node[6][3]->goCost[1] = 6; 		node[3][7]->go[2] = node[3][6];	node[3][7]->goCost[2] = 15;		node[7][3]->go[3] = node[6][3];	node[7][3]->goCost[3] = 6; 
	node[3][7]->go[0] = node[3][8];	node[3][7]->goCost[0] = 26;		node[7][3]->go[1] = node[8][3];	node[7][3]->goCost[1] = 38;		node[3][8]->go[2] = node[3][7];	node[3][8]->goCost[2] = 26;		node[8][3]->go[3] = node[7][3];	node[8][3]->goCost[3] = 38;
	node[3][8]->go[0] = node[3][9];	node[3][8]->goCost[0] = 12;		node[8][3]->go[1] = node[9][3];	node[8][3]->goCost[1] = 21;		node[3][9]->go[2] = node[3][8];	node[3][9]->goCost[2] = 12;		node[9][3]->go[3] = node[8][3];	node[9][3]->goCost[3] = 21;
	node[4][0]->go[0] = node[4][1];	node[4][0]->goCost[0] = 16;		node[0][4]->go[1] = node[1][4];	node[0][4]->goCost[1] = 9; 		node[4][1]->go[2] = node[4][0];	node[4][1]->goCost[2] = 16;		node[1][4]->go[3] = node[0][4];	node[1][4]->goCost[3] = 9; 
	node[4][1]->go[0] = node[4][2];	node[4][1]->goCost[0] = 10;		node[1][4]->go[1] = node[2][4];	node[1][4]->goCost[1] = 35;		node[4][2]->go[2] = node[4][1];	node[4][2]->goCost[2] = 10;		node[2][4]->go[3] = node[1][4];	node[2][4]->goCost[3] = 35;
	node[4][2]->go[0] = node[4][3];	node[4][2]->goCost[0] = 33;		node[2][4]->go[1] = node[3][4];	node[2][4]->goCost[1] = 5; 		node[4][3]->go[2] = node[4][2];	node[4][3]->goCost[2] = 33;		node[3][4]->go[3] = node[2][4];	node[3][4]->goCost[3] = 5; 
	node[4][3]->go[0] = node[4][4];	node[4][3]->goCost[0] = 7 ;		node[3][4]->go[1] = node[4][4];	node[3][4]->goCost[1] = 23;		node[4][4]->go[2] = node[4][3];	node[4][4]->goCost[2] = 7; 		node[4][4]->go[3] = node[3][4];	node[4][4]->goCost[3] = 23;
	node[4][4]->go[0] = node[4][5];	node[4][4]->goCost[0] = 33;		node[4][4]->go[1] = node[5][4];	node[4][4]->goCost[1] = 22;		node[4][5]->go[2] = node[4][4];	node[4][5]->goCost[2] = 33;		node[5][4]->go[3] = node[4][4];	node[5][4]->goCost[3] = 22;
	node[4][5]->go[0] = node[4][6];	node[4][5]->goCost[0] = 10;		node[5][4]->go[1] = node[6][4];	node[5][4]->goCost[1] = 20;		node[4][6]->go[2] = node[4][5];	node[4][6]->goCost[2] = 10;		node[6][4]->go[3] = node[5][4];	node[6][4]->goCost[3] = 20;
	node[4][6]->go[0] = node[4][7];	node[4][6]->goCost[0] = 47;		node[6][4]->go[1] = node[7][4];	node[6][4]->goCost[1] = 56;		node[4][7]->go[2] = node[4][6];	node[4][7]->goCost[2] = 47;		node[7][4]->go[3] = node[6][4];	node[7][4]->goCost[3] = 56;
	node[4][7]->go[0] = node[4][8];	node[4][7]->goCost[0] = 77;		node[7][4]->go[1] = node[8][4];	node[7][4]->goCost[1] = 5; 		node[4][8]->go[2] = node[4][7];	node[4][8]->goCost[2] = 77;		node[8][4]->go[3] = node[7][4];	node[8][4]->goCost[3] = 5; 
	node[4][8]->go[0] = node[4][9];	node[4][8]->goCost[0] = 46;		node[8][4]->go[1] = node[9][4];	node[8][4]->goCost[1] = 11;		node[4][9]->go[2] = node[4][8];	node[4][9]->goCost[2] = 46;		node[9][4]->go[3] = node[8][4];	node[9][4]->goCost[3] = 11;
	node[5][0]->go[0] = node[5][1];	node[5][0]->goCost[0] = 29;		node[0][5]->go[1] = node[1][5];	node[0][5]->goCost[1] = 29;		node[5][1]->go[2] = node[5][0];	node[5][1]->goCost[2] = 29;		node[1][5]->go[3] = node[0][5];	node[1][5]->goCost[3] = 29;
	node[5][1]->go[0] = node[5][2];	node[5][1]->goCost[0] = 19;		node[1][5]->go[1] = node[2][5];	node[1][5]->goCost[1] = 31;		node[5][2]->go[2] = node[5][1];	node[5][2]->goCost[2] = 19;		node[2][5]->go[3] = node[1][5];	node[2][5]->goCost[3] = 31;
	node[5][2]->go[0] = node[5][3];	node[5][2]->goCost[0] = 22;		node[2][5]->go[1] = node[3][5];	node[2][5]->goCost[1] = 28;		node[5][3]->go[2] = node[5][2];	node[5][3]->goCost[2] = 22;		node[3][5]->go[3] = node[2][5];	node[3][5]->goCost[3] = 28;
	node[5][3]->go[0] = node[5][4];	node[5][3]->goCost[0] = 16;		node[3][5]->go[1] = node[4][5];	node[3][5]->goCost[1] = 33;		node[5][4]->go[2] = node[5][3];	node[5][4]->goCost[2] = 16;		node[4][5]->go[3] = node[3][5];	node[4][5]->goCost[3] = 33;
	node[5][4]->go[0] = node[5][5];	node[5][4]->goCost[0] = 7 ;		node[4][5]->go[1] = node[5][5];	node[4][5]->goCost[1] = 47;		node[5][5]->go[2] = node[5][4];	node[5][5]->goCost[2] = 7; 		node[5][5]->go[3] = node[4][5];	node[5][5]->goCost[3] = 47;
	node[5][5]->go[0] = node[5][6];	node[5][5]->goCost[0] = 21;		node[5][5]->go[1] = node[6][5];	node[5][5]->goCost[1] = 3; 		node[5][6]->go[2] = node[5][5];	node[5][6]->goCost[2] = 21;		node[6][5]->go[3] = node[5][5];	node[6][5]->goCost[3] = 3; 
	node[5][6]->go[0] = node[5][7];	node[5][6]->goCost[0] = 22;		node[6][5]->go[1] = node[7][5];	node[6][5]->goCost[1] = 45;		node[5][7]->go[2] = node[5][6];	node[5][7]->goCost[2] = 22;		node[7][5]->go[3] = node[6][5];	node[7][5]->goCost[3] = 45;
	node[5][7]->go[0] = node[5][8];	node[5][7]->goCost[0] = 24;		node[7][5]->go[1] = node[8][5];	node[7][5]->goCost[1] = 46;		node[5][8]->go[2] = node[5][7];	node[5][8]->goCost[2] = 24;		node[8][5]->go[3] = node[7][5];	node[8][5]->goCost[3] = 46;
	node[5][8]->go[0] = node[5][9];	node[5][8]->goCost[0] = 23;		node[8][5]->go[1] = node[9][5];	node[8][5]->goCost[1] = 41;		node[5][9]->go[2] = node[5][8];	node[5][9]->goCost[2] = 23;		node[9][5]->go[3] = node[8][5];	node[9][5]->goCost[3] = 41;
	node[6][0]->go[0] = node[6][1];	node[6][0]->goCost[0] = 16;		node[0][6]->go[1] = node[1][6];	node[0][6]->goCost[1] = 14;		node[6][1]->go[2] = node[6][0];	node[6][1]->goCost[2] = 16;		node[1][6]->go[3] = node[0][6];	node[1][6]->goCost[3] = 14;
	node[6][1]->go[0] = node[6][2];	node[6][1]->goCost[0] = 31;		node[1][6]->go[1] = node[2][6];	node[1][6]->goCost[1] = 19;		node[6][2]->go[2] = node[6][1];	node[6][2]->goCost[2] = 31;		node[2][6]->go[3] = node[1][6];	node[2][6]->goCost[3] = 19;
	node[6][2]->go[0] = node[6][3];	node[6][2]->goCost[0] = 33;		node[2][6]->go[1] = node[3][6];	node[2][6]->goCost[1] = 36;		node[6][3]->go[2] = node[6][2];	node[6][3]->goCost[2] = 33;		node[3][6]->go[3] = node[2][6];	node[3][6]->goCost[3] = 36;
	node[6][3]->go[0] = node[6][4];	node[6][3]->goCost[0] = 25;		node[3][6]->go[1] = node[4][6];	node[3][6]->goCost[1] = 41;		node[6][4]->go[2] = node[6][3];	node[6][4]->goCost[2] = 25;		node[4][6]->go[3] = node[3][6];	node[4][6]->goCost[3] = 41;
	node[6][4]->go[0] = node[6][5];	node[6][4]->goCost[0] = 31;		node[4][6]->go[1] = node[5][6];	node[4][6]->goCost[1] = 42;		node[6][5]->go[2] = node[6][4];	node[6][5]->goCost[2] = 31;		node[5][6]->go[3] = node[4][6];	node[5][6]->goCost[3] = 42;
	node[6][5]->go[0] = node[6][6];	node[6][5]->goCost[0] = 35;		node[5][6]->go[1] = node[6][6];	node[5][6]->goCost[1] = 43;		node[6][6]->go[2] = node[6][5];	node[6][6]->goCost[2] = 35;		node[6][6]->go[3] = node[5][6];	node[6][6]->goCost[3] = 43;
	node[6][6]->go[0] = node[6][7];	node[6][6]->goCost[0] = 37;		node[6][6]->go[1] = node[7][6];	node[6][6]->goCost[1] = 34;		node[6][7]->go[2] = node[6][6];	node[6][7]->goCost[2] = 37;		node[7][6]->go[3] = node[6][6];	node[7][6]->goCost[3] = 34;
	node[6][7]->go[0] = node[6][8];	node[6][7]->goCost[0] = 69;		node[7][6]->go[1] = node[8][6];	node[7][6]->goCost[1] = 14;		node[6][8]->go[2] = node[6][7];	node[6][8]->goCost[2] = 69;		node[8][6]->go[3] = node[7][6];	node[8][6]->goCost[3] = 14;
	node[6][8]->go[0] = node[6][9];	node[6][8]->goCost[0] = 5 ;		node[8][6]->go[1] = node[9][6];	node[8][6]->goCost[1] = 24;		node[6][9]->go[2] = node[6][8];	node[6][9]->goCost[2] = 5; 		node[9][6]->go[3] = node[8][6];	node[9][6]->goCost[3] = 24;
	node[7][0]->go[0] = node[7][1];	node[7][0]->goCost[0] = 21;		node[0][7]->go[1] = node[1][7];	node[0][7]->goCost[1] = 18;		node[7][1]->go[2] = node[7][0];	node[7][1]->goCost[2] = 21;		node[1][7]->go[3] = node[0][7];	node[1][7]->goCost[3] = 18;
	node[7][1]->go[0] = node[7][2];	node[7][1]->goCost[0] = 24;		node[1][7]->go[1] = node[2][7];	node[1][7]->goCost[1] = 39;		node[7][2]->go[2] = node[7][1];	node[7][2]->goCost[2] = 24;		node[2][7]->go[3] = node[1][7];	node[2][7]->goCost[3] = 39;
	node[7][2]->go[0] = node[7][3];	node[7][2]->goCost[0] = 74;		node[2][7]->go[1] = node[3][7];	node[2][7]->goCost[1] = 68;		node[7][3]->go[2] = node[7][2];	node[7][3]->goCost[2] = 74;		node[3][7]->go[3] = node[2][7];	node[3][7]->goCost[3] = 68;
	node[7][3]->go[0] = node[7][4];	node[7][3]->goCost[0] = 10;		node[3][7]->go[1] = node[4][7];	node[3][7]->goCost[1] = 45;		node[7][4]->go[2] = node[7][3];	node[7][4]->goCost[2] = 10;		node[4][7]->go[3] = node[3][7];	node[4][7]->goCost[3] = 45;
	node[7][4]->go[0] = node[7][5];	node[7][4]->goCost[0] = 20;		node[4][7]->go[1] = node[5][7];	node[4][7]->goCost[1] = 30;		node[7][5]->go[2] = node[7][4];	node[7][5]->goCost[2] = 20;		node[5][7]->go[3] = node[4][7];	node[5][7]->goCost[3] = 30;
	node[7][5]->go[0] = node[7][6];	node[7][5]->goCost[0] = 11;		node[5][7]->go[1] = node[6][7];	node[5][7]->goCost[1] = 44;		node[7][6]->go[2] = node[7][5];	node[7][6]->goCost[2] = 11;		node[6][7]->go[3] = node[5][7];	node[6][7]->goCost[3] = 44;
	node[7][6]->go[0] = node[7][7];	node[7][6]->goCost[0] = 45;		node[6][7]->go[1] = node[7][7];	node[6][7]->goCost[1] = 61;		node[7][7]->go[2] = node[7][6];	node[7][7]->goCost[2] = 45;		node[7][7]->go[3] = node[6][7];	node[7][7]->goCost[3] = 61;
	node[7][7]->go[0] = node[7][8];	node[7][7]->goCost[0] = 32;		node[7][7]->go[1] = node[8][7];	node[7][7]->goCost[1] = 25;		node[7][8]->go[2] = node[7][7];	node[7][8]->goCost[2] = 32;		node[8][7]->go[3] = node[7][7];	node[8][7]->goCost[3] = 25;
	node[7][8]->go[0] = node[7][9];	node[7][8]->goCost[0] = 9 ;		node[8][7]->go[1] = node[9][7];	node[8][7]->goCost[1] = 48;		node[7][9]->go[2] = node[7][8];	node[7][9]->goCost[2] = 9; 		node[9][7]->go[3] = node[8][7];	node[9][7]->goCost[3] = 48;
	node[8][0]->go[0] = node[8][1];	node[8][0]->goCost[0] = 19;		node[0][8]->go[1] = node[1][8];	node[0][8]->goCost[1] = 42;		node[8][1]->go[2] = node[8][0];	node[8][1]->goCost[2] = 19;		node[1][8]->go[3] = node[0][8];	node[1][8]->goCost[3] = 42;
	node[8][1]->go[0] = node[8][2];	node[8][1]->goCost[0] = 34;		node[1][8]->go[1] = node[2][8];	node[1][8]->goCost[1] = 5; 		node[8][2]->go[2] = node[8][1];	node[8][2]->goCost[2] = 34;		node[2][8]->go[3] = node[1][8];	node[2][8]->goCost[3] = 5; 
	node[8][2]->go[0] = node[8][3];	node[8][2]->goCost[0] = 55;		node[2][8]->go[1] = node[3][8];	node[2][8]->goCost[1] = 34;		node[8][3]->go[2] = node[8][2];	node[8][3]->goCost[2] = 55;		node[3][8]->go[3] = node[2][8];	node[3][8]->goCost[3] = 34;
	node[8][3]->go[0] = node[8][4];	node[8][3]->goCost[0] = 34;		node[3][8]->go[1] = node[4][8];	node[3][8]->goCost[1] = 37;		node[8][4]->go[2] = node[8][3];	node[8][4]->goCost[2] = 34;		node[4][8]->go[3] = node[3][8];	node[4][8]->goCost[3] = 37;
	node[8][4]->go[0] = node[8][5];	node[8][4]->goCost[0] = 20;		node[4][8]->go[1] = node[5][8];	node[4][8]->goCost[1] = 8; 		node[8][5]->go[2] = node[8][4];	node[8][5]->goCost[2] = 20;		node[5][8]->go[3] = node[4][8];	node[5][8]->goCost[3] = 8; 
	node[8][5]->go[0] = node[8][6];	node[8][5]->goCost[0] = 35;		node[5][8]->go[1] = node[6][8];	node[5][8]->goCost[1] = 55;		node[8][6]->go[2] = node[8][5];	node[8][6]->goCost[2] = 35;		node[6][8]->go[3] = node[5][8];	node[6][8]->goCost[3] = 55;
	node[8][6]->go[0] = node[8][7];	node[8][6]->goCost[0] = 37;		node[6][8]->go[1] = node[7][8];	node[6][8]->goCost[1] = 9; 		node[8][7]->go[2] = node[8][6];	node[8][7]->goCost[2] = 37;		node[7][8]->go[3] = node[6][8];	node[7][8]->goCost[3] = 9; 
	node[8][7]->go[0] = node[8][8];	node[8][7]->goCost[0] = 45;		node[7][8]->go[1] = node[8][8];	node[7][8]->goCost[1] = 46;		node[8][8]->go[2] = node[8][7];	node[8][8]->goCost[2] = 45;		node[8][8]->go[3] = node[7][8];	node[8][8]->goCost[3] = 46;
	node[8][8]->go[0] = node[8][9];	node[8][8]->goCost[0] = 26;		node[8][8]->go[1] = node[9][8];	node[8][8]->goCost[1] = 50;		node[8][9]->go[2] = node[8][8];	node[8][9]->goCost[2] = 26;		node[9][8]->go[3] = node[8][8];	node[9][8]->goCost[3] = 50;
	node[9][0]->go[0] = node[9][1];	node[9][0]->goCost[0] = 16;		node[0][9]->go[1] = node[1][9];	node[0][9]->goCost[1] = 26;		node[9][1]->go[2] = node[9][0];	node[9][1]->goCost[2] = 16;		node[1][9]->go[3] = node[0][9];	node[1][9]->goCost[3] = 26;
	node[9][1]->go[0] = node[9][2];	node[9][1]->goCost[0] = 22;		node[1][9]->go[1] = node[2][9];	node[1][9]->goCost[1] = 36;		node[9][2]->go[2] = node[9][1];	node[9][2]->goCost[2] = 22;		node[2][9]->go[3] = node[1][9];	node[2][9]->goCost[3] = 36;
	node[9][2]->go[0] = node[9][3];	node[9][2]->goCost[0] = 27;		node[2][9]->go[1] = node[3][9];	node[2][9]->goCost[1] = 30;		node[9][3]->go[2] = node[9][2];	node[9][3]->goCost[2] = 27;		node[3][9]->go[3] = node[2][9];	node[3][9]->goCost[3] = 30;
	node[9][3]->go[0] = node[9][4];	node[9][3]->goCost[0] = 20;		node[3][9]->go[1] = node[4][9];	node[3][9]->goCost[1] = 5; 		node[9][4]->go[2] = node[9][3];	node[9][4]->goCost[2] = 20;		node[4][9]->go[3] = node[3][9];	node[4][9]->goCost[3] = 5; 
	node[9][4]->go[0] = node[9][5];	node[9][4]->goCost[0] = 41;		node[4][9]->go[1] = node[5][9];	node[4][9]->goCost[1] = 26;		node[9][5]->go[2] = node[9][4];	node[9][5]->goCost[2] = 41;		node[5][9]->go[3] = node[4][9];	node[5][9]->goCost[3] = 26;
	node[9][5]->go[0] = node[9][6];	node[9][5]->goCost[0] = 38;		node[5][9]->go[1] = node[6][9];	node[5][9]->goCost[1] = 8; 		node[9][6]->go[2] = node[9][5];	node[9][6]->goCost[2] = 38;		node[6][9]->go[3] = node[5][9];	node[6][9]->goCost[3] = 8; 
	node[9][6]->go[0] = node[9][7];	node[9][6]->goCost[0] = 32;		node[6][9]->go[1] = node[7][9];	node[6][9]->goCost[1] = 53;		node[9][7]->go[2] = node[9][6];	node[9][7]->goCost[2] = 32;		node[7][9]->go[3] = node[6][9];	node[7][9]->goCost[3] = 53;
	node[9][7]->go[0] = node[9][8];	node[9][7]->goCost[0] = 64;		node[7][9]->go[1] = node[8][9];	node[7][9]->goCost[1] = 45;		node[9][8]->go[2] = node[9][7];	node[9][8]->goCost[2] = 64;		node[8][9]->go[3] = node[7][9];	node[8][9]->goCost[3] = 45;
	node[9][8]->go[0] = node[9][9];	node[9][8]->goCost[0] = 23;		node[8][9]->go[1] = node[9][9];	node[8][9]->goCost[1] = 18;		node[9][9]->go[2] = node[9][8];	node[9][9]->goCost[2] = 23;		node[9][9]->go[3] = node[8][9];	node[9][9]->goCost[3] = 18;


	//設定邊界 
	for(i = 0; i < 10; i++)
	{
		node[i][9]->go[0] = NULL; node[i][9]->goCost[0] = 9999;
		node[9][i]->go[1] = NULL; node[9][i]->goCost[1] = 9999;
		node[i][0]->go[2] = NULL; node[i][0]->goCost[2] = 9999;
		node[0][i]->go[3] = NULL; node[0][i]->goCost[3] = 9999;
	}
	
	//初始化起點和終點 
	theStart = node[0][0];												//設定起點 
	theStart->nowCost = 0;												//起點道起點的cost是0 
	theStart->road = 'S';												//起點的名字是'S' 
	theEnd = node[9][9];												//設定終點 
	theEnd->road = 'D';													//終點的名字是'E' 
	
	return theStart;
}

path_ptr initial2()														//第二題的初始化 
{
	//絕大部芬都與initial1相同, 主要差別是大小的不同, 相同的部分就不多加解釋 
	int i, j;
	for(i = 0; i < 100; i++)
	{
		list[i][0] = 9999;
		list[i][1] = 0;
	}
	for(i = 0; i < 10; i++)
		for(j = 0; j < 10; j++)
			node[i][j] = NULL;
	
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			node[i][j] = malloc(sizeof(*node[i][j]));
			node[i][j]->nowCost = 9999;
			node[i][j]->road = 'O';
			node[i][j]->d2Td1 = 10*i+j;
		}
	}
	
	node[0][1]->initialTraffic = 'R';		node[0][1]->firstTraffic = 11;		node[0][1]->traffic = 10;
	node[0][2]->initialTraffic = 'G';		node[0][2]->firstTraffic = 20;		node[0][2]->traffic = 20;
	node[0][3]->initialTraffic = 'R';		node[0][3]->firstTraffic = 7 ;		node[0][3]->traffic = 7;
	node[0][4]->initialTraffic = 'G';		node[0][4]->firstTraffic = 2 ;		node[0][4]->traffic = 3;
	node[1][0]->initialTraffic = 'G';		node[1][0]->firstTraffic = 16;		node[1][0]->traffic = 11;
	node[1][1]->initialTraffic = 'G';		node[1][1]->firstTraffic = 12;		node[1][1]->traffic = 6;
	node[1][2]->initialTraffic = 'R';		node[1][2]->firstTraffic = 15;		node[1][2]->traffic = 3;
	node[1][3]->initialTraffic = 'R';		node[1][3]->firstTraffic = 23;		node[1][3]->traffic = 12;
	node[1][4]->initialTraffic = 'G';		node[1][4]->firstTraffic = 14;		node[1][4]->traffic = 4;
	node[2][0]->initialTraffic = 'G';		node[2][0]->firstTraffic = 29;		node[2][0]->traffic = 8;	
	node[2][1]->initialTraffic = 'R';		node[2][1]->firstTraffic = 13;		node[2][1]->traffic = 14;
	node[2][2]->initialTraffic = 'G';		node[2][2]->firstTraffic = 18;		node[2][2]->traffic = 13;
	node[2][3]->initialTraffic = 'G';		node[2][3]->firstTraffic = 16;		node[2][3]->traffic = 13;
	node[2][4]->initialTraffic = 'R';		node[2][4]->firstTraffic = 6 ;		node[2][4]->traffic = 7;
	node[3][0]->initialTraffic = 'G';		node[3][0]->firstTraffic = 23;		node[3][0]->traffic = 7;
	node[3][1]->initialTraffic = 'R';		node[3][1]->firstTraffic = 6 ;		node[3][1]->traffic = 5;	
	node[3][2]->initialTraffic = 'G';		node[3][2]->firstTraffic = 29;		node[3][2]->traffic = 11;
	node[3][3]->initialTraffic = 'G';		node[3][3]->firstTraffic = 20;		node[3][3]->traffic = 8;
	node[3][4]->initialTraffic = 'R';		node[3][4]->firstTraffic = 6 ;		node[3][4]->traffic = 7;
	node[4][0]->initialTraffic = 'R';		node[4][0]->firstTraffic = 16;		node[4][0]->traffic = 16;
	node[4][1]->initialTraffic = 'G';		node[4][1]->firstTraffic = 19;		node[4][1]->traffic = 4;
	node[4][2]->initialTraffic = 'R';		node[4][2]->firstTraffic = 5 ;		node[4][2]->traffic = 8;
	node[4][3]->initialTraffic = 'R';		node[4][3]->firstTraffic = 17;		node[4][3]->traffic = 5;

	node[0][0]->go[0] = node[0][1];	node[0][0]->goCost[0] = 21;		node[0][0]->go[1] = node[1][0];	node[0][0]->goCost[1] = 3 ;		node[0][1]->go[2] = node[0][0];	node[0][1]->goCost[2] = 21;		node[1][0]->go[3] = node[0][0];	node[1][0]->goCost[3] = 3 ;
	node[0][1]->go[0] = node[0][2];	node[0][1]->goCost[0] = 22;		node[1][0]->go[1] = node[2][0];	node[1][0]->goCost[1] = 45;		node[0][2]->go[2] = node[0][1];	node[0][2]->goCost[2] = 22;		node[2][0]->go[3] = node[1][0];	node[2][0]->goCost[3] = 45;
	node[0][2]->go[0] = node[0][3];	node[0][2]->goCost[0] = 24;		node[2][0]->go[1] = node[3][0];	node[2][0]->goCost[1] = 46;		node[0][3]->go[2] = node[0][2];	node[0][3]->goCost[2] = 24;		node[3][0]->go[3] = node[2][0];	node[3][0]->goCost[3] = 46;
	node[0][3]->go[0] = node[0][4];	node[0][3]->goCost[0] = 23;		node[3][0]->go[1] = node[4][0];	node[3][0]->goCost[1] = 41;		node[0][4]->go[2] = node[0][3];	node[0][4]->goCost[2] = 23;		node[4][0]->go[3] = node[3][0];	node[4][0]->goCost[3] = 41;
	node[1][0]->go[0] = node[1][1];	node[1][0]->goCost[0] = 35;		node[0][1]->go[1] = node[1][1];	node[0][1]->goCost[1] = 43;		node[1][1]->go[2] = node[1][0];	node[1][1]->goCost[2] = 35;		node[1][1]->go[3] = node[0][1];	node[1][1]->goCost[3] = 43;
	node[1][1]->go[0] = node[1][2];	node[1][1]->goCost[0] = 37;		node[1][1]->go[1] = node[2][1];	node[1][1]->goCost[1] = 34;		node[1][2]->go[2] = node[1][1];	node[1][2]->goCost[2] = 37;		node[2][1]->go[3] = node[1][1];	node[2][1]->goCost[3] = 34;
	node[1][2]->go[0] = node[1][3];	node[1][2]->goCost[0] = 69;		node[2][1]->go[1] = node[3][1];	node[2][1]->goCost[1] = 14;		node[1][3]->go[2] = node[1][2];	node[1][3]->goCost[2] = 69;		node[3][1]->go[3] = node[2][1];	node[3][1]->goCost[3] = 14;
	node[1][3]->go[0] = node[1][4];	node[1][3]->goCost[0] = 5 ;		node[3][1]->go[1] = node[4][1];	node[3][1]->goCost[1] = 24;		node[1][4]->go[2] = node[1][3];	node[1][4]->goCost[2] = 5 ;		node[4][1]->go[3] = node[3][1];	node[4][1]->goCost[3] = 24;
	node[2][0]->go[0] = node[2][1];	node[2][0]->goCost[0] = 11;		node[0][2]->go[1] = node[1][2];	node[0][2]->goCost[1] = 44;		node[2][1]->go[2] = node[2][0];	node[2][1]->goCost[2] = 11;		node[1][2]->go[3] = node[0][2];	node[1][2]->goCost[3] = 44;
	node[2][1]->go[0] = node[2][2];	node[2][1]->goCost[0] = 45;		node[1][2]->go[1] = node[2][2];	node[1][2]->goCost[1] = 61;		node[2][2]->go[2] = node[2][1];	node[2][2]->goCost[2] = 45;		node[2][2]->go[3] = node[1][2];	node[2][2]->goCost[3] = 61;
	node[2][2]->go[0] = node[2][3];	node[2][2]->goCost[0] = 32;		node[2][2]->go[1] = node[3][2];	node[2][2]->goCost[1] = 25;		node[2][3]->go[2] = node[2][2];	node[2][3]->goCost[2] = 32;		node[3][2]->go[3] = node[2][2];	node[3][2]->goCost[3] = 25;
	node[2][3]->go[0] = node[2][4];	node[2][3]->goCost[0] = 9 ;		node[3][2]->go[1] = node[4][2];	node[3][2]->goCost[1] = 48;		node[2][4]->go[2] = node[2][3];	node[2][4]->goCost[2] = 9 ;		node[4][2]->go[3] = node[3][2];	node[4][2]->goCost[3] = 48;
	node[3][0]->go[0] = node[3][1];	node[3][0]->goCost[0] = 35;		node[0][3]->go[1] = node[1][3];	node[0][3]->goCost[1] = 55;		node[3][1]->go[2] = node[3][0];	node[3][1]->goCost[2] = 35;		node[1][3]->go[3] = node[0][3];	node[1][3]->goCost[3] = 55;
	node[3][1]->go[0] = node[3][2];	node[3][1]->goCost[0] = 37;		node[1][3]->go[1] = node[2][3];	node[1][3]->goCost[1] = 9 ;		node[3][2]->go[2] = node[3][1];	node[3][2]->goCost[2] = 37;		node[2][3]->go[3] = node[1][3];	node[2][3]->goCost[3] = 9 ;
	node[3][2]->go[0] = node[3][3];	node[3][2]->goCost[0] = 45;		node[2][3]->go[1] = node[3][3];	node[2][3]->goCost[1] = 46;		node[3][3]->go[2] = node[3][2];	node[3][3]->goCost[2] = 45;		node[3][3]->go[3] = node[2][3];	node[3][3]->goCost[3] = 46;
	node[3][3]->go[0] = node[3][4];	node[3][3]->goCost[0] = 26;		node[3][3]->go[1] = node[4][3];	node[3][3]->goCost[1] = 50;		node[3][4]->go[2] = node[3][3];	node[3][4]->goCost[2] = 26;		node[4][3]->go[3] = node[3][3];	node[4][3]->goCost[3] = 50;
	node[4][0]->go[0] = node[4][1];	node[4][0]->goCost[0] = 38;		node[0][4]->go[1] = node[1][4];	node[0][4]->goCost[1] = 8 ;		node[4][1]->go[2] = node[4][0];	node[4][1]->goCost[2] = 38;		node[1][4]->go[3] = node[0][4];	node[1][4]->goCost[3] = 8 ;
	node[4][1]->go[0] = node[4][2];	node[4][1]->goCost[0] = 32;		node[1][4]->go[1] = node[2][4];	node[1][4]->goCost[1] = 53;		node[4][2]->go[2] = node[4][1];	node[4][2]->goCost[2] = 32;		node[2][4]->go[3] = node[1][4];	node[2][4]->goCost[3] = 53;
	node[4][2]->go[0] = node[4][3];	node[4][2]->goCost[0] = 64;		node[2][4]->go[1] = node[3][4];	node[2][4]->goCost[1] = 15;		node[4][3]->go[2] = node[4][2];	node[4][3]->goCost[2] = 64;		node[3][4]->go[3] = node[2][4];	node[3][4]->goCost[3] = 15;
	node[4][3]->go[0] = node[4][4];	node[4][3]->goCost[0] = 23;		node[3][4]->go[1] = node[4][4];	node[3][4]->goCost[1] = 18;		node[4][4]->go[2] = node[4][3];	node[4][4]->goCost[2] = 23;		node[4][4]->go[3] = node[3][4];	node[4][4]->goCost[3] = 18;

	for(i = 0; i < 5; i++)
	{
		node[i][4]->go[0] = NULL; node[i][4]->goCost[0] = 9999;
		node[4][i]->go[1] = NULL; node[4][i]->goCost[1] = 9999;
		node[i][0]->go[2] = NULL; node[i][0]->goCost[2] = 9999;
		node[0][i]->go[3] = NULL; node[0][i]->goCost[3] = 9999;
	}
	
	theStart = node[0][0];
	theStart->nowCost = 0;
	theStart->road = 'S';
	theStart->noTraffic = 1;											//題目的(0, 0)是沒有紅綠燈的 
	theEnd = node[4][4];
	theEnd->road = 'D';

	return theStart;
}

path_ptr initial3()														//第三題的初始化 
{
	//絕大部芬都與initial1相同, 主要差別是大小的不同, 相同的部分就不多加解釋 
	int i, j;
	for(i = 0; i < 100; i++)
	{
		list[i][0] = 9999;
		list[i][1] = 0;
	}
	for(i = 0; i < 10; i++)
		for(j = 0; j < 10; j++)
			node[i][j] = NULL;
	
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			node[i][j] = malloc(sizeof(*node[i][j]));
			node[i][j]->nowCost = 9999;
			node[i][j]->road = 'O';
			node[i][j]->d2Td1 = 10*i+j;
		}
	}
	
	node[0][1]->initialTraffic = 'R';		node[0][1]->firstTraffic = 27;		node[0][1]->traffic =14;
	node[0][2]->initialTraffic = 'R';		node[0][2]->firstTraffic = 2 ;		node[0][2]->traffic =14;
	node[0][3]->initialTraffic = 'G';		node[0][3]->firstTraffic = 24;		node[0][3]->traffic =17;
	node[0][4]->initialTraffic = 'G';		node[0][4]->firstTraffic = 9 ;		node[0][4]->traffic =29;
	node[0][5]->initialTraffic = 'R';		node[0][5]->firstTraffic = 22;		node[0][5]->traffic =12;
	node[1][0]->initialTraffic = 'G';		node[1][0]->firstTraffic = 12;		node[1][0]->traffic =10;
	node[1][1]->initialTraffic = 'R';		node[1][1]->firstTraffic = 17;		node[1][1]->traffic =11;
	node[1][2]->initialTraffic = 'R';		node[1][2]->firstTraffic = 11;		node[1][2]->traffic =10;
	node[1][3]->initialTraffic = 'G';		node[1][3]->firstTraffic = 20;		node[1][3]->traffic =20;
	node[1][4]->initialTraffic = 'R';		node[1][4]->firstTraffic = 7 ;		node[1][4]->traffic =7 ;
	node[1][5]->initialTraffic = 'G';		node[1][5]->firstTraffic = 2 ;		node[1][5]->traffic =3 ;
	node[2][0]->initialTraffic = 'R';		node[2][0]->firstTraffic = 17;		node[2][0]->traffic =2 ;
	node[2][1]->initialTraffic = 'G';		node[2][1]->firstTraffic = 16;		node[2][1]->traffic =11;
	node[2][2]->initialTraffic = 'G';		node[2][2]->firstTraffic = 12;		node[2][2]->traffic =6 ;
	node[2][3]->initialTraffic = 'R';		node[2][3]->firstTraffic = 15;		node[2][3]->traffic =3 ;
	node[2][4]->initialTraffic = 'R';		node[2][4]->firstTraffic = 23;		node[2][4]->traffic =12;
	node[2][5]->initialTraffic = 'G';		node[2][5]->firstTraffic = 14;		node[2][5]->traffic =4 ;
	node[3][0]->initialTraffic = 'G';		node[3][0]->firstTraffic = 8 ;		node[3][0]->traffic =9 ;
	node[3][1]->initialTraffic = 'G';		node[3][1]->firstTraffic = 29;		node[3][1]->traffic =8 ;
	node[3][2]->initialTraffic = 'R';		node[3][2]->firstTraffic = 13;		node[3][2]->traffic =14;
	node[3][3]->initialTraffic = 'G';		node[3][3]->firstTraffic = 18;		node[3][3]->traffic =13;
	node[3][4]->initialTraffic = 'G';		node[3][4]->firstTraffic = 16;		node[3][4]->traffic =13;
	node[3][5]->initialTraffic = 'R';		node[3][5]->firstTraffic = 6 ;		node[3][5]->traffic =7 ;
	node[4][0]->initialTraffic = 'R';		node[4][0]->firstTraffic = 27;		node[4][0]->traffic =19;
	node[4][1]->initialTraffic = 'G';		node[4][1]->firstTraffic = 23;		node[4][1]->traffic =7 ;
	node[4][2]->initialTraffic = 'R';		node[4][2]->firstTraffic = 6 ;		node[4][2]->traffic =5 ;
	node[4][3]->initialTraffic = 'G';		node[4][3]->firstTraffic = 29;		node[4][3]->traffic =11;
	node[4][4]->initialTraffic = 'G';		node[4][4]->firstTraffic = 20;		node[4][4]->traffic =8 ;
	node[4][5]->initialTraffic = 'R';		node[4][5]->firstTraffic = 6 ;		node[4][5]->traffic =7 ;
	node[5][0]->initialTraffic = 'R';		node[5][0]->firstTraffic = 6 ;		node[5][0]->traffic =4 ;
	node[5][1]->initialTraffic = 'R';		node[5][1]->firstTraffic = 16;		node[5][1]->traffic =16;
	node[5][2]->initialTraffic = 'G';		node[5][2]->firstTraffic = 19;		node[5][2]->traffic =4 ;
	node[5][3]->initialTraffic = 'R';		node[5][3]->firstTraffic = 5 ;		node[5][3]->traffic =8 ;
	node[5][4]->initialTraffic = 'R';		node[5][4]->firstTraffic = 17;		node[5][4]->traffic =5 ;

	node[0][0]->go[0] = node[0][1];	node[0][0]->goCost[0] = 33;		node[0][0]->go[1] = node[1][0]; node[0][0]->goCost[1] = 12;		node[0][1]->go[2] = node[0][0];	node[0][1]->goCost[2] = 33;		node[1][0]->go[3] = node[0][0];	node[1][0]->goCost[3] = 12;
	node[0][1]->go[0] = node[0][2];	node[0][1]->goCost[0] = 10;		node[1][0]->go[1] = node[2][0]; node[1][0]->goCost[1] = 20;		node[0][2]->go[2] = node[0][1];	node[0][2]->goCost[2] = 10;		node[2][0]->go[3] = node[1][0];	node[2][0]->goCost[3] = 20;
	node[0][2]->go[0] = node[0][3];	node[0][2]->goCost[0] = 27;		node[2][0]->go[1] = node[3][0]; node[2][0]->goCost[1] = 56;		node[0][3]->go[2] = node[0][2];	node[0][3]->goCost[2] = 27;		node[3][0]->go[3] = node[2][0];	node[3][0]->goCost[3] = 56;
	node[0][3]->go[0] = node[0][4];	node[0][3]->goCost[0] = 15;		node[3][0]->go[1] = node[4][0]; node[3][0]->goCost[1] = 5 ;		node[0][4]->go[2] = node[0][3];	node[0][4]->goCost[2] = 15;		node[4][0]->go[3] = node[3][0];	node[4][0]->goCost[3] = 5 ;
	node[0][4]->go[0] = node[0][5];	node[0][4]->goCost[0] = 17;		node[4][0]->go[1] = node[5][0]; node[4][0]->goCost[1] = 11;		node[0][5]->go[2] = node[0][4];	node[0][5]->goCost[2] = 17;		node[5][0]->go[3] = node[4][0];	node[5][0]->goCost[3] = 11;
	node[1][0]->go[0] = node[1][1];	node[1][0]->goCost[0] = 7 ;		node[0][1]->go[1] = node[1][1]; node[0][1]->goCost[1] = 47;		node[1][1]->go[2] = node[1][0];	node[1][1]->goCost[2] = 7 ;		node[1][1]->go[3] = node[0][1];	node[1][1]->goCost[3] = 47;
	node[1][1]->go[0] = node[1][2];	node[1][1]->goCost[0] = 21;		node[1][1]->go[1] = node[2][1]; node[1][1]->goCost[1] = 3 ;		node[1][2]->go[2] = node[1][1];	node[1][2]->goCost[2] = 21;		node[2][1]->go[3] = node[1][1];	node[2][1]->goCost[3] = 3 ;
	node[1][2]->go[0] = node[1][3];	node[1][2]->goCost[0] = 22;		node[2][1]->go[1] = node[3][1]; node[2][1]->goCost[1] = 45;		node[1][3]->go[2] = node[1][2];	node[1][3]->goCost[2] = 22;		node[3][1]->go[3] = node[2][1];	node[3][1]->goCost[3] = 45;
	node[1][3]->go[0] = node[1][4];	node[1][3]->goCost[0] = 24;		node[3][1]->go[1] = node[4][1]; node[3][1]->goCost[1] = 46;		node[1][4]->go[2] = node[1][3];	node[1][4]->goCost[2] = 24;		node[4][1]->go[3] = node[3][1];	node[4][1]->goCost[3] = 46;
	node[1][4]->go[0] = node[1][5];	node[1][4]->goCost[0] = 23;		node[4][1]->go[1] = node[5][1]; node[4][1]->goCost[1] = 41;		node[1][5]->go[2] = node[1][4];	node[1][5]->goCost[2] = 23;		node[5][1]->go[3] = node[4][1];	node[5][1]->goCost[3] = 41;
	node[2][0]->go[0] = node[2][1];	node[2][0]->goCost[0] = 78;		node[0][2]->go[1] = node[1][2]; node[0][2]->goCost[1] = 68;		node[2][1]->go[2] = node[2][0];	node[2][1]->goCost[2] = 78;		node[1][2]->go[3] = node[0][2];	node[1][2]->goCost[3] = 68;
	node[2][1]->go[0] = node[2][2];	node[2][1]->goCost[0] = 35;		node[1][2]->go[1] = node[2][2]; node[1][2]->goCost[1] = 43;		node[2][2]->go[2] = node[2][1];	node[2][2]->goCost[2] = 35;		node[2][2]->go[3] = node[1][2];	node[2][2]->goCost[3] = 43;
	node[2][2]->go[0] = node[2][3];	node[2][2]->goCost[0] = 37;		node[2][2]->go[1] = node[3][2]; node[2][2]->goCost[1] = 34;		node[2][3]->go[2] = node[2][2];	node[2][3]->goCost[2] = 37;		node[3][2]->go[3] = node[2][2];	node[3][2]->goCost[3] = 34;
	node[2][3]->go[0] = node[2][4];	node[2][3]->goCost[0] = 69;		node[3][2]->go[1] = node[4][2]; node[3][2]->goCost[1] = 14;		node[2][4]->go[2] = node[2][3];	node[2][4]->goCost[2] = 69;		node[4][2]->go[3] = node[3][2];	node[4][2]->goCost[3] = 14;
	node[2][4]->go[0] = node[2][5];	node[2][4]->goCost[0] = 5 ;		node[4][2]->go[1] = node[5][2]; node[4][2]->goCost[1] = 24;		node[2][5]->go[2] = node[2][4];	node[2][5]->goCost[2] = 5 ;		node[5][2]->go[3] = node[4][2];	node[5][2]->goCost[3] = 24;
	node[3][0]->go[0] = node[3][1];	node[3][0]->goCost[0] = 82;		node[0][3]->go[1] = node[1][3]; node[0][3]->goCost[1] = 72;		node[3][1]->go[2] = node[3][0];	node[3][1]->goCost[2] = 82;		node[1][3]->go[3] = node[0][3];	node[1][3]->goCost[3] = 72;
	node[3][1]->go[0] = node[3][2];	node[3][1]->goCost[0] = 11;		node[1][3]->go[1] = node[2][3]; node[1][3]->goCost[1] = 44;		node[3][2]->go[2] = node[3][1];	node[3][2]->goCost[2] = 11;		node[2][3]->go[3] = node[1][3];	node[2][3]->goCost[3] = 44;
	node[3][2]->go[0] = node[3][3];	node[3][2]->goCost[0] = 45;		node[2][3]->go[1] = node[3][3]; node[2][3]->goCost[1] = 61;		node[3][3]->go[2] = node[3][2];	node[3][3]->goCost[2] = 45;		node[3][3]->go[3] = node[2][3];	node[3][3]->goCost[3] = 61;
	node[3][3]->go[0] = node[3][4];	node[3][3]->goCost[0] = 32;		node[3][3]->go[1] = node[4][3]; node[3][3]->goCost[1] = 25;		node[3][4]->go[2] = node[3][3];	node[3][4]->goCost[2] = 32;		node[4][3]->go[3] = node[3][3];	node[4][3]->goCost[3] = 25;
	node[3][4]->go[0] = node[3][5];	node[3][4]->goCost[0] = 9 ;		node[4][3]->go[1] = node[5][3]; node[4][3]->goCost[1] = 48;		node[3][5]->go[2] = node[3][4];	node[3][5]->goCost[2] = 9 ;		node[5][3]->go[3] = node[4][3];	node[5][3]->goCost[3] = 48;
	node[4][0]->go[0] = node[4][1];	node[4][0]->goCost[0] = 64;		node[0][4]->go[1] = node[1][4]; node[0][4]->goCost[1] = 88;		node[4][1]->go[2] = node[4][0];	node[4][1]->goCost[2] = 64;		node[1][4]->go[3] = node[0][4];	node[1][4]->goCost[3] = 88;
	node[4][1]->go[0] = node[4][2];	node[4][1]->goCost[0] = 35;		node[1][4]->go[1] = node[2][4]; node[1][4]->goCost[1] = 55;		node[4][2]->go[2] = node[4][1];	node[4][2]->goCost[2] = 35;		node[2][4]->go[3] = node[1][4];	node[2][4]->goCost[3] = 55;
	node[4][2]->go[0] = node[4][3];	node[4][2]->goCost[0] = 37;		node[2][4]->go[1] = node[3][4]; node[2][4]->goCost[1] = 9 ;		node[4][3]->go[2] = node[4][2];	node[4][3]->goCost[2] = 37;		node[3][4]->go[3] = node[2][4];	node[3][4]->goCost[3] = 9 ;
	node[4][3]->go[0] = node[4][4];	node[4][3]->goCost[0] = 45;		node[3][4]->go[1] = node[4][4]; node[3][4]->goCost[1] = 46;		node[4][4]->go[2] = node[4][3];	node[4][4]->goCost[2] = 45;		node[4][4]->go[3] = node[3][4];	node[4][4]->goCost[3] = 46;
	node[4][4]->go[0] = node[4][5];	node[4][4]->goCost[0] = 26;		node[4][4]->go[1] = node[5][4]; node[4][4]->goCost[1] = 50;		node[4][5]->go[2] = node[4][4];	node[4][5]->goCost[2] = 26;		node[5][4]->go[3] = node[4][4];	node[5][4]->goCost[3] = 50;
	node[5][0]->go[0] = node[5][1];	node[5][0]->goCost[0] = 55;		node[0][5]->go[1] = node[1][5]; node[0][5]->goCost[1] = 94;		node[5][1]->go[2] = node[5][0];	node[5][1]->goCost[2] = 55;		node[1][5]->go[3] = node[0][5];	node[1][5]->goCost[3] = 94;
	node[5][1]->go[0] = node[5][2];	node[5][1]->goCost[0] = 38;		node[1][5]->go[1] = node[2][5]; node[1][5]->goCost[1] = 8 ;		node[5][2]->go[2] = node[5][1];	node[5][2]->goCost[2] = 38;		node[2][5]->go[3] = node[1][5];	node[2][5]->goCost[3] = 8 ;
	node[5][2]->go[0] = node[5][3];	node[5][2]->goCost[0] = 32;		node[2][5]->go[1] = node[3][5]; node[2][5]->goCost[1] = 53;		node[5][3]->go[2] = node[5][2];	node[5][3]->goCost[2] = 32;		node[3][5]->go[3] = node[2][5];	node[3][5]->goCost[3] = 53;
	node[5][3]->go[0] = node[5][4];	node[5][3]->goCost[0] = 64;		node[3][5]->go[1] = node[4][5]; node[3][5]->goCost[1] = 15;		node[5][4]->go[2] = node[5][3];	node[5][4]->goCost[2] = 64;		node[4][5]->go[3] = node[3][5];	node[4][5]->goCost[3] = 15;
	node[5][4]->go[0] = node[5][5];	node[5][4]->goCost[0] = 23;		node[4][5]->go[1] = node[5][5]; node[4][5]->goCost[1] = 18;		node[5][5]->go[2] = node[5][4];	node[5][5]->goCost[2] = 23;		node[5][5]->go[3] = node[4][5];	node[5][5]->goCost[3] = 18;
	
	for(i = 0; i < 6; i++)
	{
		node[i][5]->go[0] = NULL; node[i][5]->goCost[0] = 9999;
		node[5][i]->go[1] = NULL; node[5][i]->goCost[1] = 9999;
		node[i][0]->go[2] = NULL; node[i][0]->goCost[2] = 9999;
		node[0][i]->go[3] = NULL; node[0][i]->goCost[3] = 9999;
	}
	
	theStart = node[0][0];
	theStart->road = 'S';
	theStart->nowCost = 0;
	theStart->noTraffic = 1;											//題目的(0, 0)是沒有紅綠燈的 
	theEnd = node[5][5];
	theEnd->road = 'D';
		
	return theStart; 
} 

void walk(path_ptr ptr)													//從起點走到終點的涵式 (核心演算法) 
{
	list[theStart->d2Td1][0] = 0;										//設定起點到起點的距離是0 
	list[theStart->d2Td1][1] = 1;										//0是起點到起點的最短路徑 
	path_ptr queue[100];												//每次會讀一個點, 並加入一個最佳解 
	queue[0] = ptr;														//設定第一個點為起點 
	
	int i, k, j, rear = 1, mini;
	for(i = 0; ; i++)													//讀入剛新增的點 
	{
		if(i > 500)														//超過目標步數太多, 顯示有bug 
			printf("bug\n");
			
		if(queue[i]->road == 'D')										//若該點為終點結束涵式 (不會有問題, 因為被讀進來表示透過演算法那已經是最小值了, 所以就算有些點沒拜訪過也不會有影響 
		{
			find(theEnd);												//尋找從終點到起點路線 
			return;														//結束涵式 
		}
			
		for(k = 0; k < 4; k++)
			if(queue[i]->go[k])											//檢查該點四個方向能不能走 
			{
				//這裡是尋找較短路徑, 但無法確認是否為最短路徑 
				// 	  該點的下一個點的cost 	 >     該點的cost    +  該點往下點的cost   +  紅燈的停留時間(若是綠燈為0) 
				if (queue[i]->go[k]->nowCost > queue[i]->nowCost + queue[i]->goCost[k] + traffic(queue[i]))
				{
					// 該點的下一個點的cost  =     該點的cost    +  該點往下點的cost   +  紅燈的停留時間(若是綠燈為0) 
					queue[i]->go[k]->nowCost = queue[i]->nowCost + queue[i]->goCost[k] + traffic(queue[i]);
					//更新該點在list裡面起點到該點的cost 
					list[queue[i]->go[k]->d2Td1][0] = queue[i]->go[k]->nowCost;
					//記錄該點的下個點的來源(該點) 
					queue[i]->go[k]->come = queue[i];
				}
			}
		//mini是為了尋找下一個有最佳點的解(終點通常是會在最後才是, 所以可以用來和其他點比較) 
		mini = theEnd->d2Td1;
		for(j = 0; j < 100; j++)
			//將目前最小的點找出, 但非最佳解 
			if(list[mini][0] > list[j][0] && list[j][1] == 0)		
				mini = j;
		
		//將得出的最佳解放入queue成為下一個要讀的點 
		queue[rear] = node[mini/10][mini%10];
		//紀錄該點為最佳解 
		list[mini][1] = 1;
		//將queue的最後位置移動 
		rear++;
	}
	return;
}

void find (path_ptr ptr)												//從終點走到起點的涵式 
{
	//若輸入點是終點, 直接呼叫終點的上一個點 
	if(ptr->road == 'D')
		return find(ptr->come);
	//若輸入點是起點, 結束涵式 
	if(ptr->road == 'S')
		return;
	//若輸入的點是一般的點, 將路名改成'@', 並在呼叫上一個點 
	else
	{
		ptr->road = '@';
		return find(ptr->come);
	}
	
}

void printMap (int size)												//把地圖印出來的涵式 
{
	int i, j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
			printf("%c-", node[i][j]->road);							//把路名列印出來 
		printf("\b \n");
		if (i != size - 1)
		{
			for(j = 0; j < size; j++)
				printf("| ");
			printf("\n");
		}
	}
	
	printf("\n");
	return;
}

int printCost (path_ptr ptr)											//把目前的cost印出的涵式 
{
	printf("花費時間為 : %d\n\n\n", ptr->nowCost);						//列印出現在cost 
	
	int i, j;
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			node[i][j]->road = 'O';										//把道路還原 
	
	return ptr->nowCost;												//回傳現在cost 
}

int traffic(path_ptr ptr)												//計算該點紅綠燈狀態的涵式 
{
	if(ptr)
	{
		if(ptr->noTraffic)												//noTraffic == 1, 表示該點沒有紅綠燈回傳要等0秒 
			return 0;

		//時間尚未過一開始的倒數 
		//該點的時間(=cost) + 起始時間 - 紅綠的初始時間 
		if(ptr->nowCost + startTime - ptr->firstTraffic < 0)
		{
			//若一開始是紅燈, 計算要等多久 
			if(ptr->initialTraffic == 'R')	
				return ptr->firstTraffic - ptr->nowCost;
			//一開始是綠燈 
			return 0;
		}

		int temp;
		//判斷現在的時間是落在龍綠燈循環的前半段還是後半段 ( R/G  G/R) 
		//	 點的時間(=cost)  +  起始時間 -  紅綠燈的起始時間   %   (紅燈+綠燈的持續時間)   
		temp = ( ptr->nowCost + startTime - ptr->firstTraffic ) % (ptr->traffic*2) ;

		//若是在前半段 
		if ( temp < ptr->traffic )
		{
			//一開始是綠燈, 則現在是紅燈, 回傳要等的時間 
			if ( ptr->initialTraffic == 'G' )
				return ptr->traffic - temp;
			//一開始是紅燈, 現在是綠燈 
			return 0;
		}
		//若是在後半段 
		else
		{
			//一開始是紅燈, 現在還是紅燈, 回傳要等的時間 
			if ( ptr->initialTraffic == 'R' )
				return ptr->traffic * 2 - temp;
			//一開始是綠燈, 現在還是綠燈 
			return 0;
		}
	}
}

path_ptr newStart (int i, int j)										//更新起點的涵式 
{
	theStart->road = 'O';												//將原起點還原 
	theStart->nowCost = 9999;
	theStart = node[i][j];												//將新起點更新 
	theStart->road = 'S';
	theStart->nowCost = 0;
	
	return theStart;
}

path_ptr newEnd (int i, int j)											//更新終點的涵式 
{
	if(theEnd->d2Td1 != theStart->d2Td1)								//確保要還原的點不是新的起點 
	{
		theEnd->road = 'O';												//將原終點還原 
		theEnd->nowCost = 9999;
	}
	theEnd = node[i][j];												//將新終點更新 
	theEnd->road = 'D';
	theEnd->nowCost = 9999;
	
	return theEnd;
}

void clean (int size)													//歸零每點路徑的涵式 
{
	int i, j;
	for(i = 0; i < 100; i++)
	{
		list[i][0] = 9999;												//將表還原 
		list[i][1] = 0;
	}

	for(i = 0; i < size; i ++)
		for(j = 0; j < size; j++)
			node[i][j]->nowCost = 9999;									//還原每點 
			
	theStart->nowCost = 0;												//更正起點 
}

