extern "C" wchar_t* __ODC__( const char * );
extern "C" char* __ODA__( const char * );
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
constexpr unsigned long real_check_sum = 0x3ab2;

bool checking_password()
{
	char checking_pass[20] = { '\0' };
	for (size_t i = 0; i < 5; i++)
	{
		checking_pass[i] = password[i];
	}
	unsigned int count = 0;
	while (checking_pass[count]!= password[0])
	{
		++count;
	}
	if (count == 0)
	{
		return false;
	}
	return true;
}

typedef NTSTATUS(NTAPI* pfnNtQueryInformationProcess)(
	_In_ HANDLE ProcessHandle,
	_In_ UINT ProcessInformationClass,
	_Out_ PVOID ProcessInformation,
	_In_ ULONG ProcessInformationLength,
	_Out_opt_ PULONG ReturnLength
	);


void fIsDebuggerPresent() {
	if (IsDebuggerPresent())
	{
/*		printf("Debugger detected\n");*/
		printf(__ODA__("KRUXXXXXckoq .246:=APWY\\^js )4CPPU_`kt%%/6;@OTUZ_bjlmw$/5=CQ^_aiknu\"157>"));
		exit(OTLADCHIK);
	}
	//else
		//printf("Debugger not detected\n");
}
// 3.3
// reference: "Anti-Unpacker Tricks" by Peter Ferrie
void fCheckRemoteDebuggerPresent() {

	BOOL isdbg = FALSE;

	CheckRemoteDebuggerPresent(GetCurrentProcess(), &isdbg);
	if (isdbg)
	{
/*		printf("Debugger detected\n");*/
		printf(__ODA__("MY^cccccffu%28@DQW^em{!06BJTU`cds ,2AIUdqtwz!$)03<EMNW`gs *9DJQR`nw$**3="));
		exit(OTLADCHIK);
	}
	//else
		//printf("Debugger not detected\n");
}



// 3.6
// reference: "Anti-Unpacker Tricks" by Peter Ferrie

void pDebugObjectHandle() {

	HANDLE proc;
	NTSTATUS ntStatus;
	HANDLE hDebugHandle = NULL;
	proc = GetCurrentProcess();

	pfnNtQueryInformationProcess NtQueryInformationProcess = NULL;
/*	HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));*/
	HMODULE hNtDll = LoadLibrary(__ODC__("GLR\\\\\\\\\\`aoz} %,8EPZbblzz|\"&,78@O^_fhmy!$3:HOYhkq!.07CEEKRZfjr!0128\?FNWY"));
/*	NtQueryInformationProcess = (pfnNtQueryInformationProcess)GetProcAddress(hNtDll, "NtQueryInformationProcess");*/
	NtQueryInformationProcess = (pfnNtQueryInformationProcess)GetProcAddress(hNtDll, __ODA__("AGKXXXXXcruyyz$0>BDFP[fhw!*5DLPVbp}*59:<BFMNY_fmq}-.3:;;IRT[^epu} /16=HR"));
	UINT ProcessDebugObjectHandle = 0x1E;

	ntStatus = NtQueryInformationProcess(proc, ProcessDebugObjectHandle, &hDebugHandle, sizeof(hDebugHandle), NULL);
	if (hDebugHandle)
	{
/*		printf("Debugger detected\n");*/
		printf(__ODA__("FNU`````hhhjs{'(6\?HIQQTXddhiiot{%&,5DIJT]alu&/;DRTV]bpz!'.;GTV^houw!/3BP"));
		exit(OTLADCHIK);
		return;
	}
	else
	{
		//printf("Debugger not detected\n");
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
/*	HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));*/
	HMODULE hNtDll = LoadLibrary(__ODC__("CJLQQQQQT^ein{'+78>LXbeo}-8>IP\\fnwx$&)+/8DOXeflw%)3<CORT`bhqsssw{$*3<GV["));
/*	NtQueryInformationProcess = (pfnNtQueryInformationProcess)GetProcAddress(hNtDll, "NtQueryInformationProcess");*/
	NtQueryInformationProcess = (pfnNtQueryInformationProcess)GetProcAddress(hNtDll, __ODA__("NOSXXXXX_ko{})7;GT\\]^bhhkot%09HTabp|+6\?GPX_giq\".9=CKM[jqw\"/6ANQYhkt#)06C"));
	UINT ProcessDebugFlags = 0x1F;
	ntStatus = NtQueryInformationProcess(proc, ProcessDebugFlags, &hDebugFlags, sizeof(hDebugFlags), NULL);
	if (hDebugFlags == FALSE)
/*		printf("Debugger detected\n");*/
		printf(__ODA__("PTXaaaaajkw -8GHJW^my$(.9\?BCHLY]^bchuz\"/=IPW`josx!*8GLQV`jr}}}'-4@BFKZet"));
	//else
		//printf("Debugger not detected\n");
}



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
/*	input.open("password.txt");*/
	input.open(__ODA__("LTZ`````ns#1\?EMUamrx{,.<CJUZZcgos|-6<CQS"));
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
/*	_cputs("Enter password:\n");*/
	_cputs(__ODA__("JRV[[[[[dny\"&)89\?LQUX\\^abp}%./5@ILLVdgky(+-7@IIXbhuv$12@@KYaeixx#00149@K"));
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
/*		_cputs("No such command\nYour choice: ");*/
		_cputs(__ODA__("BQS_____jwy -4CEES^empwz!#+9@AMQ[\\]^hs!,--2;AIX_lt#%(68ALX[[[]ekkr|%+0<I"));
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
/*	_cputs("Enter file, which u want open: \n");*/
	_cputs(__ODA__("LPWfffffgt}\")69@CQU`elp{\"#+00:EOZcrsu!$+49FTY_iky\"#*00>ITYgikv|\".:IIVVWeeox'08>CENUXadjjloorsv{|-/<DJUV^"));
	cin >> s;
/*	FILE* fin = fopen(s, "r");*/
	FILE* fin = fopen(s, __ODA__("MMRaaaaacqx $12@KR\\kx'.:=KNNXgvwz)/9\?\?HT"));
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
/*			fscanf(fin, "%d", &(elem->g4[i][j]));*/
			fscanf(fin, __ODA__("LQQ\\\\\\\\\\bix'/=@KW_knw&4@CFR_chrz%*3\?HV_k"), &(elem->g4[i][j]));
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
/*	_cprintf("Enter the file name(Kruskal's algorithm):\n");*/
	_cprintf(__ODA__("FIJPPPPP^bqy()39ADJLVY^alovww%,18@NS\\`gggt\")5AGUWcghq}\"+,,-45DES\\ktw(7AIOSZ[^agruy(47:ABGGMU^lx'+-:GOO\\\\"));
	cin >> l;
/*	fin = fopen(l, "r");*/
	fin = fopen(l, __ODA__("LSXbbbbbcfpv$++/8BITakox{+9:GNX`mw'5CESZ"));
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
/*			fscanf(fin, "%d", &(elemSec->weightMatrix[i][j]));*/
			fscanf(fin, __ODA__("MTT^^^^^chly(4CMZ_hlnpss{{#&45=IP^dijx &"), &(elemSec->weightMatrix[i][j]));
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
/*			_cprintf("%d - %d ",st + 1, r + 1);*/
			_cprintf(__ODA__("NOVdddddsu!+4@IUccoy*/6;GHMZ[cily%*1=HIM"),st + 1, r + 1);
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
	if (tasks)// Åñëè çàäà÷è åñòü
	{
		// Âåðíóòü ïåðâóþ èç íèõ
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
/*			_cprintf("%d - %d ", first + 1, second + 1);*/
			_cprintf(__ODA__("NVWeeeeelu}}!')4<ADPWZixx(47DR]`ms /3@@C"), first + 1, second + 1);
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
	fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();
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

int search_min_path(int* array_)
{
	int min_ = 0;
	for (size_t i = 0; i < 10; i++)
	{
		if (min_ < array_[i])
		{
			min_ = array_[i];
		}
	}
	return min_;
}



int check_min_path_graph()
{
	struct graphG6 graph_;
	int min_ = 0;
	graph_.weightMatrix = new int* [10];
	for (size_t i = 0; i < 10; i++)
	{
		graph_.weightMatrix[i] = new int[10];
		for (size_t j = 0; j < 10; j++)
		{
			graph_.weightMatrix[i][j] = rand();
		}
		int temp = search_min_path(graph_.weightMatrix[i]);
		if (min_ < temp)
		{
			min_ = temp;
		}
	}
	return min_;
}
void readGraph(struct graphG6* elem, FILE* fin)
{
	int c = '\0';
	int matrixRow = 0;
	int numbEdge = 0;
	int befc = 0;
	c = fgetc(fin);
	fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();
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
/*			fscanf(fin, "%d", &(elem->weightMatrix[i][j]));*/
			fscanf(fin, __ODA__("JPW_____agtx\"\")089DNSSU_fovx(08@ELSakmuy"), &(elem->weightMatrix[i][j]));
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
/*	_cputs("Enter the vertex the path you want to find from: \n");*/
	_cputs(__ODA__("PZ[\\\\\\\\\\^inv%./8FSbqtv|$()15;DOVZ[]ffsy$&,045BFLW\\giu$$0<GLYbbpz(/0<GKLUX^`gjkv#1<BGLX^fkmy|+4;;<\?HMS_m|*+358;>MNZ`lz|%4:\?IMPVadkz $-1>C"));
	cin >> first;
/*	_cputs("Enter the vertex the path to which you want to find: \n");*/
	_cputs(__ODA__("FUY\\\\\\\\\\\\cdfmms#+:BLU[\\hq{*.08:AMX_fot{*7:;GV[]]`fkuy{%34\?JOQZ^chkww|#+9EO]]]lsy!+/>IMMSUZddhu{,/9<BIVcefmz+4CDR_eirtw#(+.8<=LTT___iu#%1"));
	cin >> second;
	if (first > matrixRow || second > matrixRow)
	{
/*		_cputs("erorr\n");*/
		_cputs(__ODA__("DMPXXXXXelz}%'')+6\?FHU[^bgt%4\?CORUYbfnz\""));
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
/*		_cputs("No path was found\n");*/
		_cputs(__ODA__("PYYccccchrstx&+09BFUcpxy)*/0\?MNU__jnrry(6>AMMSY`ehillux$-28FUabdr!#/7@AM"));
		return;
	}
/*	_cputs("D: ");*/
	_cputs(__ODA__("LTUddddddfkwz{|*4CLTaft}+0\?HRV^kw{(.7=DM"));
	check_min_path_graph();
	for (int i = 0; i < matrixRow; i++)
	{
/*		_cprintf("%d ", elem->d[i]);*/
		_cprintf(__ODA__("DRSYYYYYYetwzz'6EJMS[ekv$1==>DPXehvy)2::"), elem->d[i]);
	}
	fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();
/*	_cputs("\nP: ");*/
	_cputs(__ODA__("O^dgggggs|+9BIM\\iv#2<GV^ko})2=\?LOQ\\jx|*,"));
	for (int i = 0; i < matrixRow; i++)
	{
/*		_cprintf("%d ", elem->p[i] + 1);*/
		_cprintf(__ODA__("HVY^^^^^lx#(2>AOY`js}&3:;ITT`jn{{$$*49EP"), elem->p[i] + 1);
	}
/*	_cputs("\n\n");*/
	_cputs(__ODA__("LT[_____`lv''+9=GVeilz!,:GJOYety#%%(7AKM"));
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
/*		_cputs("D: ");*/
		_cputs(__ODA__("APRRRRRR_jjx|%34CMVZZhky}&4>GO]bo{'+1>DI"));
		for (int i = 0; i < matrixRow; i++)
		{
/*			_cprintf("%d ", elem->d[i]);*/
			_cprintf(__ODA__("JWX\\\\\\\\\\\\`bdkyzz|&2<CFUUY]`dfmp!!,33AHO^"), elem->d[i]);
		}
/*		_cputs("\nP: ");*/
		_cputs(__ODA__("JPSbbbbbktt$22AGJQ[als$399ALO^aabeor!&&1"));
		for (int i = 0; i < matrixRow; i++)
		{
/*			_cprintf("%d ", elem->p[i] + 1);*/
			_cprintf(__ODA__("BHKXXXXXdjls\"-;BHOT[cfns{#-0::HUcooy$/7:"), elem->p[i] + 1);
		}
/*		_cputs("\n\n");*/
		_cputs(__ODA__("IJMNNNNNPXfggmw}%''.09=CLY_cgp{ %)*7FRYb"));
	}
	int i = second - 1;
	if (elem->d[second - 1] == INF)
	{
/*		_cputs("No path was found\n"); //<< endl;*/
		_cputs(__ODA__("NV\\ggggggq &+6CJLYZ\\]bbkxy&.1<@ESXajjs{+9DOSV`ls{+77:DINW]hsz#)*2589>HP_")); //<< endl;
		return;
	}
	while (i != first - 1)
	{
/*		_cprintf("%d<-", i + 1);*/
		_cprintf(__ODA__("CGISSSSSZ`hhimt{*.=KV`ouy#$'4<@HJMOTapz'"), i + 1);
		i = elem->p[i];
	}
/*	_cprintf("%d\n", i + 1);*/
	_cprintf(__ODA__("LVYbbbbbjt!-5DGIPRU_jku}}$-557<IVYachmss"), i + 1);
/*	_cprintf("Total weight: %d\n", elem->d[second - 1]);*/
	_cprintf(__ODA__("PPVWWWWWbiw!!%%4CFMRX_nyz*19\?EHOUWemsxz%.=DFINPR_nu#(03\?\?LXgpuw{$27BNVbj"), elem->d[second - 1]);
}


void max_min(struct graphG6* elem)
{
	int matrixRow = elem->matrixRow;
	int first = 0;
	int second = 0;
/*	_cputs("Enter the vertex the path you want to find from: \n");*/
	_cputs(__ODA__("NVW\\\\\\\\\\jsz#.269;BOWabellz!(/7FHMMR]drz\"$&)-3\?CKQW^epr|'0\?JV^ku$.9APVdivx)68>ANYZ`fgsy#)6<CQ[bqvv ,3AOY]^jttv%/<KW^aeqz|%1>EHWYenu&,17<A"));
	cin >> first;
/*	_cputs("Enter the vertex the path to which you want to find: \n");*/
	_cputs(__ODA__("EORWWWWWdm{\".9GRU[]aix$./3\?GGGKV`aer#+3:=@O^lt{|#$-0<GMW]eghqqr!'.4AEQ]ht%)57@CLNW_do|\"03==EOYans$'69:;<=CDQQ_hoz'03AIKTZ[`fp}(,4<GLYbhu"));
	cin >> second;
	if (first > matrixRow || second > matrixRow)
	{
/*		_cputs("erorr\n");*/
		_cputs(__ODA__("P[agggggpx$%0>JLSaov'14@BJYbmy%((6APUWXc"));
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
/*	_cputs("S { \n");*/
	_cputs(__ODA__("JUUXXXXXfq!#-0<CNU\\kl{&2ACOW_jls\"14;GHQ["));
	for (int k = 0; k < counts - 1; k++)
	{
/*		_cprintf("%d ", s[k] + 1);*/
		_cprintf(__ODA__("DDGNNNNNUbinqy \"-7:HRY^cnu\"+5\?IQVZejquv!"), s[k] + 1);
	}
/*	_cprintf("} \n");*/
	_cprintf(__ODA__("CPSYYYYY\\]lu}#/9HKNO]`ikw -3::IJLLV`bknu"));
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
/*	_cprintf("D: ");*/
	_cprintf(__ODA__("ORT[[[[[\\cq!$(1=BNO]imw{|(3<\?HJWddknx\"15"));
	for (int i = 0; i < matrixRow; i++)
	{
/*		_cprintf("%d ", elem->d[i]);*/
		_cprintf(__ODA__("HTUWWWWWdhu!%05>KYboy#,.:=>IMSTchmy)13AL"), elem->d[i]);
	}
/*	_cputs ("\nP: ");*/
	_cputs (__ODA__("LU[`````nnu&4\?HVakvx$./28<IPXYZ`hkst!\")8"));
	for (int i = 0; i < matrixRow; i++)
	{
/*		_cprintf("%d ", elem->p[i] + 1);*/
		_cprintf(__ODA__("P[\\\\\\\\\\\\cdq\")3=BGNPQ[ekkmt\"&(-3BOQ^ds|-5"), elem->p[i] + 1);
	}
/*	_cputs("\n\n");*/
	_cputs(__ODA__("MNN\\\\\\\\\\\\kkw{$09DDKS^my\"#'35<KXervy*07AH"));
	v[maxIdx] = false;
	s[1] = maxIdx;
	max = -10000;
	maxIdx = 0;
	for (int i = 0; i < matrixRow - 2; i++)
	{
/*		_cputs("S { ");*/
		_cputs(__ODA__("HIOSSSSSUY[jjv&+-67@IXbbm{*-17:\?KU^cp *+"));
		for (int k = 0; k < counts; k++)
		{
/*			_cprintf("%d ", s[k] + 1);*/
			_cprintf(__ODA__("NV[bbbbbnn| *89;EKKWWahux|-./<FFRU`ckw&)"), s[k] + 1);
		}
/*		_cputs("} \n");*/
		_cputs(__ODA__("HRVcccccntuy#$%)8ENV_im|&/5BP_aju%19EPVc"));
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
/*		_cputs("D: ");*/
		_cputs(__ODA__("NVX[[[[[^my{)-799ERZhv&02;EGQVW_msv\")77>"));
		for (int i = 0; i < matrixRow; i++)
		{
/*			_cprintf("%d ", elem->d[i]);*/
			_cprintf(__ODA__("MNN]]]]]kqw|&,-5\?@KPS\\drt|*359FHQ`dr!$$1"), elem->d[i]);
		}
/*		_cputs("\nP: ");*/
		_cputs(__ODA__("HQUdddddsux(/15\?DLLP[_boy!%08>DQW]`cn}-8"));
		for (int i = 0; i < matrixRow; i++)
		{
/*			_cprintf("%d ", elem->p[i] + 1);*/
			_cprintf(__ODA__("HVZ]]]]]alu!.6=@HUdlll{$-;AOZ[glq\"%)*8CP"), elem->p[i] + 1);
		}
/*		_cputs("\n\n");*/
		_cputs(__ODA__("CRVeeeees$047ES]elou (6@ADGPUbjkot$*7<EI"));
	}

	int i = second - 1;
	if (-(elem->d[second - 1]) == INF)
	{
/*		_cputs("\nNo path was found\n");*/
		_cputs(__ODA__("IVV^^^^^mppz+29GL[_jv&**6<AKU]``lo}#,-13:DHJUW`moou},--17DGRVXcdns\"$36CR"));
		return;
	}
	while (i != first - 1)
	{
/*		_cprintf("%d<-", i + 1);*/
		_cprintf(__ODA__("IINRRRRRRXYeirry%+/9<DGLVdr!)2@CJNYhsxy%"), i + 1);
		i = elem->p[i];
	}
/*	_cprintf("%d\n", i + 1);*/
	_cprintf(__ODA__("JPU\\\\\\\\\\gklt\"*2\?KRY\\gp}!&0\?DKV_dgjtv!/12"), i + 1);
/*	_cprintf("Total weight: %d\n", elem->d[second-1]);*/
	_cprintf(__ODA__("OQUZZZZZafouux&'/455\?\?NO[dsw&&)-;=\?LOVchisv %3>MV`jmnu$.=JXcdooyy|%'5=KZ"), elem->d[second-1]);
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

int search_min(int* array_)
{
	int min_ = 0;
	for (size_t i = 0; i < 10; i++)
	{
		if (min_ < array_[i])
		{
			min_ = array_[i];
		}
	}
	return min_;
}



int check_max_flow_graph()
{
	struct network graph_;
	int min_ = 0;
	graph_.bandwitdth = new int* [10];
	for (size_t i = 0; i < 10; i++)
	{
		graph_.bandwitdth[i] = new int[10];
		for (size_t j = 0; j < 10; j++)
		{
			graph_.bandwitdth[i][j] = rand();
		}
		int temp = search_min(graph_.bandwitdth[i]);
		if (min_ < temp)
		{
			min_ = temp;
		}
	}
	return min_;
}

void readGraph(struct network* elem, FILE* fin)
{
	int c = '\0';
	int matrixRow = 0;
	int numbEdge = 0;
	c = fgetc(fin);
	int befC = 0;
	fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();
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
/*			fscanf(fin, "%d", &(elem->bandwitdth[i][j]));*/
			fscanf(fin, __ODA__("BBHOOOOOVW^dot$,,7FQR]cmuy\"&,7=HQ\\fgilo|"), &(elem->bandwitdth[i][j]));
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
	check_max_flow_graph();
	fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();
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
	fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();
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


/*	_cprintf("Source: %d\n", source + 1);*/
	_cprintf(__ODA__("GJQ[[[[[_cjs}*8ES[ijpux!+.1=HOZhw',9CNZh"), source + 1);
/*	_cprintf("Destination: %d", dest + 1);*/
	_cprintf(__ODA__("LTUUUUUU^_lr},5\?NQTbox%)0\?\?MXYdmny(-6BFS"), dest + 1);
	int result = 0;
	int temp = 0;
	int** fban = new int* [matrixRow];
	fIsDebuggerPresent();
	pDebugObjectHandle();
	fCheckRemoteDebuggerPresent();
	pProcessDebugFlags();
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

/*	_cputs("Max Flow: \n");*/
	_cputs(__ODA__("LZ______ioov|}+4AEPZimqv} #'.1\?NTW[^gr!."));
	for (int i = 0; i < matrixRow; i++)
	{
		for (int j = 0; j < matrixRow; j++)
		{
			if (fban[i][j] == 0)
			{
/*				_cputs("0/0  ");*/
				_cputs(__ODA__("GGLUUUUUcnrvx!&(+7CNXdmst .6=@CHHU[bgllu"));
			}
			else
			{
/*				_cprintf("%d/%d  ", elem->bandwitdth[j][i], fban[i][j]);*/
				_cprintf(__ODA__("FUWXXXXX\\\\fgt -8=BOYaky\"\"116<AJNRVegkrt$"), elem->bandwitdth[j][i], fban[i][j]);
			}
		}
/*		_cprintf("\n");*/
		_cprintf(__ODA__("BKKLLLLLY\\`hlwy%&(2=\?EJLYbpqu$%&-7<>EGHM"));
	}
/*	_cprintf("\n\n");*/
	_cprintf(__ODA__("MRUcccccjns\"-4CHIWY^`jy{)/4::IRYaagnox(7"));
/*	_cprintf("Maximum network flow value : %d\n", result);*/
	_cprintf(__ODA__("LPTcccccmwy%'-.:=FTco  )56>HHHUVYafkv$2>FHN[`ku||&3@LOSTbitw}\"/;BQ^crz%08@LTYhsu|(-9DFQX_`jt \".=JNVeqz\"*"), result);
}
/*lab 4 end*/

void menu()
{
	while (1)
	{
		__asm
		{
			JZ loc_4011C4
			JNZ loc_4011C4
			test eax, eax
			JMP loc_4011C4
			mov eax, 5678
			loc_4011C4:
		}
		//system("cls");
/*		_cputs("Choose lab, wich you want check\n");*/
		_cputs(__ODA__("CLP^^^^^et%%3@@BLSZ`mv}-5>HHT\\ht!\"+33;=IT\\dst%018<BJS]iilprv&/>HIX`ikluu|%'//8;;CR[`hoq}',.=>ANYcnquz$,5"));
/*		_cputs("1. Lab 2\n");*/
		_cputs(__ODA__("ADIPPPPPTYfqsy%47:==\?@CHWY``iklruy|$008C"));
/*		_cputs("2. Lab 3\n");*/
		_cputs(__ODA__("GSSYYYYY^^allpy&)57BFPQ`ju|,5;JRSVY]fu$)"));
/*		_cputs("3. Lab 4\n");*/
		_cputs(__ODA__("KNU_____gqtt}#%-6<>CIWbly$$(6\?IP_jjkvwz}"));
/*		_cputs("4. Exit\n");*/
		_cputs(__ODA__("HRT_____nyy$278FNZcjq}.1:GGQ]cmv%*/2;HKT"));
/*		_cputs("Your choice: \n");*/
		_cputs(__ODA__("LSYeeeeegjp -9EJYglqs}-6\?HRYZfpssu%--6<G"));
/*		char choice = get_input("1234");*/
		char choice = get_input(__ODA__("GGHIIIIILV]jy*3BIJSajkvx'4CCKPXXds{ -1<B"));
		if (choice)
		{
			fIsDebuggerPresent();
			pDebugObjectHandle();
		}
		else
		{
			fIsDebuggerPresent();
			pDebugObjectHandle();
		}
		if (choice)
		{
			fCheckRemoteDebuggerPresent();
			pProcessDebugFlags();
		}
		else
		{
			fCheckRemoteDebuggerPresent();
			pProcessDebugFlags();
		}
		switch (choice) {
		case '1':
		{

			struct graphG4* graph1 = new struct graphG4[1];
			struct graphG5* graph2 = new struct graphG5[1];
			if (!CheckPass())
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("P\\\\bbbbbjjy{'(3;DO^eemy)4:>GP\\]]lvy{+3=C"));
				exit(UNRIGHT_PASSWORD);
			}
			unsigned long check_sum = CrcCalculation();
			//_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
/*				_cputs("Error CRC\n");*/
				_cputs(__ODA__("NVW]]]]]kt%-3;;IKZ`bfr{(.=@AOO]^gv#$%28B"));
/*				system("pause");*/
				system(__ODA__("FHJJJJJJWbjt#(6CMZ_jxz))2=@@GPRZ^eklnv\"&"));
				exit(UNRIGHT_PASSWORD);
			}
			char symbol = '/';
			if (check_pass[0] == symbol)
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("KLQSSSSSS[ioqs$,489@NTbfhs$),49FKSbgmw!&"));
				exit(UNRIGHT_PASSWORD);
			}
			if (!readGraph(graph1, graph2))
			{
/*				_cputs("Error reading the graph\n");*/
				_cputs(__ODA__("FGGLLLLLNT[inz&/0:;>IWdfpp|++2ADFGQX_et#)05:@IU`grt '046BFLRVXbls ,:EKNY"));
/*				system("pause");*/
				system(__ODA__("FFKMMMMM[__ky)27BGMPTcgkz&&(4=KKPUYckuv'"));
				return;
			}

			bool* visited = new bool[graph1->matrixRow];
			graph1->ost = new int* [graph1->matrixRow];
			if (!CheckPass())
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("HKO\\\\\\\\\\_`aamu{}#(-4COSbp|'5<KYhhkntx)45"));
				exit(UNRIGHT_PASSWORD);
			}
			symbol = '/';
			if (check_pass[0] == symbol)
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("OZ\\bbbbbentz$38BNVXadq||&2=FMTX[jy\",-;GT"));
				exit(UNRIGHT_PASSWORD);
			}
			check_sum = CrcCalculation();
			//_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
/*				_cputs("Error CRC\n");*/
				_cputs(__ODA__("MY^hhhhhmmw$-3BMRV`chjr} +,1:HHQUZirz /7"));
/*				system("pause");*/
				system(__ODA__("IXXYYYYYdiors{+7=>ANNN]cfnty%03>JNQS^`dd"));
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
/*			_cputs("The sequence of adding edges to the skeleton: ");*/
			_cputs(__ODA__("BMRVVVVVZ`bjy*1=IUdouv%/3\?EHSXgtz{'(7CCGVaimx!#&12=GS\\hlw}+8ELPUbimst\"-9FHSWXZZ[itw#//<FMMNVWepsx\"##&+11"));
			for (int i = 0; i < graph1->matrixRow; i++)
			{
				DFS(i, visited, graph1);
			}
/*			_cputs("\nThe adjacency matrix of the skeleton of the graph G4:\n");*/
			_cputs(__ODA__("FQVeeeeefttu|+5;HNPW[hw&128\?BQ_`jlo $*1>GKOS_hsw|&()5AOQ_eru$/5:FTcipv *039\?HMQSakntz$3<DMYclqx(.36677AIM\\fghoz*02:>HHUW^kx| !.6DDOZhv|\""));
			for (int i = 0; i < graph1->matrixRow; i++)
			{
				visited[i] = 0;
				for (int j = 0; j < graph1->matrixRow; j++)
				{
/*					_cprintf("%d ", graph1->ost[i][j]);*/
					_cprintf(__ODA__("HSTWWWWWYhlqz\"&)8\?LX`oz}-55;EQWcqrx$%&1@"), graph1->ost[i][j]);
					graph1->ost[i][j] = 0;
				}
/*				_cputs("\n");*/
				_cputs(__ODA__("FMNXXXXXX\\\\eght$347FT]kz{ $3BGSW`iqrxx!\""));
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
/*			cout << "The sequence of adding edges to the skeleton : ";*/
			cout << __ODA__("INTTTTTTaios{),56;BNU\\dflt{+-9\?@ETTT\\ahnv'335APRRTT\\gqww'0;GPXcltvv%2;HVety'69BHQXYcq\"*7>>GLS`ijr|!-29DH");
			if (choice)
			{
				search_min_krusk(graph2);
			}
			else
			{
				if (!checking_password())
				{
					exit(UNRIGHT_PASSWORD);
				}
			}
			cout << endl;
/*			cout << "Adjacency matrix of the minimal skeleton of the graph G5: " << endl;*/
			cout << __ODA__("BEKWWWWWdqx'-9<DQ[jo}%1235=HQZaafpvz}(2=ADOPU]cksv /4<EHOY]bqs{|-0\?\?BFQ_bns|%'-/6BEHJJKSanovvy!05@AJRW^ko| \",5=GKNS_iitu#.8FQ^adfu&.133=") << endl;
			for (int i = 0; i < graph2->matrixRow; i++)
			{
				for (int j = 0; j < graph2->matrixRow; j++)
				{
					cout << graph2->adjMatrix[i][j] << ' ';
				}
				cout << endl;
			}
/*			cout << "Weight: " << graph2->totMinWeight << endl;*/
			cout << __ODA__("M\\_cccccot!-6\?ABPZ_glw!&5=>\?ELRRW``ios!(") << graph2->totMinWeight << endl;
/*			system("pause");*/
			system(__ODA__("IW[\\\\\\\\\\]blq{,.8:EKWafjjt%))8GGO[]jmz%,."));
			break;
		}
		case '2':
		{
			if (!CheckPass())
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("M\\apppppu !!079>LXXft}#+5<ILLS\\_`kqv} -7"));
				exit(UNRIGHT_PASSWORD);
			}
			char symbol = '/';
			if (check_pass[0] == symbol)
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("P[^iiiiiu\"/9>IWX`fhkv -7>FU`lnp!'(228FTT"));
				exit(UNRIGHT_PASSWORD);
			}
			unsigned long check_sum = CrcCalculation();
			//_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
/*				_cputs("Error CRC\n");*/
				_cputs(__ODA__("CQQZZZZZdq}-1:=IS_erv .11=FPWaowy}!-<\?CE"));
/*				system("pause");*/
				system(__ODA__("NNN[[[[[]do *0\?EQZhmmwyz%+7;IRT]]fgs#1\?N"));
				exit(UNRIGHT_PASSWORD);
			}
			struct graphG6* firstGraph = new struct graphG6[1];
			struct graphG6* secondGraph = new struct graphG6[1];
			char s[50] = { '\0' };
			char sec[50] = { '\0' };
/*			_cputs("Enter the file name(Ford - Belman algorithm) : \n");*/
			_cputs(__ODA__("KY[dddddiorx(247ADEGJKYefiknrt|&*,/>EQQXblw'6ANQ\\kxy|'2:HMMZZ[hls!*5;GPTaklnz$18ESXdss\"'3=LYfo{ ..468;JKQXYghmnnzz(7BDPWWY_eqv'(025=@CJR"));
			cin >> s;
/*			_cputs("Enter file name(max - min path) : \n");*/
			_cputs(__ODA__("GKMQQQQQZZafllu%(7==KRT[^cp{#'()))5:IJLV\\\\]ls !/8;ISZfsu%*.::IQUYamt!/3<IM[bhkvzz),-;DQY[\\hjtz$%)/1=@JMO"));
			cin >> sec;
/*			FILE* fins1 = fopen(s, "r");*/
			FILE* fins1 = fopen(s, __ODA__("ENSUUUUU^cdksu\"&,38FHNUVVdp|,09:\?DDHT\\gj"));
/*			FILE* fins2 = fopen(sec, "r");*/
			FILE* fins2 = fopen(sec, __ODA__("IOTTTTTTXgnqxz}&-5DMUZajm|\"\"1;JOY`jmm{$$"));
			if (fins1 == NULL || fins2 == NULL)
			{
/*				_cprintf("Error");*/
				_cprintf(__ODA__("PV]^^^^^ds %3=KSU^ds!%(+7BGRV`gp ++59>JU"));
				return;
			}
			readGraph(firstGraph, fins1);
			readGraph(secondGraph, fins2);
			fclose(fins1);
			fclose(fins2);
			if (!CheckPass())
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("OQQ]]]]]aip}%(*1>JKLXaow|*6DMRV\\deer|(13"));
				exit(UNRIGHT_PASSWORD);
			}
			symbol = '/';
			if (check_pass[0] == symbol)
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("COPRRRRRXfiop &+01;AFU\\blqz(/6AFMX_ip{(+"));
				exit(UNRIGHT_PASSWORD);
			}
			check_sum = CrcCalculation();
			//_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
/*				_cputs("Error CRC\n");*/
				_cputs(__ODA__("ELRVVVVVX^agnnqxx|#/<FFKPTcjjkt#.;\?LZet "));
/*				system("pause");*/
				system(__ODA__("ENT^^^^^kst}()+05BCGTcjly|(-.1;<FS_em{#("));
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
/*			_cputs("Ford-Belman Method: \n");*/
			_cputs(__ODA__("FHMVVVVV\\iu%4>GIO\\dissst%'158DEHLTYgq}#-5==\?LP\\_aly#*066BQ`clmv -1>FMR`h"));

			if (choice)
			{
				ford_belman(firstGraph);
/*				_cputs("Finding the maxmin path: \n");*/
				_cputs(__ODA__("INPWWWWWbbkv&0:CKOR^ajjmy&1>\?CJNVbiv|$12@KVdenrrxxy*-3<>DFKYdkkv}!%22@HN"));
				max_min(secondGraph);
			}
			else
			{
				if (!checking_password())
				{
					exit(UNRIGHT_PASSWORD);
				}
			}
/*			system("pause");*/
			system(__ODA__("CRSZZZZZ]eky}-/=LQT\\afggjx &55=EKXeiot{{"));
			break;
		}
		
		case '3':
		{
			if (!CheckPass())
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("LNO]]]]]flsw{\"#'25=IKRUUcou##/357AFQ[clp"));
				exit(UNRIGHT_PASSWORD);
			}
			unsigned long check_sum = CrcCalculation();
		//	_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
/*				_cputs("Error CRC\n");*/
				_cputs(__ODA__("LOUYYYYYZdmz&/26AIV]isz| \"\"#156=GR\\\\\\\\jy"));
/*				system("pause");*/
				system(__ODA__("HHM\\\\\\\\\\`amy)8DILVeqy#,4;EMOW[\\\\dr|$0;AK"));
				exit(UNRIGHT_PASSWORD);
			}
			struct network* netw = new struct network[sizeof(struct network)];
/*			_cputs("Enter file name\n");*/
			_cputs(__ODA__("EGGQQQQQZ^_dpy{#%4;=\?JOQS`adekkwz#'*69@IR[dnv$-1<FN\\hrtw',.059:FTYehlqrz"));
			char file_name[50] = { '\0' };
			cin >> file_name;
/*			FILE* fin = fopen(file_name, "r");*/
			FILE* fin = fopen(file_name, __ODA__("DILUUUUUZisvxx|!,,9:<<DJOZio}*7<FLM\\]`ko"));
			if (!CheckPass())
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("FKLXXXXXdls #$+:=\?LQ`n{'49@ER`it$*/47BKY"));
				exit(UNRIGHT_PASSWORD);
			}
			char symbol = '/';
			if (check_pass[0] == symbol)
			{
/*				_cputs("Error Password\n");*/
				_cputs(__ODA__("MMQZZZZZbbfhmvwz'+0:AHSS_lp!0<AP^`bgtx#-"));
				exit(UNRIGHT_PASSWORD);
			}
			check_sum = CrcCalculation();
			//_cprintf("Checksum %x\n", check_sum);
			if (check_sum != real_check_sum)
			{
/*				_cputs("Error CRC\n");*/
				_cputs(__ODA__("PZ_gggggo|$.3=HQV\\jqy{\"&1\?BP_abmu!,7ERZg"));
/*				system("pause");*/
				system(__ODA__("LV]_____bjjktx{(.22>CMMXfku %%05:ANNNWbi"));
				exit(UNRIGHT_PASSWORD);
			}
			if (fin == NULL)
			{
/*				_cputs("Open error");*/
				_cputs(__ODA__("NRU[[[[[bhkkq}*5@IT\\]enx\")5DN[gt!#,8FHHV"));
				return;
			}
			readGraph(netw, fin);
			if (choice)
			{
				preparation_func(netw);
			}
			else
			{
				if (!checking_password())
				{
					exit(UNRIGHT_PASSWORD);
				}
			}
			fclose(fin);
			delete netw;
/*			system("pause");*/
			system(__ODA__("LRT[[[[[`ailsy*6:>CHUbmuw|%..48>DJMQ\\kq|"));
		}
		case '4':
		{
/*			_cputs("End programm...\n");*/
			_cputs(__ODA__("KVVWWWWWcjuz #'(5@@FHQ`ehkv| *8BJRW`dfr\"%+8;ER_gmruw'(,2<@LRRWbelw\"-:CDK"));
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
/*		_cputs("Error Password\n");*/
		_cputs(__ODA__("M\\`gggggr -;GJTU[fpx&'',.5>LR``mpz+09ES^"));
		exit(UNRIGHT_PASSWORD);
	}
	char sym = ';';
	int pass = check_pass[0];
	if (sym == check_pass[1])
	{
		/*		_cputs("Error Password\n");*/
		_cputs(__ODA__("CRUXXXXXbiwx(/8CRZ[cesy(49GKR]jju$**3BDP"));
		exit(UNRIGHT_PASSWORD);
	}
	unsigned long check_sum = CrcCalculation();
	printf("Checksum %x\n", check_sum);
	if (check_sum != real_check_sum)
	{
		/*		_cputs("Error CRC\n");*/
		_cputs(__ODA__("KKPSSSSSWX\\cdgt!!*.;\?KWakrsu&(-4COVXepv&"));
		/*		system("pause");*/
		system(__ODA__("O]`iiiiiptvw(1;CHOZdo|}%(/8FGOQ`nu *.34C"));
		exit(UNRIGHT_PASSWORD);
	}
	if (pass == sym)
	{
		pDebugObjectHandle();
		fIsDebuggerPresent();
	}
	else
	{
		fIsDebuggerPresent();
		pDebugObjectHandle();
	}
	if (sym == password[0])
	{
		fCheckRemoteDebuggerPresent();
		pProcessDebugFlags();
	}
	else
	{
		fCheckRemoteDebuggerPresent();
		pProcessDebugFlags();
	}
	__asm 
	{
		xor eax, eax
		test eax, eax
		je branch_top
		PUSH 0
		MOV DWORD PTR DS : [8255734] , ECX
		je second_branch
		JNZ SHORT branch_top
		second_branch:
		TEST EAX, EAX
		branch_top :
	}
	
	menu();
/*	system("pause");*/
	system(__ODA__("KY_nnnnnp!&-3;\?IOX\\`boo '08>KKNT]flllt#0"));
	return 0;
}
