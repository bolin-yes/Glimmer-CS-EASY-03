#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef struct _node {
    int data;
    struct _node *next;
    bool firstpass;//用来判断循环链表打印时是否为第一次经过节点
} Node;

Node *head = NULL;
Node *tail = NULL;

// 在链表头部插入节点
void H(int data1, int data2, int data3) {
    Node *node1 = (Node *)malloc(sizeof(Node));
    node1->data = data3;
    node1->next = head;
    head = node1;

    Node *node2 = (Node *)malloc(sizeof(Node));
    node2->data = data2;
    node2->next = head;
    head = node2;

    Node *node3 = (Node *)malloc(sizeof(Node));
    node3->data = data1;
    node3->next = head;
    head = node3;
}

// 在链表尾部插入节点
void T(int data1, int data2, int data3) {
    Node *node1 = (Node *)malloc(sizeof(Node));
    node1->data = data1;
    node1->next = NULL;
    tail->next=node1;
    tail=node1;

    Node *node2 = (Node *)malloc(sizeof(Node));
    node2->data = data2;
    node2->next = NULL;
    tail->next = node2;
    tail = node2;

    Node *node3 = (Node *)malloc(sizeof(Node));
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
        free(current);
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
int main() {
    head = (Node *)malloc(sizeof(Node));
    head->data = 1;
    head->next = NULL;
    tail = head;

    int operationCount = 16;
    for (int i = 0; i < operationCount; i++) {
        char operation;
        printf("请输入操作（H/T/D/C）：");
        scanf(" %c", &operation);
        int data1, data2, data3, location;
        switch (operation) {
            case 'H':
                printf("请输入三个数据：");
                scanf("%d %d %d", &data1, &data2, &data3);
                H(data1, data2, data3);
                break;
            case 'T':
                printf("请输入三个数据：");
                scanf("%d %d %d", &data1, &data2, &data3);
                T(data1, data2, data3);
                break;
            case 'D':
                printf("请输入要删除的位置：");
                scanf("%d", &location);
                D(location);
                break;
            case 'C':
                C(&head);
                break;
            default:
                printf("无效操作！\n");
        }
    }

    // 遍历并打印链表
    Node *c = head;
    c->firstpass=true;//判断是否为第一次经历该节点
    while (c->firstpass==true) {
        printf("%d -> ", c->data);
        c->firstpass=false;
        c = c->next;
    }
    printf("\n");
    number();
    return 0;
}
