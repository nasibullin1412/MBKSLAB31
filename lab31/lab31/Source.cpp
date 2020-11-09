#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <list>
#define INF 100000
#define UNRIGHT_PASSWORD -2
using namespace std;

int numEd = 0;
unsigned char password[20] = { '\0' };
char* check_pass = nullptr;
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
	cout << "Enter password:" << endl;
	char check[50] = { '\0' };
	cin >> check;
	input.close();
	return check;
}


char get_input(const char* mask)
{
	char res = 0;
	while (1) {
		res = tolower(getchar());
		while (getchar() != '\n');
		if (strchr(mask, res)) return res;
		cout << "No such command\nYour choice: ";
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
	cout << "Enter file, which u want open: " << endl;
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
	cout << "Enter the file name(Kruskal's algorithm):" << endl;
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
			cout << st + 1 << "-" << r + 1 << " ";
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
			cout << first + 1 << "-" << second + 1 << " ";
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
	cout << "Enter the vertex the path you want to find from: " << endl;
	cin >> first;
	cout << "Enter the vertex the path to which you want to find: " << endl;
	cin >> second;
	if (first > matrixRow || second > matrixRow)
	{
		cout << "erorr" << endl;
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
		cout << "No path was found" << endl;
		return;
	}
	cout << "D: ";
	for (int i = 0; i < matrixRow; i++)
	{
		cout << elem->d[i] << ' ';
	}
	cout << endl; cout << "P: ";
	for (int i = 0; i < matrixRow; i++)
	{
		cout << elem->p[i] + 1 << ' ';
	}
	cout << endl << endl;
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
		cout << "D: ";
		for (int i = 0; i < matrixRow; i++)
		{
			cout << elem->d[i] << ' ';
		}
		cout << endl;
		cout << "P: ";
		for (int i = 0; i < matrixRow; i++)
		{
			cout << elem->p[i] + 1 << ' ';
		}
		cout << endl << endl;
	}
	int i = second - 1;
	if (elem->d[second - 1] == INF)
	{
		cout << "No path was found" << endl;
		return;
	}
	while (i != first - 1)
	{
		cout << i + 1 << "<-";
		i = elem->p[i];
	}
	cout << i + 1 << endl;
	cout << "Total weight: " << elem->d[second - 1] << endl;
}


void max_min(struct graphG6* elem)
{
	int matrixRow = elem->matrixRow;
	int first = 0;
	int second = 0;
	cout << "Enter the vertex the path you want to find from: " << endl;
	cin >> first;
	cout << "Enter the vertex the path to which you want to find: " << endl;
	cin >> second;
	if (first > matrixRow || second > matrixRow)
	{
		cout << "erorr" << endl;
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
	cout << "S { ";
	for (int k = 0; k < counts - 1; k++)
	{
		cout << s[k] + 1 << ' ';
	}
	cout << "} " << endl;
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
	cout << "D: ";
	for (int i = 0; i < matrixRow; i++)
	{
		cout << elem->d[i] << ' ';
	}
	cout << endl;
	cout << "P: ";
	for (int i = 0; i < matrixRow; i++)
	{
		cout << elem->p[i] + 1 << ' ';
	}
	cout << endl << endl;
	v[maxIdx] = false;
	s[1] = maxIdx;
	max = -10000;
	maxIdx = 0;
	for (int i = 0; i < matrixRow - 2; i++)
	{
		cout << "S { ";
		for (int k = 0; k < counts; k++)
		{
			cout << s[k] + 1 << ' ';
		}
		cout << "} " << endl;
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
		cout << "D: ";
		for (int i = 0; i < matrixRow; i++)
		{
			cout << elem->d[i] << ' ';
		}
		cout << endl;
		cout << "P: ";
		for (int i = 0; i < matrixRow; i++)
		{
			cout << elem->p[i] + 1 << ' ';
		}
		cout << endl << endl;
	}

	int i = second - 1;
	if (-(elem->d[second - 1]) == INF)
	{
		cout << endl;
		cout << "No path was found" << endl;
		return;
	}
	while (i != first - 1)
	{
		cout << i + 1 << "<-";
		i = elem->p[i];
	}
	cout << i + 1 << endl;
	cout << "Total weight: " << elem->d[second - 1] << endl;
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


int min(int first, int second)
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
	visit[v] = true;
	int curf = 0;
	for (int i = 0; i < elem->matrixRow; i++)
	{
		if (elem->bandwitdth[v][i] > 0 && !visit[i])
		{
			curf = ford_falkerson(i, dest, visit, elem, min(elem->bandwitdth[v][i], flow));
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


	cout << "Source: " << source + 1 << endl;
	cout << "Destination: " << dest + 1 << endl;
	int result = 0;
	int temp = 0;
	int** fban = new int* [matrixRow];
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

	cout << "Max Flow: " << endl;
	for (int i = 0; i < matrixRow; i++)
	{
		for (int j = 0; j < matrixRow; j++)
		{
			if (fban[i][j] == 0)
			{
				cout << "0/0  ";
			}
			else
			{
				cout << elem->bandwitdth[j][i] << "/" << fban[i][j] << "  ";
			}
		}
		cout << endl;
	}
	cout << endl << endl;
	cout << "Maximum network flow value : " << result << endl;
}
/*lab 4 end*/

void menu()
{
	while (1)
	{
		//system("cls");
		cout << "Choose lab, wich you want check" << endl;
		cout << "1. Lab 2" << endl;
		cout << "2. Lab 3" << endl;
		cout << "3. Lab 4" << endl;
		cout << "4. Exit" << endl;
		cout << "Your choice: ";
		char choice = get_input("1234");
		switch (choice) {
		case '1':
		{
			if (!CheckPass())
			{
				cout << "Error Password" << endl;
				exit(UNRIGHT_PASSWORD);
			}
			struct graphG4* graph1 = new struct graphG4[1];
			struct graphG5* graph2 = new struct graphG5[1];
			if (!readGraph(graph1, graph2))
			{
				cout << "Error reading the graph" << endl;
				system("pause");
				return;
			}
			bool* visited = new bool[graph1->matrixRow];
			graph1->ost = new int* [graph1->matrixRow];
			if (!CheckPass())
			{
				cout << "Error Password" << endl;
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
			cout << "The sequence of adding edges to the skeleton: ";
			for (int i = 0; i < graph1->matrixRow; i++)
			{
				DFS(i, visited, graph1);
			}
			cout << endl;
			cout << "The adjacency matrix of the skeleton of the graph G4:" << endl;
			for (int i = 0; i < graph1->matrixRow; i++)
			{
				visited[i] = 0;
				for (int j = 0; j < graph1->matrixRow; j++)
				{
					cout << graph1->ost[i][j] << ' ';
					graph1->ost[i][j] = 0;
				}
				cout << endl;
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
				cout << "Error Password" << endl;
				exit(UNRIGHT_PASSWORD);
			}
			struct graphG6* firstGraph = new struct graphG6[1];
			struct graphG6* secondGraph = new struct graphG6[1];
			char s[50] = { '\0' };
			char sec[50] = { '\0' };
			cout << "Enter the file name(Ford - Belman algorithm) : " << endl;
			cin >> s;
			cout << "Enter file name(max - min path) : " << endl;
			cin >> sec;
			FILE* fins1 = fopen(s, "r");
			FILE* fins2 = fopen(sec, "r");
			if (fins1 == NULL || fins2 == NULL)
			{
				printf("Error");
				return;
			}
			readGraph(firstGraph, fins1);
			readGraph(secondGraph, fins2);
			fclose(fins1);
			fclose(fins2);
			if (!CheckPass())
			{
				cout << "Error Password" << endl;
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
			cout << "Ford-Belman Method: " << endl;
			ford_belman(firstGraph);
			cout << "Finding the maxmin path: " << endl;
			max_min(secondGraph);
			system("pause");
			break;
		}
		case '3':
		{
			if (!CheckPass())
			{
				cout << "Error Password" << endl;
				exit(UNRIGHT_PASSWORD);
			}
			struct network* netw = new struct network[sizeof(struct network)];
			cout << "Enter file name" << endl;
			char file_name[50] = { '\0' };
			cin >> file_name;
			FILE* fin = fopen(file_name, "r");
			if (!CheckPass())
			{
				cout << "Error Password" << endl;
				exit(UNRIGHT_PASSWORD);
			}
			if (fin == NULL)
			{
				cout << "Open error";
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
			cout << "End programm..." << endl;
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
		cout << "Error Password" << endl;
		exit(UNRIGHT_PASSWORD);
	}
	menu();
	system("pause");
	return 0;
}