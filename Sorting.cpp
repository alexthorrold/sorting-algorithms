#include <iostream>

void bubbleSort(int *a, int n)
{
	int flag;

	for (int i = 0; i < n - 1; i++)
	{
		flag = 0;

		for (int j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;
			}
		}

		if (flag == 0)
			break;
	}
}

void insertionSort(int *a, int n)
{
	for (int i = 1; i < n; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (a[j] < a[j - 1])
			{
				int temp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = temp;
			}
			else
			{
				break;
			}
		}
	}
}

void selectionSort(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		int minIndex = i;

		for (int j = i; j < n; j++)
		{
			if (a[j] < a[minIndex])
				minIndex = j;
		}

		int temp = a[i];
		a[i] = a[minIndex];
		a[minIndex] = temp;
	}
}

int smallest(int a, int b, int c)
{
	if (a < b && a < c)
		return a;
	else if (b < a && b < c)
		return b;
	else
		return c;
}

int middle(int a, int b, int c)
{
	if ((a < b && a > c) || (a > b && a < c))
		return a;
	else if ((b < a && b > c) || (b > a && b < c))
		return b;
	else
		return c;
}

int largest(int a, int b, int c)
{
	if (a > b && a > c)
		return a;
	else if (b > a && b > c)
		return b;
	else
		return c;
}

void swap(int *a, int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void quickSort(int *a, int s, int l)
{
	if (s == l)
		return;

	int first = a[s];
	int second = a[l / 2];
	int third = a[l];

	a[s] = smallest(first, second, third);
	a[l / 2] = largest(first, second, third);
	a[l] = middle(first, second, third);

	int i = s, j = l - 1;

	while (i <= j)
	{
		if (a[i] > a[l] && a[j] < a[l])
			swap(a, i, j);

		if (a[i] < a[l])
			i++;
		
		if (a[j] > a[l])
			j--;
	}

	swap(a, i, l);
	quickSort(a, s, j);
	quickSort(a, i + 1, l);
}

struct Array
{
	int *a;
	unsigned capacity;
};

Array *newArray(unsigned capacity)
{
	Array *a = (Array *)malloc(sizeof(Array));
	a->a = (int *)malloc(capacity * sizeof(int));
	a->capacity = capacity;

	return a;
}

Array *sortedMerge(Array *a, Array *b)
{
	Array *returnArray = newArray(a->capacity + b->capacity);

	int i = 0, j = 0, k = 0;

	while (i < a->capacity || j < b->capacity)
	{
		if (i < a->capacity && j < b->capacity)
		{
			if (a->a[i] < b->a[j])
				returnArray->a[k] = a->a[i++];
			else
				returnArray->a[k] = b->a[j++];
		}
		else if (i < a->capacity)
		{
			returnArray->a[k] = a->a[i++];
		}
		else
		{
			returnArray->a[k] = b->a[j++];
		}

		k++;
	}

	return returnArray;
}


Array *concat(Array *a, int s, int e)
{
	Array *returnArray = newArray(e - s + 1);

	for (int i = 0; i <= e; i++)
	{
		returnArray->a[i] = a->a[i + s];
	}

	return returnArray;
}

//struct Node
//{
//	int data;
//	Node *next;
//};
//
//Node *newNode(int data)
//{
//	Node *n = (Node *)malloc(sizeof(Node));
//	n->data = data;
//	n->next = NULL;
//}
//
//void insert(Node *root, int data)
//{
//	Node *n = root;
//	Node *add = newNode(data);
//
//	while (n->next)
//		n = n->next;
//
//	n->next = add;
//}

void moveLeft(Array *a, int from, int to)
{
	int temp = a->a[from];

	for (int i = from; i > to; i--)
	{
		a->a[i] = a->a[i - 1];
	}

	a->a[to] = temp;
}

void somethingSort(Array *a, int s, int e)
{
	if (s >= e)
		return;

	int pivot = a->a[s];
	int pivotIndex = s;

	for (int i = s + 1; i <= e; i++)
	{
		if (a->a[i] < pivot)
		{
			moveLeft(a, i, pivotIndex);
			pivotIndex++;
		}
	}

	somethingSort(a, s, pivotIndex - 1);
	somethingSort(a, pivotIndex + 1, e);
}

void merge(Array *a, int s, int m, int e)
{
	Array *temp = newArray(e - s + 1);

	for (int i = s, j = m, k = s; i < m || j <= e;)
	{
		if (i < m && j <= e)
		{
			if (a->a[i] < a->a[j])
			{
				temp->a[k] = a->a[i];
				i++;
			}
			else
			{
				temp->a[k] = a->a[j];
				j++;
			}
		}
		else if (i < m)
		{
			temp->a[k] = a->a[i];
			i++;
		}
		else
		{
			temp->a[k] = a->a[j];
			j++;
		}

		k++;
	}

	for (int i = 0; i < temp->capacity; i++)
	{
		a->a[i + s] = temp->a[i];
	}

	free(temp);
}

void mergeSort(Array *a, int s, int e)
{
	if (s == e)
		return;

	int m = (s + e) / 2 + 1;

	mergeSort(a, s, m);
	mergeSort(a, m + 1, e);

	merge(a, s, m + 1, e);
}

int max(Array *a)
{
	int max = a->a[0];

	for (int i = 1; i < a->capacity; i++)
	{
		if (a->a[i] > max)
			max = a->a[i];
	}

	return max;
}

void countSort(Array *a)
{
	Array *hash = newArray(max(a) + 1);

	for (int i = 0; i < hash->capacity; i++)
		hash->a[i] = 0;

	for (int i = 0; i < a->capacity; i++)
		hash->a[a->a[i]]++;

	for (int i = 0, j = 0; i < hash->capacity; i++)
	{
		while (hash->a[i] > 0)
		{
			a->a[j] = i;
			hash->a[i]--;
			j++;
		}
	}
}

int main()
{
	//int *a = (int *)malloc(4 * sizeof(int));
	//a[0] = 8;
	//a[1] = 5;
	//a[2] = 7;
	//a[3] = 2;
	//a[4] = 3;

	//quickSort(a, 0, 4);

	//for (int i = 0; i < 5; i++)
	//	printf("%d\n", a[i]);

	Array *a = newArray(7);

	a->a[0] = 4;
	a->a[1] = 1;
	a->a[2] = 3;
	a->a[3] = 7;
	a->a[4] = 5;
	a->a[5] = 8;
	a->a[6] = 2;
	//a->a[0] = 1;
	//a->a[1] = 3;
	//a->a[2] = 7;
	//a->a[3] = 2;
	//a->a[4] = 4;
	//a->a[5] = 5;
	//a->a[6] = 8;

	//mergeSort(a, 0, 6);
	//merge(a, 0, 3, 6);

	//mergeSort(a, 0, a->capacity - 1);

	//Array *a = newArray(2);
	//a->a[0] = 4;
	//a->a[1] = 3;

	//merge(a, 0, 1, 1);

	countSort(a);

	for (int i = 0; i < a->capacity; i++)
		printf("%d ", a->a[i]);
}
