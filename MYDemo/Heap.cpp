#include<stdio.h>
#include<malloc.h>
#define MaxData 2147483647
#define ERROR -1
typedef int T;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    T *Elements; // 存储堆元素的数组
    int Size; //堆的当前元素个数
    int Capacity; //The maximum capacity of the heap
};

// abstract methods
MaxHeap New(int eles[], int MaxSize);
MaxHeap Create(int MaxSize);//create a new heap
bool IsFull(MaxHeap heap); //return true if the heap is full
bool Insert(MaxHeap heap, T item); //insert a new element into the heap
bool IsEmpty(MaxHeap heap); //return true if the heap is empty
T Remove(MaxHeap heap); //remove an element from the top of the heap
void Sort(MaxHeap heap); //sort the heap
bool Verify(MaxHeap heap); //return true if the heap is well formed
int FindGreatChild(MaxHeap heap, int parent);
void LevelOrderTraversal(MaxHeap heap); //Level Order Traversal

// create a new heap with the given elements and capacity 
MaxHeap New(int eles[], int MaxSize){
    MaxHeap heap = (MaxHeap)malloc(sizeof(struct HeapStruct));
    heap -> Elements = (T *)malloc(sizeof(MaxSize + 1) * sizeof(T));
    heap -> Size = 21;
    printf("Size of elements = %d\n", heap -> Size);
    heap-> Capacity = MaxSize;
    heap-> Elements[0] = MaxData;
    for (int i = 0; i < heap->Size; i++){
        heap->Elements[i+1] = eles[i];
    };
    //DONE
    return heap;
}


// create a empty heap
MaxHeap Create(int MaxSize){
    MaxHeap heap = (MaxHeap)malloc(sizeof(struct HeapStruct));
    // Elements[0] as sentinel, heap element storage from Element[1]
    heap-> Elements = (T *)malloc(sizeof(MaxSize + 1) * sizeof(T));
    heap-> Size = 0;
    heap-> Capacity = MaxSize;
    // Sentinel greater than any possible value
    heap-> Elements[0] = MaxData;
    return heap;
}

// insert a new element into the heap
bool Insert(MaxHeap heap, T item){
    if (IsFull(heap)){
        printf("Heap is full, cannot insert!\n");
        return false;
    }
    int i = ++heap-> Size; // i points to the last position insert into the heap
    for (;heap-> Elements[i/2] < item; i /= 2){ // i/=2 is finding the parent element,
    //stop where the parent value is greater than insert value
        heap-> Elements[i] = heap-> Elements[i / 2]; 
        // let the child element has the parent element's value
    }
    heap-> Elements[i] = item; // give the insert value to parent element
    //printf("i = %d, There size is %d",i, heap->Size);
    //LevelOrderTraversal(heap);
    return true; // insert successed
}

T Remove(MaxHeap heap){
    int parent, child;
    T maxItem, temp;
    if (IsEmpty(heap)){
        printf("Heap is empty");
        return ERROR;
    }
    maxItem = heap-> Elements[1]; // delete the root, save it in maxItem
    temp = heap-> Elements[heap-> Size--]; // get and delete the last element
    
    // condition: parent has left child element? parent * 2 is the position of the left child
    // this for loop is finding the right position for temp
    // finding from the root element    
    for (parent = 1; parent * 2 <= heap->Size; parent = child){
        printf("In Function travers");LevelOrderTraversal(heap);
        // child index points to the left child
        child = parent * 2;//即使temp是右侧最小值，也可以给左侧赋值
        // child is not the last element which means there is a right child element
        if ((child != heap->Size) && 
            // find the greater child element
            (heap->Elements[child] < heap-> Elements[child + 1])){
            child++;
        }
        // condition: temp is greater than the greater child element, go to next recursion
        if (heap->Elements[child] <= temp){
            break;
        }
        else{
            heap->Elements[parent] = heap-> Elements[child];
        }
    }
    heap-> Elements[parent] = temp;
    return maxItem;
}

bool IsFull(MaxHeap heap){
    return (heap->Size == heap->Capacity);
}

bool IsEmpty(MaxHeap heap){
    if (heap->Size == 0){
        return true;
    }
    return false;
}

void LevelOrderTraversal(MaxHeap heap){
    printf("LevelOrderTraversal Resulting: ");
    for (int i = 1; i <= heap->Size; i++){
        printf("%d ", heap->Elements[i]);
    }
    printf("\n");
}

void Sort(MaxHeap heap){
    int parent = heap->Size / 2;
    int child;
    
    while (parent >= 1){
        child = parent * 2;
        int temp = heap->Elements[parent];
        if ((child + 1) / 2 == parent && 
        heap->Elements[child + 1] > heap->Elements[child]){
            child++;
        }
        if (temp < heap->Elements[child]){
            heap->Elements[parent] = heap->Elements[child];
            heap->Elements[child] = temp;
        }
        printf("In MID Function travers, parent = %d\t", parent);
        LevelOrderTraversal(heap);
        if (parent * 4 <= heap->Size){
            int id1 = FindGreatChild(heap, parent);
            int id2 = FindGreatChild(heap, id1);
            if (id1 != -1 && id2 != -1){
                child = FindGreatChild(heap, parent);
                int grandchild = FindGreatChild(heap, child);
                if (heap->Elements[child] < heap-> Elements[grandchild]){
                    temp = heap-> Elements[child];
                    heap->Elements[child] = heap-> Elements[grandchild];
                    heap->Elements[grandchild] = temp;
                }
            }
        }
        printf("In END Function travers, parent = %d\t", parent);
        LevelOrderTraversal(heap);
        parent--;
    }
}

int FindGreatChild(MaxHeap heap, int parent){
    if (parent *2 > heap->Size){
        return ERROR;
    }
    int child = parent * 2;
    if (child != heap->Size &&
    heap->Elements[child] < heap-> Elements[child + 1]){
        return child + 1;
    }
    return child;
}

bool Verify(MaxHeap heap){
    int parent = heap->Size / 2;
    int child;
    while (parent >= 1){
        child = parent * 2;
        if (child != heap->Size &&
        heap->Elements[child] < heap->Elements[child + 1]){
            child++;
        }
        if (heap->Elements[parent] < heap->Elements[child]){ 
        return false;
        }
        parent--;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    int MaxSize = 100;
    /*
	MaxHeap H = Create(MaxSize);
	Insert(H,10);
	Insert(H,8);
	Insert(H,9);
	Insert(H,4);
	Insert(H,6);
    Insert(H,5);
    Insert(H,3);
    
    LevelOrderTraversal(H);
    printf("\n");
	Remove(H);
	LevelOrderTraversal(H);
    */
    
    int elements[] ={79,66,43,83,30,87,38,55,91,72,49,9,99, 100, 101,102,103, 104,105,106,107};  
    MaxHeap heap = New(elements, 100);
    if (Verify(heap)){
        printf("Is well formed\n");
    }else{
        printf("Not well formed\n");
    }
    Sort(heap);
    printf("after sorting: \n");
    LevelOrderTraversal(heap);
    if (Verify(heap)){
        printf("Is well formed\n");
    }else{
        printf("Not well formed\n");
    }
    return 0;
}

