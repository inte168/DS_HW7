/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("----- 허정윤 2021041047-----\n");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	if(*h != NULL) freeList(*h);//*h가 NULL이 아니면(이미 있음) 할당된 메모리를 해제시킴.

	//*h를 할당해주고 첫 노드를 NULL로 설정해줌.
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	listNode* p = h->first;
	listNode* pre = NULL;
	while(p != NULL){
		//pre로 p값을 넘기고, p값은 rlink로 계속 이동, pre는 해제를 반복한다.
		pre = p;
		p= p->rlink;
		free(pre);
	}
	//h 자체도 해제시켜준다.(이중포인터)
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	//노드를 만들고 값(key, llink, rlink)을 넣어준다
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if(h->first == NULL){//first가 NULL일 때에(h에 다른 노드가 없을 때에) node를 first로
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL){//rlink가 비어있는 노드까지 n을 이동시킴
		n=n->rlink;
	}
	//n의 rlink에 node를 넣고, n의 llink에 n을 넣음.
	n->rlink = node;
	node->llink = n;
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first == NULL){//first가 비어있으면 에러 메시지.
		printf("Error: Nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->rlink == NULL){//노드가 하나인 경우.
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->rlink !=NULL){//마지막 노드까지 이동.(이때 trail은 마지막 전 노드)
		trail = n;
		n = n->rlink;
	}

	//trail의 rlink(n)를 비우고 n을 해제
	trail ->rlink = NULL;
	free(n);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL){//first가 비어있으면 그냥 넣음.
		h->first = node;
		return 1;
	}
	//first를 rlink에 연결.
	node->rlink = h->first;
	//node->llink = NULL; 위에 NULL 해둠.

	//first를 가져와서 llink에 node연결, first를 node로.
	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if(h->first == NULL){//에러메시지
		printf("Error: Nothing to delete.\n");
		return 0;
	}

	//n을 만들어서 n의 rlink를 h->first로 
	listNode* n = h->first;
	h->first = n->rlink;

	//n(처음 h->first)를 해제한다.
	free(n);
	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	if(h->first == NULL){//없으면 에러메시지.
		printf("Error: nothing to Invert.\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n !=NULL){//n을 옮겨가면서 middle을 이용하여 trail과 n을 rlink,llink에 붙여서 invert 리스트를 생성
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	//위에서 middle로 정렬되어있기 때문에 middle을 first로.
	h->first = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	//node를 만들어서 key, llink, rlink를 넣어준다.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink=node->rlink=NULL;

	if(h->first == NULL){//없으면 그대로 노드를 first로 넣어준다.
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while(n!=NULL){
		if(n->key >=key){//삽입 위치 파악.
			if(n == h->first){//첫 노드 앞쪽인지 확인하여 insetFirst.
				insertFirst(h,key);
			}
			else{//아닌 경우 n을 node의 rlink에, n->llink를 node의 llink에, n->llink의 rlink에 node를 넣어준다.
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n=n->rlink;
	}

	//못찾은 경우 마지막에 삽입 
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL){
		printf("Error: Nothing to delete\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL){
		if(n->key == key){
			if(n==h->first){//맨 앞이면 deleteFirst로 넘김.
				deleteFirst(h);
			}
			else if (n->rlink == NULL){//마지막 노드는 deleteLast로 넘김.
				deleteLast(h);
			}
			else{//중간 어딘가이면 n의 왼쪽의 rlink에 n의 rlink, n의 오른쪽의 llink에 n의 llink를 넣는다.
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n=n->rlink;
	}//여담으로 for문으로도 가능.

	//여기로 왔다는 것은 찾지 못했단 이야기.
	printf("Error: Cannot find the node for key = %d\n", key);
	return 1;
}


