#include<stdio.h>
#include<malloc.h>
#define MaxData 2147483647
#define ERROR -1
typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    ElementType *Elements; // 存储堆元素的数组
    int Size; //堆的当前元素个数
    int Capacity; //The maximum capacity of the heap
};

// abstract methods
MaxHeap Create(int MaxSize);//create a new heap
bool IsFull(MaxHeap heap); //return true if the heap is full
bool Insert(MaxHeap heap, ElementType item); //insert a new element into the heap
bool IsEmpty(MaxHeap heap); //return true if the heap is empty
ElementType Remove(MaxHeap heap); //remove an element from the top of the heap
void LevelOrderTraversal(MaxHeap heap); //Level Order Traversal

// create a new heap
MaxHeap Create(int MaxSize){
    MaxHeap heap = (MaxHeap)malloc(sizeof(struct HeapStruct));
    // Elements[0] as sentinel, heap element storage from Element[1]
    heap-> Elements = (ElementType *)malloc(sizeof(MaxSize + 1) * sizeof(ElementType));
    heap-> Size = 0;
    heap-> Capacity = MaxSize;
    // Sentinel greater than any possible value
    heap-> Elements[0] = MaxData;
    return heap;
}

// insert a new element into the heap
bool Insert(MaxHeap heap, ElementType item){
    if (IsFull){
        printf("Heap is full, cannot insert!\n");7
        return false;
    }
    int i = ++heap-> Size; // i points to the last position insert into the heap
    for (;heap-> Elements[i/2] < item; i /= 2){ // i/=2 is finding the parent element,
    //stop where the parent value is greater than insert value
        heap-> Elements[i] = heap-> Elements[i / 2]; 
        // let the child element has the parent element's value
    }
    heap-> Elements[i] = item; // give the insert value to parent element
    return true; // insert successed
}

ElementType Remove(MaxHeap heap, ElementType){
    int parent, child;
    ElementType maxItem, temp;
    if (IsEmpty(heap)){
        printf("Heap is empty");
        return;
    }
    maxItem = heap-> Elements[1]; // delete the root, save it in maxItem
    temp = heap-> Elements[heap-> Size--]; // get the last element
    // condition: parent has left child element? parent * 2 is the position of the left child
    // this for loop is finding the right position for temp
    // finding from the root element    
    for (parent = 1; parent * 2 <= heap->Size; parent = child){
        // child index points to the left child
        child = parent * 2;
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
    for (int i = 1; i < heap->Size; i++){
        printf("%D", heap->Elements[i]);
    }
}

int main(int argc, char const *argv[])
{
    MaxHeap heap = Create(1000); 

    return 0;
}

