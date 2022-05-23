#include<stdio.h>
#include<malloc.h>
#define MaxData 100000
#define ERROR -1
typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
	ElementType *Elements;   // �洢��Ԫ�ص����� 
	int Size;      // �ѵĵ�ǰԪ�ظ��� 
	int Capacity;  // �ѵ�������� 
};

MaxHeap Create(int MaxSize);  // ���� 
bool IsFull(MaxHeap H);    // �ж϶��Ƿ���
bool Insert(MaxHeap H,ElementType item);   // ����Ԫ��
bool IsEmpty(MaxHeap H);    //  �ж϶��Ƿ�Ϊ��
ElementType DeleteMax(MaxHeap H);  // ɾ�������ض������Ԫ��
void LevelOrderTraversal(MaxHeap H);  // ������� 

// ���� 
MaxHeap Create(int MaxSize){
	MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapStruct));
	// Elements[0] ��Ϊ�ڱ�����Ԫ�ش�  Elements[1] ��ʼ��� 
	H->Elements = (ElementType *)malloc((MaxSize+1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	// "�ڱ�"���ڶ������п��ܵ�ֵ 
	H->Elements[0] = MaxData;
	return H;
} 

// ���룬����ȫ�����������һ��λ�ò��� 
bool Insert(MaxHeap H,ElementType item){
	if(IsFull(H)){
		printf("���������޷����룡\n");
		return false;
	}
	int i = ++H->Size;  // ָ��������һ��λ�� 
	for(;H->Elements[i/2] < item;i/=2)    // �����ұ� item ��Ľ�� 
		H->Elements[i] = H->Elements[i/2];  //  ���¸�ֵ 
	H->Elements[i] = item;  // �ҵ��ˣ��� item ֵ�Ž�ȥ 
	return true;
}

// ɾ�����Ӹ����ɾ�� 
ElementType DeleteMax(MaxHeap H){
	int parent,child;
	ElementType Max,tmp;
	if(IsEmpty(H)){
		printf("��Ϊ�գ��޷�ɾ����\n");
		return ERROR;
	}
	Max = H->Elements[1];  // �õ����ֵ
	tmp = H->Elements[H->Size--];  // �õ���ȫ���������һ��ֵ 
	// �б�������parent �Ƿ������ӽ�� 
	for(parent=1;parent*2<=H->Size;parent=child){
		// ���Һ��ӽ�����ҽϴ��ֵ 
		child = 2 * parent;  // ���ӽ�� 
		// child!=H->Size ��ʾ child ��Ϊ��ǰ���һ����㣬�� parent ���Һ��ӽ�� 
		if((child!=H->Size) &&(H->Elements[child] < H->Elements[child+1]))
			child++;  
		// �� tmp �Ҹ����ʵ�λ�� 
		// �����ǰ���Һ��ӽ��� tmp ��С��˵�� tmp λ���Ѿ����� 
		if(H->Elements[child] <= tmp)
			break;
		else    // ����ѽϴ�ĺ��ӽ�����������Լ�������ȥ�� 
			H->Elements[parent] = H->Elements[child];
	}
	H->Elements[parent] = tmp;  // �ں��ʵ�λ�ð� tmp �Ž�ȥ 
	return Max;
} 

// �ж��Ƿ��Ѿ��� 
bool IsFull(MaxHeap H){
	return (H->Size == H->Capacity);
}

// �ж��Ƿ�Ϊ��
bool IsEmpty(MaxHeap H){
	return !H->Size;
}

// �������
void LevelOrderTraversal(MaxHeap H){
	int i;
	printf("��������Ľ���ǣ�");
	for(i = 1;i<=H->Size;i++){
		printf("%d ",H->Elements[i]);
	} 
	printf("\n"); 
} 

int main(){
	MaxHeap H;
	int MaxSize = 100;
	H = Create(MaxSize);
	Insert(H,55);
	Insert(H,66);
	Insert(H,44);
	Insert(H,33);
	Insert(H,11);
	Insert(H,22);
	Insert(H,88);
	Insert(H,99);
	/*
		 99
		/  \
	   88  66
	  / \  / \
	 55 11 22 44
	/ 
   33	  
	*/
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	return 0;
}


























