#include "Header.h"

void floyd(Graph our, int** Matrix)
{
	int i, j, k;

	for (k = 0; k < our.getNumOfV(); k++)
	{
		for (i = 0; i < our.getNumOfV(); i++)
		{
			for (j = 0; j < our.getNumOfV(); j++)
			{
				if (i == j)
				{
					Matrix[i][j] = 0;
					continue;
				}
				if (Matrix[i][k] != 0 && Matrix[k][j] != 0 && Matrix[i][j] != 0)
				{
					if (Matrix[i][k] + Matrix[k][j] < Matrix[i][j])
					{
						Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
					}
				}
				else if (Matrix[i][j] != 0)
				{
					continue;
				}
				else if (Matrix[i][k] != 0 && Matrix[k][j] != 0)
				{
					Matrix[i][j] = Matrix[i][k] + Matrix[k][j];
				}
			}
		}
	}
};

void RemakeVert(Vertices* vert, Graph my)
{
	for (int i = 0; i < my.numOfVertices; i++)
	{
		vert[i].SumOfEdges = 0;
		vert[i].VertNum = 0;
	}
	for (int i = 0; i < my.numOfVertices; i++)
	{
		vert[i].VertNum = i + 1;

		for (int j = 0; j < my.numOfVertices; j++)
		{
			if (my.matrix[i][j] == true)
			{
				vert[i].SumOfEdges++;
			}
		}
	}
}

void insertionSort(Vertices* verteces, int length)
{
	Vertices temp;
	int	item;
	for (int i = 1; i < length; i++)
	{
		temp = verteces[i];
		item = i - 1;
		while (item >= 0 && verteces[item].SumOfEdges > temp.SumOfEdges)
		{
			verteces[item + 1] = verteces[item];
			verteces[item] = temp;
			item--;
		}
	}
}

void MakeInsSort(Graph my, Vertices* vert)
{
	cout << endl;

	insertionSort(vert, my.numOfVertices);

	cout << "Insertion Sort : " << endl;

	for (int i = 0; i < my.numOfVertices; i++)
	{
		cout << '[' << vert[i].VertNum << ']' << " : " << vert[i].SumOfEdges << endl;
	}
	cout << endl;
}

void BubbleSort(Vertices* vert, int length)
{
	Vertices temp;
	bool exit = false;

	while (!exit)
	{
		exit = true;
		for (int i = 0; i < (length - 1); i++)
		{
			if (vert[i].SumOfEdges > vert[i + 1].SumOfEdges)
			{
				temp = vert[i];
				vert[i] = vert[i + 1];
				vert[i + 1] = temp;
				exit = false;
			}
		}
	}
}

void MakeBubSort(Graph my, Vertices* vert)
{
	cout << endl;

	BubbleSort(vert, my.numOfVertices);

	cout << "Bubble Sort : " << endl;

	for (int i = 0; i < my.numOfVertices; i++)
	{
		cout << '[' << vert[i].VertNum << ']' << " : " << vert[i].SumOfEdges << endl;
	}
	cout << endl;
}

void ShakerSort(Vertices* vert, int length)
{
	int Left, Right, i;
	Left = 0;
	Right = length - 1;

	while (Left <= Right)
	{
		for (i = Right; i >= Left; i--)
		{
			if (vert[i - 1].SumOfEdges > vert[i].SumOfEdges)
			{
				Vertices temp = vert[i];
				vert[i] = vert[i - 1];
				vert[i - 1] = temp;
			}
		}

		Left++;

		for (i = Left; i <= Right; i++)
		{
			if (vert[i - 1].SumOfEdges > vert[i].SumOfEdges)
			{
				Vertices temp = vert[i];
				vert[i] = vert[i - 1];
				vert[i - 1] = temp;
			}
		}

		Right--;
	}
}

void MakeShakerSort(Graph my, Vertices* vert)
{
	cout << endl;

	ShakerSort(vert, my.numOfVertices);

	cout << "Shaker Sort : " << endl;

	for (int i = 0; i < my.numOfVertices; i++)
	{
		cout << '[' << vert[i].VertNum << ']' << " : " << vert[i].SumOfEdges << endl;
	}
	cout << endl;
}

void QuickSort(Vertices* vert, int length, int L, int R)
{
	int i = L, j = R;

	int mid = (R + L) / 2;

	Vertices first = vert[mid];
	Vertices sec;

	do
	{
		while (vert[i].SumOfEdges < first.SumOfEdges)
		{
			i++;
		}

		while (first.SumOfEdges < vert[j].SumOfEdges)
		{
			j--;
		}

		if (i <= j)
		{
			sec = vert[i];
			vert[i] = vert[j];
			vert[j] = sec;

			i++;
			j--;
		}
	} while (i < j);

	if (L < j)
	{
		QuickSort(vert, length, L, j);
	}

	if (i < R)
	{
		QuickSort(vert, length, i, R);
	}
}

void MakeQuickSort(Graph my, Vertices* vert)
{
	cout << endl;

	QuickSort(vert, my.numOfVertices, 0, my.numOfVertices - 1);

	cout << "Quick Sort : " << endl;

	for (int i = 0; i < my.numOfVertices; i++)
	{
		cout << '[' << vert[i].VertNum << ']' << " : " << vert[i].SumOfEdges << endl;
	}
	cout << endl;
}

void MergeSort(int l, int r, int length, Vertices* vert) 
{
	if (r == l)
	{
		return;
	}

	if (r - l == 1) 
	{
		if (vert[r].SumOfEdges < vert[l].SumOfEdges)
		{
			swap(vert[r], vert[l]);
		}
		return;
	}

	int m = (r + l) / 2;

	MergeSort(l, m, length, vert);
	MergeSort(m + 1, r, length, vert);

	Vertices* buf = new Vertices[length];

	int xl = l;
	int xr = m + 1;
	int cur = 0;

	while (r - l + 1 != cur) 
	{
		if (xl > m)
		{
			buf[cur++] = vert[xr++];
		}
		else if (xr > r)
		{
			buf[cur++] = vert[xl++];
		}
		else if (vert[xl].SumOfEdges > vert[xr].SumOfEdges)
		{
			buf[cur++] = vert[xr++];
		}
		else 
		{
			buf[cur++] = vert[xl++];
		}
	}
	for (int i = 0; i < cur; i++)
	{
		vert[i + l] = buf[i];
	}
}

void MakeMergeSort(Graph my, Vertices* vert)
{
	cout << endl;

	MergeSort(0, my.numOfVertices - 1, my.numOfVertices, vert);

	cout << "Merge Sort : " << endl;

	for (int i = 0; i < my.numOfVertices; i++)
	{
		cout << '[' << vert[i].VertNum << ']' << " : " << vert[i].SumOfEdges << endl;
	}
	cout << endl;
}

void ShellSort(Vertices* vert, int length)
{
	for (int d = length / 2; d >= 1; d /= 2)
	{
		for (int i = d; i < length; i++)
		{
			for (int j = i; j >= d && vert[j - d].SumOfEdges > vert[j].SumOfEdges; j -= d)
			{
				swap(vert[j], vert[j - d]);
			}
		}
	}
}

void MakeShellSort(Graph my, Vertices* vert)
{
	cout << endl;

	ShellSort(vert,my.numOfVertices);

	cout << "Shell Sort : " << endl;

	for (int i = 0; i < my.numOfVertices; i++)
	{
		cout << '[' << vert[i].VertNum << ']' << " : " << vert[i].SumOfEdges << endl;
	}
	cout << endl;
}