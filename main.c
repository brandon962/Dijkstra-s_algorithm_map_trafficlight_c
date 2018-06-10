//branodn962@gmail.com 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node *path_ptr;											//�ڥ�������W���@�~����k�ӫإߧڪ��a��					
typedef struct Node 
{							
	char road;															//����S, O, D, @ 
	path_ptr come;														//�����W�@���I, �bfind�[�����i�H�����q���I��^�_�I 
	path_ptr go[4];														//�������I�|�Ӥ�V�s���쪺�I�O��, 0�V�k, 1�V�U, 2�V��, 3�V�W 
	int goCost[4];														//�������I���|�Ӥ�V��cost��, �W�h�P�W 
	int nowCost;														//�_�I����I��cost, �w�]9999 
	int d2Td1;															//�N�G���y����@��, EX: node[1][2]->d2Td3 = 12; 
	
	int noTraffic;														//�w�]���@, ��ܸ��I�S������O 
	int firstTraffic;													//�̪����O���˼� 
	char initialTraffic;												//�̪����O�����A 
	int traffic;														//����O���`���ɶ� 
}; 

path_ptr node [10][10];													//�G���a�� 
int list[100][2];														//�f�t�t��k�Ϊ��@���a�� 
path_ptr theEnd;														//�Ӧ����ʪ����I 
path_ptr theStart;														//�Ӧ����ʪ��_�I 
int startTime = 0;														//�Ӧ����ʪ��_�l�ɶ�(�b�ĤT�D�C�����ʪ��_�l�ɶ��|�֥[ 

void question1();														//�Ĥ@�D�����e 
void question2();														//�ĤG�D�����e 
void question3();														//�ĤT�D�����e 
path_ptr initial1();													//�Ĥ@�D����l�� 
path_ptr initial2();													//�ĤG�D����l�� 
path_ptr initial3();													//�ĤT�D����l�� 
void walk(path_ptr);													//�q�_�I�����I�����[�� 
void find(path_ptr);													//�q���I���_�I�����[�� 
void printMap(int);														//��a�ϦL�X�Ӫ��[�� 
int printCost(path_ptr);												//��ثe��cost�L�X�Ӫ��[�� 
int traffic(path_ptr);													//�p����I����O���A���[�� 
path_ptr newStart(int,int);												//��s�_�I���[�� 
path_ptr newEnd(int,int);												//��s���I���[�� 
void clean (int);														//�k�s�C�I���|���[�� 
 
int main(int argc, char *argv[]) 
{
	question1();														//�Ĥ@�D 
	question2();														//�ĤG�D 
	question3();														//�ĤT�D 

	return 0;
}

void question1()														//�Ĥ@�D�����e 
{
	printf("�Ĥ@�D\n");
	theStart = initial1();												//��l�ư_�I 
	printf("�ثe�a��\n");
	printMap(10);														//�C�L�X�����e���_�I 
	walk(theStart);														//��ڦ樫 (���K�M��q���I���_�I���� 
	printf("\n���|�a��\n");
	printMap(10);														//�C�L�����᪺�� 
	printCost(theEnd);													//�C�Lcost 
	system("PAUSE");
	system("CLS");
}

void question2()														//�ĤG�D�����e 
{
	printf("�ĤG�D\n");
	theStart = initial2();												//��l�ư_�I 
	printf("�ثe�a��\n");
	printMap(5);														//�C�L�X�����e���_�I 
	walk(theStart);														//��ڦ樫 (���K�M��q���I���_�I���� 
	printf("\n���|�a��\n");
	printMap(5);														//�C�L�����᪺�� 
	printCost(theEnd);													//�C�Lcost 
	system("PAUSE");
	system("CLS");
}

void question3()														//�ĤT�D�����e 
{
	printf("�ĤT�D\n");
	int tempCost = 0;
	theStart = initial3();												//��l�ư_�I 
	printf("�ثe�a��\n");												
	printMap(6);														//�C�L�X�����e���_�I 
	theStart = newStart(0,0);											//�]�߰_�I 
	theEnd = newEnd(2,0);												//�]�߲��I 
	clean(6);															//�M�Ť��e�p�⪺���u 
	walk(theStart);														//��ڦ樫 
	printf("\n���q���|�a��\n");
	printMap(6);														//�C�L���| 
	tempCost += theEnd->nowCost;										//�p���`cost 
	startTime = tempCost;												//�վ�_�l�ɶ�(�C���@�q�_�l�ɶ��N�n�[�W�q�����`cost) 
	printCost(theEnd);													//�C�Lcost 
	printf("�ثe��O�� : %d\n\n", tempCost);
	
	theStart = newStart(2,0);											//���U�ӦP�W 
	theEnd = newEnd(1,1);
	clean(6);
	walk(theStart);
	printf("\n���q���|�a��\n");
	printMap(6);
	tempCost += theEnd->nowCost;
	startTime = tempCost;
	printCost(theEnd);
	printf("�ثe��O�� : %d\n", tempCost);

	theStart = newStart(1,1);
	theEnd = newEnd(0,5);
	clean(6);
	walk(theStart);
	printf("\n���q���|�a��\n");
	printMap(6);
	tempCost += theEnd->nowCost;
	startTime = tempCost;
	printCost(theEnd);
	printf("�ثe��O�� : %d\n", tempCost);

	theStart = newStart(0,5);
	theEnd = newEnd(1,1);
	clean(6);
	walk(theStart);
	printf("\n���q���|�a��\n");
	printMap(6);
	tempCost += theEnd->nowCost;
	startTime = tempCost;
	printCost(theEnd);
	printf("�ثe��O�� : %d\n", tempCost);

	theStart = newStart(1,1);
	theEnd = newEnd(5,5);
	clean(6);
	walk(theStart);
	printf("\n���q���|�a��\n");
	printMap(6);
	tempCost += theEnd->nowCost;
	startTime = tempCost;
	printCost(theEnd);
	printf("�ثe��O�� : %d\n", tempCost);
}

path_ptr initial1()														//�Ĥ@�D����l��
{
	int i, j, k;
	for(i = 0; i < 100; i++)											//��list����l�ƪ��ʧ@ 
	{
		list[i][0] = 9999;												//list���Ĥ@�C�s��_�I����I(list[�@���y��][0])���Z�� 
		list[i][1] = 0;													//�ĤG�C�����O�_�������I���̤p��(Dijkstra��s algorithm�t��k�����W��) 
	}
	for(i = 0; i < 10; i++)
		for(j = 0; j < 10; j++)
			node[i][j] = NULL;											//�k�s�a�� 
	
	for(i = 0; i < 10; i++)
		for(j = 0; j < 10; j++)
		{
			node[i][j] = malloc(sizeof(*node[i][j]));					//�N�a�Ϫ�l�� 
			node[i][j]->road = 'O';										//�w�]���O��('O') 
			node[i][j]->nowCost = 9999;									//�w�]�M�_�I���Z�����O9999 
			node[i][j]->d2Td1 = 10*i+j;									//�]�w�G����@������ 
			node[i][j]->noTraffic = 1;									//�w�]���S������O 
		}
	
	//�H�U�O�ϥ�subime���h��P�ɽs�g�ӼзǤƿ�J 
	//0��ܩ���, 1��ܩ��U, 2��ܩ��k, 3��ܩ��W 
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


	//�]�w��� 
	for(i = 0; i < 10; i++)
	{
		node[i][9]->go[0] = NULL; node[i][9]->goCost[0] = 9999;
		node[9][i]->go[1] = NULL; node[9][i]->goCost[1] = 9999;
		node[i][0]->go[2] = NULL; node[i][0]->goCost[2] = 9999;
		node[0][i]->go[3] = NULL; node[0][i]->goCost[3] = 9999;
	}
	
	//��l�ư_�I�M���I 
	theStart = node[0][0];												//�]�w�_�I 
	theStart->nowCost = 0;												//�_�I�D�_�I��cost�O0 
	theStart->road = 'S';												//�_�I���W�r�O'S' 
	theEnd = node[9][9];												//�]�w���I 
	theEnd->road = 'D';													//���I���W�r�O'E' 
	
	return theStart;
}

path_ptr initial2()														//�ĤG�D����l�� 
{
	//���j���ⳣ�Pinitial1�ۦP, �D�n�t�O�O�j�p�����P, �ۦP�������N���h�[���� 
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
	theStart->noTraffic = 1;											//�D�ت�(0, 0)�O�S������O�� 
	theEnd = node[4][4];
	theEnd->road = 'D';

	return theStart;
}

path_ptr initial3()														//�ĤT�D����l�� 
{
	//���j���ⳣ�Pinitial1�ۦP, �D�n�t�O�O�j�p�����P, �ۦP�������N���h�[���� 
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
	theStart->noTraffic = 1;											//�D�ت�(0, 0)�O�S������O�� 
	theEnd = node[5][5];
	theEnd->road = 'D';
		
	return theStart; 
} 

void walk(path_ptr ptr)													//�q�_�I������I���[�� (�֤ߺt��k) 
{
	list[theStart->d2Td1][0] = 0;										//�]�w�_�I��_�I���Z���O0 
	list[theStart->d2Td1][1] = 1;										//0�O�_�I��_�I���̵u���| 
	path_ptr queue[100];												//�C���|Ū�@���I, �å[�J�@�ӳ̨θ� 
	queue[0] = ptr;														//�]�w�Ĥ@���I���_�I 
	
	int i, k, j, rear = 1, mini;
	for(i = 0; ; i++)													//Ū�J��s�W���I 
	{
		if(i > 500)														//�W�L�ؼШB�ƤӦh, ��ܦ�bug 
			printf("bug\n");
			
		if(queue[i]->road == 'D')										//�Y���I�����I�����[�� (���|�����D, �]���QŪ�i�Ӫ�ܳz�L�t��k���w�g�O�̤p�ȤF, �ҥH�N�⦳���I�S���X�L�]���|���v�T 
		{
			find(theEnd);												//�M��q���I��_�I���u 
			return;														//�����[�� 
		}
			
		for(k = 0; k < 4; k++)
			if(queue[i]->go[k])											//�ˬd���I�|�Ӥ�V�ण�ਫ 
			{
				//�o�̬O�M����u���|, ���L�k�T�{�O�_���̵u���| 
				// 	  ���I���U�@���I��cost 	 >     ���I��cost    +  ���I���U�I��cost   +  ���O�����d�ɶ�(�Y�O��O��0) 
				if (queue[i]->go[k]->nowCost > queue[i]->nowCost + queue[i]->goCost[k] + traffic(queue[i]))
				{
					// ���I���U�@���I��cost  =     ���I��cost    +  ���I���U�I��cost   +  ���O�����d�ɶ�(�Y�O��O��0) 
					queue[i]->go[k]->nowCost = queue[i]->nowCost + queue[i]->goCost[k] + traffic(queue[i]);
					//��s���I�blist�̭��_�I����I��cost 
					list[queue[i]->go[k]->d2Td1][0] = queue[i]->go[k]->nowCost;
					//�O�����I���U���I���ӷ�(���I) 
					queue[i]->go[k]->come = queue[i];
				}
			}
		//mini�O���F�M��U�@�Ӧ��̨��I����(���I�q�`�O�|�b�̫�~�O, �ҥH�i�H�ΨөM��L�I���) 
		mini = theEnd->d2Td1;
		for(j = 0; j < 100; j++)
			//�N�ثe�̤p���I��X, ���D�̨θ� 
			if(list[mini][0] > list[j][0] && list[j][1] == 0)		
				mini = j;
		
		//�N�o�X���̨θѩ�Jqueue�����U�@�ӭnŪ���I 
		queue[rear] = node[mini/10][mini%10];
		//�������I���̨θ� 
		list[mini][1] = 1;
		//�Nqueue���̫��m���� 
		rear++;
	}
	return;
}

void find (path_ptr ptr)												//�q���I����_�I���[�� 
{
	//�Y��J�I�O���I, �����I�s���I���W�@���I 
	if(ptr->road == 'D')
		return find(ptr->come);
	//�Y��J�I�O�_�I, �����[�� 
	if(ptr->road == 'S')
		return;
	//�Y��J���I�O�@�몺�I, �N���W�令'@', �æb�I�s�W�@���I 
	else
	{
		ptr->road = '@';
		return find(ptr->come);
	}
	
}

void printMap (int size)												//��a�ϦL�X�Ӫ��[�� 
{
	int i, j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
			printf("%c-", node[i][j]->road);							//����W�C�L�X�� 
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

int printCost (path_ptr ptr)											//��ثe��cost�L�X���[�� 
{
	printf("��O�ɶ��� : %d\n\n\n", ptr->nowCost);						//�C�L�X�{�bcost 
	
	int i, j;
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			node[i][j]->road = 'O';										//��D���٭� 
	
	return ptr->nowCost;												//�^�ǲ{�bcost 
}

int traffic(path_ptr ptr)												//�p����I����O���A���[�� 
{
	if(ptr)
	{
		if(ptr->noTraffic)												//noTraffic == 1, ��ܸ��I�S������O�^�ǭn��0�� 
			return 0;

		//�ɶ��|���L�@�}�l���˼� 
		//���I���ɶ�(=cost) + �_�l�ɶ� - ���񪺪�l�ɶ� 
		if(ptr->nowCost + startTime - ptr->firstTraffic < 0)
		{
			//�Y�@�}�l�O���O, �p��n���h�[ 
			if(ptr->initialTraffic == 'R')	
				return ptr->firstTraffic - ptr->nowCost;
			//�@�}�l�O��O 
			return 0;
		}

		int temp;
		//�P�_�{�b���ɶ��O���b�s��O�`�����e�b�q�٬O��b�q ( R/G  G/R) 
		//	 �I���ɶ�(=cost)  +  �_�l�ɶ� -  ����O���_�l�ɶ�   %   (���O+��O������ɶ�)   
		temp = ( ptr->nowCost + startTime - ptr->firstTraffic ) % (ptr->traffic*2) ;

		//�Y�O�b�e�b�q 
		if ( temp < ptr->traffic )
		{
			//�@�}�l�O��O, �h�{�b�O���O, �^�ǭn�����ɶ� 
			if ( ptr->initialTraffic == 'G' )
				return ptr->traffic - temp;
			//�@�}�l�O���O, �{�b�O��O 
			return 0;
		}
		//�Y�O�b��b�q 
		else
		{
			//�@�}�l�O���O, �{�b�٬O���O, �^�ǭn�����ɶ� 
			if ( ptr->initialTraffic == 'R' )
				return ptr->traffic * 2 - temp;
			//�@�}�l�O��O, �{�b�٬O��O 
			return 0;
		}
	}
}

path_ptr newStart (int i, int j)										//��s�_�I���[�� 
{
	theStart->road = 'O';												//�N��_�I�٭� 
	theStart->nowCost = 9999;
	theStart = node[i][j];												//�N�s�_�I��s 
	theStart->road = 'S';
	theStart->nowCost = 0;
	
	return theStart;
}

path_ptr newEnd (int i, int j)											//��s���I���[�� 
{
	if(theEnd->d2Td1 != theStart->d2Td1)								//�T�O�n�٭쪺�I���O�s���_�I 
	{
		theEnd->road = 'O';												//�N����I�٭� 
		theEnd->nowCost = 9999;
	}
	theEnd = node[i][j];												//�N�s���I��s 
	theEnd->road = 'D';
	theEnd->nowCost = 9999;
	
	return theEnd;
}

void clean (int size)													//�k�s�C�I���|���[�� 
{
	int i, j;
	for(i = 0; i < 100; i++)
	{
		list[i][0] = 9999;												//�N���٭� 
		list[i][1] = 0;
	}

	for(i = 0; i < size; i ++)
		for(j = 0; j < size; j++)
			node[i][j]->nowCost = 9999;									//�٭�C�I 
			
	theStart->nowCost = 0;												//�󥿰_�I 
}

