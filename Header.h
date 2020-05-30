#pragma once

#include <iostream>

using namespace std;

const int maxN = 20;

typedef struct Node
{
	Node* pnext = nullptr;
	int Vertix = 0;
}*StrAdj;

struct Graph
{
	int numOfVertices = 0;
	bool matrix[maxN][maxN] = { };

	StrAdj str_adj[maxN] = {};

	void addEdge(int i, int j)
	{
		if (i > numOfVertices || j > numOfVertices || i <= 0 || j <= 0 || i == j)
			return;
		i--; j--;
		matrix[i][j] = true;
		matrix[j][i] = true;
	}

	Graph()
	{
		for (int i = 0; i < maxN; i++)
			for (int j = 0; j < maxN; j++)
				matrix[i][j] = 0;
	}

	void save(char* filename)
	{
		FILE* file;
		fopen_s(&file, filename, "wb+");

		if (file)
			fwrite(this, sizeof(Graph), 1, file);

		if (file)
			fclose(file);
	}

	void load(char* filename)
	{
		FILE* file;
		fopen_s(&file, filename, "rb+");

		if (file)
			fread(this, sizeof(Graph), 1, file);

		for (int i = 0; i < numOfVertices; i++)
			str_adj[i] = nullptr;

		this->fromMatrToStrAdj();

		if (file)
			fclose(file);

	}

	void initGraph()
	{
		while (numOfVertices <= 0 || numOfVertices > maxN)
		{
			std::cout << "Num of verticles = ";
			std::cin >> numOfVertices;
		}

		int answer = 1, firstVertix = 0, secondVertix = 0;
		while (answer == 1)
		{
			std::cout << "First vertix = ";
			std::cin >> firstVertix;

			std::cout << "Second vertix = ";
			std::cin >> secondVertix;

			addEdge(firstVertix, secondVertix);

			std::cout << "One more? (1 - Yes, 2 - No)\n";
			std::cin >> answer;

			system("cls");
		}

		this->fromMatrToStrAdj();

		system("cls");
	}

	int getNumOfV()
	{
		return numOfVertices;
	}

	void printMatrix()
	{
		if (!numOfVertices)
			return;

		std::cout << "Matrix is :\n";

		for (int i = 0; i < 4; i++)
			std::cout << ' ';

		for (int i = 0; i < numOfVertices; i++)
		{
			std::cout << '[' << i + 1 << ']';
		}
		std::cout << std::endl;

		for (int i = 0; i < numOfVertices; i++)
		{
			std::cout << '[' << i + 1 << ']';
			std::cout << ' ';

			for (int j = 0; j < numOfVertices; j++)
			{
				std::cout << ' ';
				if (matrix[i][j])
					std::cout << '1';
				else
					std::cout << '0';
				std::cout << ' ';
			}
			std::cout << std::endl;
		}
	}

	void DistMatrix(int** Matrix)
	{
		for (int i = 0; i < numOfVertices; i++)
		{
			for (int j = 0; j < numOfVertices; j++)
			{
				if (matrix[i][j] == true)
				{
					Matrix[i][j] = 1;
				}
				else
				{
					Matrix[i][j] = 0;
				}
			}
		}
	}
	void PrintDistMatr(int** Matrix)
	{
		cout << endl;
		cout << "Matrix is :" << endl;

		for (int i = 0; i < numOfVertices; i++)
		{
			for (int j = 0; j < numOfVertices; j++)
			{
				cout << Matrix[i][j] << ' ';
			}
			cout << endl;
		}
	}

	void printStrAdj()
	{
		if (!numOfVertices)
			return;

		std::cout << "Structure of adjacency is :" << endl;

		for (int j = 0; j < numOfVertices; j++)
		{

			std::cout << '[' << j + 1 << ']' << ' ';

			Node* current = str_adj[j];
			while (current)
			{
				std::cout << current->Vertix << ' ';
				current = current->pnext;
			}
			std::cout << std::endl;
		}
	}

	void fromMatrToStrAdj()
	{
		if (!numOfVertices)
			return;

		for (int j = 0; j < numOfVertices; j++)
		{
			for (int i = 0; i < numOfVertices; i++)
			{
				if (matrix[i][j])
				{
					Node* current = str_adj[j];

					if (!current)
					{
						str_adj[j] = new Node();
						str_adj[j]->Vertix = i + 1;
						current = str_adj[j];
						continue;
					}

					bool isReated = false;

					while (current->pnext)
					{
						if (current->Vertix == i + 1)
							isReated = true;
						current = current->pnext;
					}

					if (isReated)
						continue;

					current->pnext = new Node();
					(current->pnext)->Vertix = i + 1;
				}
			}
		}
	}

};

struct Vertices
{
	int VertNum = 0;

	int SumOfEdges = 0;
};

void floyd(Graph our, int** Matrix);

void RemakeVert(Vertices* vert, Graph my);

void insertionSort(Vertices* verteces, int length);
void MakeInsSort(Graph my, Vertices* vert);

void BubbleSort(Vertices* vert, int length);
void MakeBubSort(Graph my, Vertices* vert);

void ShakerSort(Vertices* vert, int length);
void MakeShakerSort(Graph my, Vertices* vert);

void QuickSort(Vertices* vert, int length, int L, int R);
void MakeQuickSort(Graph my, Vertices* vert);

void MergeSort(int l, int r, int length, Vertices* vert);
void MakeMergeSort(Graph my, Vertices* vert);

void ShellSort(Vertices* vert, int length);
void MakeShellSort(Graph my, Vertices* vert);