#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#include <conio.h>
#include <windows.h>
#include <versionhelpers.h>
#include <winternl.h>

/*#include "defs.h"
#include "ntDefs.h"
#include "defs2.h"*/

#define INF 100000
#define UNRIGHT_PASSWORD -2
#define OTLADCHIK -3
using namespace std;

int numEd = 0;
unsigned char password[20] = { '\0' };
char *check_pass = nullptr;
constexpr size_t length_of_check_func = 125;
constexpr unsigned long real_check_sum = 0x39aa;


typedef NTSTATUS(NTAPI* pfnNtQueryInformationProcess)(
	_In_ HANDLE ProcessHandle,
	_In_ UINT ProcessInformationClass,
	_Out_ PVOID ProcessInformation,
	_In_ ULONG ProcessInformationLength,
	_Out_opt_ PULONG ReturnLength
	);


/*void fIsDebuggerPresent() {
	if (IsDebuggerPresent())
	{
		printf("Debugger detected\n");
		exit(OTLADCHIK);
	}
	else
		printf("Debugger not detected\n");
}
*/
// 3.3
// reference: "Anti-Unpacker Tricks" by Peter Ferrie
/*void fCheckRemoteDebuggerPresent() {

	BOOL isdbg = FALSE;

	CheckRemoteDebuggerPresent(GetCurrentProcess(), &isdbg);
	if (isdbg)
	{
		printf("Debugger detected\n");
		exit(OTLADCHIK);
	}
	else
		printf("Debugger not detected\n");
}
*/


// 3.6
// reference: "Anti-Unpacker Tricks" by Peter Ferrie
/*
void pDebugObjectHandle() {

	HANDLE proc;
	NTSTATUS ntStatus;
	HANDLE hDebugHandle = NULL;
	proc = GetCurrentProcess();

	pfnNtQueryInformationProcess NtQueryInformationProcess = NULL;
	HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));
	NtQueryInformationProcess = (pfnNtQueryInformationProcess)GetProcAddress(hNtDll, "NtQueryInformationProcess");
	UINT ProcessDebugObjectHandle = 0x1E;

	ntStatus = NtQueryInformationProcess(proc, ProcessDebugObjectHandle, &hDebugHandle, sizeof(hDebugHandle), NULL);
	if (hDebugHandle)
	{
		printf("Debugger detected\n");
		exit(OTLADCHIK);
		return;
	}
	else
	{
		printf("Debugger not detected\n");
		return;
	}
}



// 3.7
// reference: "Anti-Unpacker Tricks" by Peter Ferrie
void pProcessDebugFlags() {

	HANDLE proc;
	NTSTATUS ntStatus;
	HANDLE hDebugFlags = NULL;
	proc = GetCurrentProcess();

	pfnNtQueryInformationProcess NtQueryInformationProcess = NULL;
	HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));
	NtQueryInformationProcess = (pfnNtQueryInformationProcess)GetProcAddress(hNtDll, "NtQueryInformationProcess");
	UINT ProcessDebugFlags = 0x1F;
	ntStatus = NtQueryInformationProcess(proc, ProcessDebugFlags, &hDebugFlags, sizeof(hDebugFlags), NULL);
	if (hDebugFlags == FALSE)
		printf("Debugger detected\n");
	else
		printf("Debugger not detected\n");
}

*/

void XorAlg(const int size)
{
	int in = 0;
	for (in = 0; in < size; in++)
	{
		password[in] ^= 'A';
	}
}

bool CheckPass()
{
	if (check_pass == nullptr)
	{
		return false;
	}
	if (strcmp((const char*)password, check_pass))
	{
		return false;
	}
	return true;
}

char * key()
{
	
	ifstream input;
	input.open("password.txt");
	if (!input.is_open())
	{
		return nullptr;
	}
	char password_[20] = { '\0' };
	input.getline(password_, 20);
	size_t size = strlen(password_);
	for (size_t i = 0; i < size; i++)
	{
		password[i] = password_[i];
	}
	XorAlg(size);
	_cputs("Enter password:\n");
	//char check[50] = { '\0' };
	char* check = new char[50];
	size_t length = 50;
	_cgets_s(check, 50, &length);
	check[length] = '\0';
	input.close();
	return check;
}

unsigned long CrcCalculation()
{
	bool (*ptr)(void);
	ptr = &CheckPass;

	unsigned long check_sum = 0;
	for (size_t i = 0; i < length_of_check_func; i++)
	{
		check_sum += *(unsigned char*)((char*)ptr + i);
	}
	return check_sum;
}


char get_input(const char* mask)
{
	char res = 0;
	while (1) {
		res = tolower(getchar());
		while (getchar() != '\n');
		if (strchr(mask, res)) return res;
		_cputs("No such command\nYour choice: ");
	}
}

/*lab 2*/
struct edge
{
	int first;
	int second;
	int weight;
	struct edge* next;
};


struct graphG4
{
	int** g4;
	int** ost;
	int matrixRow;
	int numbEdge;
};

struct graphG5
{
	int** adjMatrix;
	int** weightMatrix;
	int matrixRow;
	int numEdge;
	int totMinWeight;
};

struct edge* tasks = 0;
int tasks_cnt = 0;

bool readGraph(struct graphG4* elem, struct graphG5* elemSec)
{
	char s[50] = { '\0' };
	_cputs("Enter file, which u want open: \n");
	cin >> s;
	FILE* fin = fopen(s, "r");
	if (fin == NULL)
	{
		return false;
	}
	int c = '\0';
	int matrixRow = 0;
	int numbEdge = 0;
	char befC = 0;
	c = fgetc(fin);
	while (c != '\n')
	{
		if (c != ' ' && (befC < '0' || befC > '9'))
		{
			matrixRow++;
		}
		befC = c;
		c = fgetc(fin);
	}
	fseek(fin, 0, SEEK_SET);
	elem->g4 = new int* [matrixRow];

	for (int i = 0; i < matrixRow; i++)
	{
		elem->g4[i] = new int[matrixRow];
		for (int j = 0; j < matrixRow; j++)
		{
			fscanf(fin, "%d", &(elem->g4[i][j]));
			if (elem->g4[i][j] >= 0)
			{
				numbEdge += elem->g4[i][j];
			}
		}
	}

	elem->matrixRow = matrixRow;
	elem->numbEdge = numbEdge / 2;
	fclose(fin);
	char l[50] = { '\0' };
	_cprintf("Enter the file name(Kruskal's algorithm):\n");
	cin >> l;
	fin = fopen(l, "r");
	if (fin == NULL)
	{
		return false;
	}
	matrixRow = 0;
	numbEdge = 0;
	c = fgetc(fin);
	while (c != '\n')
	{
		if (c != ' ' && c != '-')
		{
			matrixRow++;
		}
		c = fgetc(fin);
	}
	fseek(fin, 0, SEEK_SET);
	elemSec->weightMatrix = new int* [matrixRow];
	for (int i = 0; i < matrixRow; i++)
	{
		elemSec->weightMatrix[i] = new int[matrixRow];
		for (int j = 0; j < matrixRow; j++)
		{
			fscanf(fin, "%d", &(elemSec->weightMatrix[i][j]));
		}
	}
	elemSec->matrixRow = matrixRow;
	elemSec->numEdge = numbEdge / 2;
	return true;
}

void DFS(int st, bool* visited, struct graphG4* elem)
{
	int r = 0;

	visited[st] = true;
	for (r = 0; r < elem->matrixRow; r++)
		if ((elem->g4[st][r] != 0) && (!visited[r]))
		{
			_cprintf("%d - %d ",st + 1, r + 1);
			DFS(r, visited, elem);
			numEd++;
			elem->ost[st][r] += 1;
			elem->ost[r][st] += 1;
		}
}


void push_task(struct edge* t)
{
	t->next = 0;

	struct edge* cur = tasks;
	struct edge* prev = 0;
	if (tasks != 0)
	{
		while (cur != NULL && t->weight > cur->weight)
		{
			prev = cur;
			cur = cur->next;
		}
		if (prev != 0)
		{
			prev->next = t;
			t->next = cur;
		}

	}
	if (prev == 0)
	{
		t->next = tasks;
		tasks = t;
	}
	tasks_cnt++;
}


struct edge* pop_task()
{
	struct edge* ret = 0;
	if (tasks)// Если задачи есть
	{
		// Вернуть первую из них
		ret = tasks;
		tasks = ret->next;
		ret->next = 0;
		tasks_cnt--;
	}
	return ret;
}


void search_min_krusk(struct graphG5* elem)
{
	/*fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();*/
	int matrixRow = elem->matrixRow;
	int* colors = new int[matrixRow];
	int count = 0;
	for (int i = 0; i < matrixRow; i++)
	{
		colors[i] = i;
		for (int j = i; j < matrixRow; j++)
		{
			if (elem->weightMatrix[i][j] != 0)
			{
				struct edge* temp = new struct edge[1];
				temp->first = i;
				temp->second = j;
				temp->weight = elem->weightMatrix[i][j];
				push_task(temp);
			}
		}
	}
	while (tasks_cnt != 0)
	{
		struct edge* temp = pop_task();
		int first = temp->first;
		int second = temp->second;
		if (colors[first] != colors[second])
		{
			_cprintf("%d - %d ", first + 1, second + 1);
			elem->adjMatrix[first][second] = 1;
			elem->adjMatrix[second][first] = 1;
			elem->totMinWeight += temp->weight;
			int color = 0;
			if (colors[first] < colors[second])
			{
				color = colors[second];
				for (int k = 0; k < matrixRow; k++)
				{
					if (colors[k] == color)
					{
						colors[k] = colors[first];
					}
				}
			}
			else
			{
				color = colors[first];
				for (int k = 0; k < matrixRow; k++)
				{
					if (colors[k] == color)
					{
						colors[k] = colors[second];
					}
				}
			}
		}
	}
}
/*lab 2*/


/*lab 3*/

struct graphG6
{
	int** weightMatrix;
	int matrixRow;
	int max;
	int min;
	int* d;
	int* p;
};


void readGraph(struct graphG6* elem, FILE* fin)
{
	int c = '\0';
	int matrixRow = 0;
	int numbEdge = 0;
	int befc = 0;
	c = fgetc(fin);
	/*fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();*/
	while (c != '\n')
	{
		if (c != '-' && (befc < '0' || befc > '9'))
		{
			matrixRow++;
		}
		befc = c;
		c = fgetc(fin);
	}
	fseek(fin, 0, SEEK_SET);
	elem->weightMatrix = new int* [matrixRow];
	elem->max = 0;
	//elem->min = 0;
	for (int i = 0; i < matrixRow; i++)
	{
		elem->weightMatrix[i] = new int[matrixRow];
		for (int j = 0; j < matrixRow; j++)
		{
			fscanf(fin, "%d", &(elem->weightMatrix[i][j]));
			/*if (elem->weightMatrix[i][j] > elem->max)
			{
				elem->max = elem->weightMatrix[i][j];
			}*/
			if (elem->weightMatrix[i][j] < elem->min)
			{
				elem->min = elem->weightMatrix[i][j];
			}
		}
	}
	elem->matrixRow = matrixRow;
}

void ford_belman(struct graphG6* elem)
{
	int matrixRow = elem->matrixRow;
	int first = 0;
	int second = 0;
	_cputs("Enter the vertex the path you want to find from: \n");
	cin >> first;
	_cputs("Enter the vertex the path to which you want to find: \n");
	cin >> second;
	if (first > matrixRow || second > matrixRow)
	{
		_cputs("erorr\n");
		return;
	}
	bool check = true;
	for (int i = 0; i < matrixRow; i++)
	{
		elem->d[i] = elem->weightMatrix[first - 1][i];
		if (elem->d[i] != INF && first != i + 1)
		{
			check = false;
		}
		elem->p[i] = first - 1;
	}
	if (check)
	{
		_cputs("No path was found\n");
		return;
	}
	_cputs("D: ");
	for (int i = 0; i < matrixRow; i++)
	{
		_cprintf("%d ", elem->d[i]);
	}
	/*fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();*/
	_cputs("\nP: ");
	for (int i = 0; i < matrixRow; i++)
	{
		_cprintf("%d ", elem->p[i] + 1);
	}
	_cputs("\n\n");
	bool change = true;
	while (change)
	{
		change = false;
		for (int i = 0; i < matrixRow; i++)
		{
			for (int j = 0; j < matrixRow; j++)
			{
				if (elem->weightMatrix[j][i] != INF && elem->d[j] != INF && elem->d[i] > elem->d[j] + elem->weightMatrix[j][i])
				{
					elem->d[i] = elem->d[j] + elem->weightMatrix[j][i];
					elem->p[i] = j;
					change = true;
				}
			}
		}
		_cputs("D: ");
		for (int i = 0; i < matrixRow; i++)
		{
			_cprintf("%d ", elem->d[i]);
		}
		_cputs("\nP: ");
		for (int i = 0; i < matrixRow; i++)
		{
			_cprintf("%d ", elem->p[i] + 1);
		}
		_cputs("\n\n");
	}
	int i = second - 1;
	if (elem->d[second - 1] == INF)
	{
		_cputs("No path was found\n"); //<< endl;
		return;
	}
	while (i != first - 1)
	{
		_cprintf("%d<-", i + 1);
		i = elem->p[i];
	}
	_cprintf("%d\n", i + 1);
	_cprintf("Total weight: %d\n", elem->d[second - 1]);
}


void max_min(struct graphG6* elem)
{
	int matrixRow = elem->matrixRow;
	int first = 0;
	int second = 0;
	_cputs("Enter the vertex the path you want to find from: \n");
	cin >> first;
	_cputs("Enter the vertex the path to which you want to find: \n");
	cin >> second;
	if (first > matrixRow || second > matrixRow)
	{
		_cputs("erorr\n");
		return;
	}
	int* s = new int[matrixRow];
	bool* v = new bool[matrixRow];
	int counts = 2;
	for (int i = 0; i < matrixRow; i++)
	{
		s[i] = -1;
		v[i] = true;
	}
	s[0] = first - 1;
	v[first - 1] = false;
	int max = 0;
	int maxIdx = 0;
	//elem->min -= 1;
	_cputs("S { \n");
	for (int k = 0; k < counts - 1; k++)
	{
		_cprintf("%d ", s[k] + 1);
	}
	_cprintf("} \n");
	for (int i = 0; i < matrixRow; i++)
	{
		//if (elem->weightMatrix[first - 1][i] != 0 || first - 1 == i)
		//{
		elem->d[i] = elem->weightMatrix[first - 1][i];
		if (max < elem->d[i])
		{
			max = elem->d[i];
			maxIdx = i;
		}
		/*}
		else
		{
			elem->d[i] = elem->min;
		}*/
		elem->p[i] = first - 1;
	}
	_cprintf("D: ");
	for (int i = 0; i < matrixRow; i++)
	{
		_cprintf("%d ", elem->d[i]);
	}
	_cputs ("\nP: ");
	for (int i = 0; i < matrixRow; i++)
	{
		_cprintf("%d ", elem->p[i] + 1);
	}
	_cputs("\n\n");
	v[maxIdx] = false;
	s[1] = maxIdx;
	max = -10000;
	maxIdx = 0;
	for (int i = 0; i < matrixRow - 2; i++)
	{
		_cputs("S { ");
		for (int k = 0; k < counts; k++)
		{
			_cprintf("%d ", s[k] + 1);
		}
		_cputs("} \n");
		for (int k = 0; k < matrixRow; k++)
		{
			if (v[k] && elem->weightMatrix[s[counts - 1]][k] != INF && elem->weightMatrix[s[counts - 1]][k] > elem->d[k])
			{
				if (elem->weightMatrix[s[counts - 1]][k] < elem->d[s[counts - 1]])
				{
					elem->d[k] = elem->weightMatrix[s[counts - 1]][k];
				}
				else
				{
					elem->d[k] = elem->d[s[counts - 1]];
				}
				elem->p[k] = s[counts - 1];
			}
			if (elem->d[k] > max && v[k])
			{
				max = elem->d[k];
				if (-max == INF)
				{
					break;
				}
				maxIdx = k;
			}
		}
		if (-max == INF)
		{
			break;
		}
		s[counts] = maxIdx;
		counts++;
		v[maxIdx] = false;
		max = -10000;
		_cputs("D: ");
		for (int i = 0; i < matrixRow; i++)
		{
			_cprintf("%d ", elem->d[i]);
		}
		_cputs("\nP: ");
		for (int i = 0; i < matrixRow; i++)
		{
			_cprintf("%d ", elem->p[i] + 1);
		}
		_cputs("\n\n");
	}

	int i = second - 1;
	if (-(elem->d[second - 1]) == INF)
	{
		_cputs("\nNo path was found\n");
		return;
	}
	while (i != first - 1)
	{
		_cprintf("%d<-", i + 1);
		i = elem->p[i];
	}
	_cprintf("%d\n", i + 1);
	_cputs("Total weight: %d\n");
}

/*end lab3*/


/*lab 4*/
struct network
{
	int** bandwitdth;
	int** secBandwidth;
	int matrixRow;
	int max;
};



void readGraph(struct network* elem, FILE* fin)
{
	int c = '\0';
	int matrixRow = 0;
	int numbEdge = 0;
	c = fgetc(fin);
	int befC = 0;
	/*fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();*/
	while (c != '\n')
	{
		if (c != ' ' && c != '-' && (befC < '0' || befC > '9'))
		{
			matrixRow++;
		}
		befC = c;
		c = fgetc(fin);
	}
	fseek(fin, 0, SEEK_SET);
	elem->bandwitdth = new int* [matrixRow];
	elem->max = 0;
	for (int i = 0; i < matrixRow; i++)
	{
		elem->bandwitdth[i] = new int[matrixRow];
		for (int j = 0; j < matrixRow; j++)
		{
			fscanf(fin, "%d", &(elem->bandwitdth[i][j]));
			if (elem->bandwitdth[i][j] > elem->max)
			{
				elem->max = elem->bandwitdth[i][j];
			}
		}
	}
	elem->matrixRow = matrixRow;
}


int min_value(int first, int second)
{
	if (first < second)
	{
		return first;
	}
	else
	{
		return second;
	}
}

int ford_falkerson(int v, int dest, bool* visit, struct network* elem, int flow)
{
	if (v == dest)
	{
		return flow;
	}
	/*fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();*/
	visit[v] = true;
	int curf = 0;
	for (int i = 0; i < elem->matrixRow; i++)
	{
		if (elem->bandwitdth[v][i] > 0 && !visit[i])
		{
			curf = ford_falkerson(i, dest, visit, elem, min_value(elem->bandwitdth[v][i], flow));
			if (curf > 0)
			{
				elem->bandwitdth[v][i] -= curf;
				elem->bandwitdth[i][v] += curf;
				return curf;
			}
		}
	}
	return 0;
}

void preparation_func(struct network* elem)
{
	int matrixRow = elem->matrixRow;
	int dest = 0;
	int source = 0;
	bool first = false;
	/*fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();*/
	bool second = false;
	elem->secBandwidth = new int* [matrixRow];
	for (int i = 0; i < matrixRow; i++)
	{
		elem->secBandwidth[i] = new int[matrixRow];
		for (int j = 0; j < matrixRow; j++)
		{
			elem->secBandwidth[i][j] = 0;
			if (elem->bandwitdth[i][j] != 0)
			{
				first = true;
			}
			if (elem->bandwitdth[j][i] != 0)
			{
				second = true;
			}
		}
		if (!first)
		{
			dest = i;
		}
		if (!second)
		{
			source = i;
		}
		first = false;
		second = false;
	}


	_cprintf("Source: %d\n", source + 1);
	_cprintf("Destination: %d", dest + 1);
	int result = 0;
	int temp = 0;
	int** fban = new int* [matrixRow];
	/*fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();*/
	for (int i = 0; i < matrixRow; i++)
	{
		fban[i] = new int[matrixRow];
		for (int j = 0; j < matrixRow; j++)
		{
			fban[i][j] = elem->bandwitdth[i][j];
		}
	}
	bool* visit = new bool[matrixRow];
	do
	{
		for (int i = 0; i < matrixRow; i++)
		{
			visit[i] = false;
		}
		temp = ford_falkerson(source, dest, visit, elem, elem->max);
		result += temp;
	} while (temp != 0);

	_cputs("Max Flow: \n");
	for (int i = 0; i < matrixRow; i++)
	{
		for (int j = 0; j < matrixRow; j++)
		{
			if (fban[i][j] == 0)
			{
				_cputs("0/0  ");
			}
			else
			{
				_cprintf("%d/%d  ", elem->bandwitdth[j][i], fban[i][j]);
			}
		}
		_cprintf("\n");
	}
	_cprintf("\n\n");
	_cputs("Maximum network flow value : \n");
}
/*lab 4 end*/

void menu()
{
	while (1)
	{
		//system("cls");
		_cputs("Choose lab, wich you want check\n");
		_cputs("1. Lab 2\n");
		_cputs("2. Lab 3\n");
		_cputs("3. Lab 4\n");
		_cputs("4. Exit\n");
		_cputs("Your choice: \n");
		char choice = get_input("1234");
		/*fIsDebuggerPresent();
		pDebugObjectHandle();
		fCheckRemoteDebuggerPresent();
		pProcessDebugFlags();*/
		switch (choice) {
		case '1':
		{
			if (!CheckPass())
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			unsigned long check_sum = CrcCalculation();
			_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
				_cputs("Error CRC\n");
				system("pause");
				exit(UNRIGHT_PASSWORD);
			}
			char symbol = '/';
			if (check_pass[0] == symbol)
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			struct graphG4* graph1 = new struct graphG4[1];
			struct graphG5* graph2 = new struct graphG5[1];
			if (!readGraph(graph1, graph2))
			{
				_cputs("Error reading the graph\n");
				system("pause");
				return;
			}
			bool* visited = new bool[graph1->matrixRow];
			graph1->ost = new int* [graph1->matrixRow];
			if (!CheckPass())
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			symbol = '/';
			if (check_pass[0] == symbol)
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			check_sum = CrcCalculation();
			_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
				_cputs("Error CRC\n");
				system("pause");
				exit(UNRIGHT_PASSWORD);
			}
			for (int i = 0; i < graph1->matrixRow; i++)
			{
				visited[i] = false;
				graph1->ost[i] = new int[graph1->matrixRow];
				for (int j = 0; j < graph1->matrixRow; j++)
				{
					graph1->ost[i][j] = 0;
				}
			}
			_cputs("The sequence of adding edges to the skeleton: ");
			for (int i = 0; i < graph1->matrixRow; i++)
			{
				DFS(i, visited, graph1);
			}
			_cputs("\nThe adjacency matrix of the skeleton of the graph G4:\n");
			for (int i = 0; i < graph1->matrixRow; i++)
			{
				visited[i] = 0;
				for (int j = 0; j < graph1->matrixRow; j++)
				{
					_cprintf("%d ", graph1->ost[i][j]);
					graph1->ost[i][j] = 0;
				}
				_cputs("\n");
			}

			cout << endl;
			graph2->adjMatrix = new int* [graph2->matrixRow];
			for (int i = 0; i < graph2->matrixRow; i++)
			{
				graph2->adjMatrix[i] = new int[graph2->matrixRow];
				for (int j = 0; j < graph2->matrixRow; j++)
				{
					graph2->adjMatrix[i][j] = 0;
				}
			}
			graph2->totMinWeight = 0;
			cout << "The sequence of adding edges to the skeleton : ";
			search_min_krusk(graph2);
			cout << endl;
			cout << "Adjacency matrix of the minimal skeleton of the graph G5: " << endl;
			for (int i = 0; i < graph2->matrixRow; i++)
			{
				for (int j = 0; j < graph2->matrixRow; j++)
				{
					cout << graph2->adjMatrix[i][j] << ' ';
				}
				cout << endl;
			}
			cout << "Weight: " << graph2->totMinWeight << endl;
			system("pause");
			break;
		}
		case '2':
		{
			if (!CheckPass())
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			char symbol = '/';
			if (check_pass[0] == symbol)
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			unsigned long check_sum = CrcCalculation();
			_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
				_cputs("Error CRC\n");
				system("pause");
				exit(UNRIGHT_PASSWORD);
			}
			struct graphG6* firstGraph = new struct graphG6[1];
			struct graphG6* secondGraph = new struct graphG6[1];
			char s[50] = { '\0' };
			char sec[50] = { '\0' };
			_cputs("Enter the file name(Ford - Belman algorithm) : \n");
			cin >> s;
			_cputs("Enter file name(max - min path) : \n");
			cin >> sec;
			FILE* fins1 = fopen(s, "r");
			FILE* fins2 = fopen(sec, "r");
			if (fins1 == NULL || fins2 == NULL)
			{
				_cprintf("Error");
				return;
			}
			readGraph(firstGraph, fins1);
			readGraph(secondGraph, fins2);
			fclose(fins1);
			fclose(fins2);
			if (!CheckPass())
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			symbol = '/';
			if (check_pass[0] == symbol)
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			check_sum = CrcCalculation();
			_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
				_cputs("Error CRC\n");
				system("pause");
				exit(UNRIGHT_PASSWORD);
			}
			int matrixRow = firstGraph->matrixRow;
			firstGraph->d = new int[matrixRow];
			firstGraph->p = new int[matrixRow];
			for (int i = 0; i < matrixRow; i++)
			{
				firstGraph->d[i] = 0;
				firstGraph->p[i] = 0;
			}
			matrixRow = secondGraph->matrixRow;
			secondGraph->d = new int[matrixRow];
			secondGraph->p = new int[matrixRow];
			for (int i = 0; i < matrixRow; i++)
			{
				secondGraph->d[i] = 0;
				secondGraph->p[i] = 0;
			}
			_cputs("Ford-Belman Method: \n");
			ford_belman(firstGraph);
			_cputs("Finding the maxmin path: \n");
			max_min(secondGraph);
			system("pause");
			break;
		}
		case '3':
		{
			if (!CheckPass())
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			unsigned long check_sum = CrcCalculation();
			_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
				_cputs("Error CRC\n");
				system("pause");
				exit(UNRIGHT_PASSWORD);
			}
			struct network* netw = new struct network[sizeof(struct network)];
			_cputs("Enter file name\n");
			char file_name[50] = { '\0' };
			cin >> file_name;
			FILE* fin = fopen(file_name, "r");
			if (!CheckPass())
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			char symbol = '/';
			if (check_pass[0] == symbol)
			{
				_cputs("Error Password\n");
				exit(UNRIGHT_PASSWORD);
			}
			check_sum = CrcCalculation();
			_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
				_cputs("Error CRC\n");
				system("pause");
				exit(UNRIGHT_PASSWORD);
			}
			if (fin == NULL)
			{
				_cputs("Open error");
				return;
			}
			readGraph(netw, fin);
			preparation_func(netw);
			fclose(fin);
			delete netw;
			system("pause");
		}
		case '4':
		{
			_cputs("End programm...\n");
			return;
		}
		}
	}
}

int main()
{

	
	check_pass = key();
	if (!CheckPass())
	{
		_cputs("Error Password\n");
		exit(UNRIGHT_PASSWORD);
	}
	char sym = ';';
	/*fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();*/
	if (sym == check_pass[1])
	{
		_cputs("Error Password\n");
		exit(UNRIGHT_PASSWORD);
	}
	unsigned long check_sum = CrcCalculation();
	printf("Checksum %x\n", check_sum);
	if (check_sum != real_check_sum)
	{
		_cputs("Error CRC\n");
		system("pause");
		exit(UNRIGHT_PASSWORD);
	}
	menu();
	system("pause");
	return 0;
}