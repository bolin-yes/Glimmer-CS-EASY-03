//本文件为和约瑟夫有个约会的修订版，提升代码的运行效率和鲁棒性，在本文件中，代码修改处的注释会加入序号以方便学长辨别哪里进行过修改
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define DEBUG 0//1.是否进入debug模式检查程序
typedef struct _node {
    int data;
    struct _node *next;
    bool firstpass;//用来判断循环链表打印时是否为第一次经过节点
} Node;

Node *head = NULL;
Node *tail = NULL;

// 在链表头部插入节点
   void H(int data1, int data2, int data3, Node **TotalNodes) {
       *TotalNodes = (Node *)malloc(3 * sizeof(Node));
       //2.学习后得知，分配内存是会有系统调用的，也需要相应的时间，分配次数过多有可能产生内存碎片，减少内存的分配次数可以减少系统调用从而提高效率，因此我在这里用了指针的指针一次性分配了三个指针大小的内存，然后通过指针的指针再逐个将内存赋给指针。
       if(TotalNodes==NULL){
        printf("内存分配失败\n");
        exit(0);
       }//3.检查内存是否分配成功若不成功退出程序防止错误
       Node *node1 = *TotalNodes;
       node1->data = data3;
       node1->next = head;

       Node *node2 = *TotalNodes + 1;
       node2->data = data2;
       node2->next = node1;

       Node *node3 = *TotalNodes + 2;
       node3->data = data1;
       node3->next = node2;
       head = node3;
   }
// 在链表尾部插入节点
void T(int data1, int data2, int data3, Node **TotalNodes) {
       *TotalNodes = (Node *)malloc(3 * sizeof(Node));
       //4.这里同理减少内存分配次数。
       if(TotalNodes==NULL){
        printf("内存分配失败\n");
        exit(0);
       }//5.同理，检查内存是否分配成功
       Node *node1 = *TotalNodes;
       node1->data = data1;
       node1->next = NULL;
       if (tail == NULL){
           head = node1;
           tail = node1;
       } else {
           tail->next = node1;
           tail = node1;
       }
       Node *node2 = *TotalNodes + 1;
       node2->data = data2;
       node2->next = NULL;
       tail->next = node2;
       tail = node2;

       Node *node3 = *TotalNodes + 2;
       node3->data = data3;
       node3->next = NULL;
       tail->next = node3;
       tail = node3;
   }

// 删除指定位置的节点
void D(int location) {
    if (location < 1) {
        printf("输入的位置无效！\n");
        return;
    }
    Node *current = head;
    Node *previous = NULL;
    int count = 1;
    while (current!= NULL && count < location){
        previous = current;
        current = current->next;
        count++;
    }//寻找节点位置

    if (current!= NULL) {
        if (previous == NULL) {
            head = current->next;
            if (head == NULL) {
                tail = NULL;
            }
        } //判断要删除的链表是否为头节点
        else {
            previous->next = current->next;
            if (current == tail) {
                tail = previous;
            }
        }
    } 
    else {
        printf("输入的位置无效！\n");
    }
}

// 将尾节点的后继指向头节点
void C(Node **head) {
    if (*head == NULL) {
        return;
    }
    Node *temp = *head;
    while (temp->next!= NULL) {
        temp = temp->next;
    }
    temp->next = *head;
}
//删除报过的数
void del(Node*t){
   Node *m = head;
   Node *previous=NULL;
   
    while (m->next!=t) {
        m = m->next;
}//遍历链表找到要删除的数
m->next=t->next;
}
//报数并将结果导入到Josephus.out
void number(){
    FILE*fp;
    fp=fopen(" Josephus.out","w");
    if(fp==NULL){
        printf("can't open this flie\n");
        exit(0);
        //5.我在这里加入了对文件是否打开成功的判断，如果文件未打开成功，则在终端输出提示并退出程序，防止后续对文件的操作造成未知的后果或者使程序崩溃。
    }
    Node*p=head;
    int order,turn;
    order=1;turn=1;
    while(p!=NULL){
        if(p->data==3)break;
        p=p->next;
    }//找到数据为3的节点
    while(p!=NULL){
        if(p->next==p){
        fprintf(fp,"%d\n",p->data);
        break;//判断是否为最后一个数据
        }
        if(order==turn){
        fprintf(fp,"%d\n",p->data);
        Node*t=p;
        del(t);
        turn=turn+1;
        order=1;
        p=p->next;
        }
        else{
            p=p->next;
            order=order+1;
        }
        
    }
    fclose(fp);
    printf("over");
}
 // 6.我将遍历并打印链表单独制作一个函数，方便进行debug
void print(){
Node *c = head;
    c->firstpass=true;//判断是否为第一次经历该节点
    while (c->firstpass==true) {
        printf("%d -> ", c->data);
        c->firstpass=false;
        c = c->next;
    }
}
int main() {
    head = (Node *)malloc( sizeof(Node));
    head->data = 1;
    head->next = NULL;
    tail = head;

    int operationCount = 16;
    for (int i = 0; i < operationCount; i++) {
        char operation;
        printf("请输入操作（H/T/D/C）：");
        scanf(" %c", &operation);
        int data1, data2, data3, location;
        Node*TotalNodes;
        switch (operation) {
            case 'H':
                printf("请输入三个数据：");
                scanf("%d %d %d", &data1, &data2, &data3);
                H( data1,  data2,  data3, &TotalNodes);
                #if DEBUG
                void print();
                #endif//7.通过更改debug的值进入退出debug模式可以观察链表现况
                break;
            case 'T':
                printf("请输入三个数据：");
                scanf("%d %d %d", &data1, &data2, &data3);
                T( data1,  data2,  data3, &TotalNodes);
                #if DEBUG
                void print();
                #endif//8.通过更改debug的值进入退出debug模式可以观察链表现况
                break;
            case 'D':
                printf("请输入要删除的位置：");
                scanf("%d", &location);
                D(location);
                #if DEBUG
                void print();
                #endif//9.通过更改debug的值进入退出debug模式可以观察链表现况
                break;
            case 'C':
                C(&head);
                break;
            default:
                printf("无效操作！\n");
                i--;//10.当用户错误输入时，将i--避免因为用户的错误操作而导致正确操作的次数减少。
        }
    }
    print();
    printf("\n");
    number();
    return 0;
}
