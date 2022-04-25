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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
	printf("----- ������ 2021041047-----\n");
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
	if(*h != NULL) freeList(*h);//*h�� NULL�� �ƴϸ�(�̹� ����) �Ҵ�� �޸𸮸� ������Ŵ.

	//*h�� �Ҵ����ְ� ù ��带 NULL�� ��������.
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	listNode* p = h->first;
	listNode* pre = NULL;
	while(p != NULL){
		//pre�� p���� �ѱ��, p���� rlink�� ��� �̵�, pre�� ������ �ݺ��Ѵ�.
		pre = p;
		p= p->rlink;
		free(pre);
	}
	//h ��ü�� ���������ش�.(����������)
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	//��带 ����� ��(key, llink, rlink)�� �־��ش�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if(h->first == NULL){//first�� NULL�� ����(h�� �ٸ� ��尡 ���� ����) node�� first��
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL){//rlink�� ����ִ� ������ n�� �̵���Ŵ
		n=n->rlink;
	}
	//n�� rlink�� node�� �ְ�, n�� llink�� n�� ����.
	n->rlink = node;
	node->llink = n;
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	if(h->first == NULL){//first�� ��������� ���� �޽���.
		printf("Error: Nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->rlink == NULL){//��尡 �ϳ��� ���.
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->rlink !=NULL){//������ ������ �̵�.(�̶� trail�� ������ �� ���)
		trail = n;
		n = n->rlink;
	}

	//trail�� rlink(n)�� ���� n�� ����
	trail ->rlink = NULL;
	free(n);

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL){//first�� ��������� �׳� ����.
		h->first = node;
		return 1;
	}
	//first�� rlink�� ����.
	node->rlink = h->first;
	//node->llink = NULL; ���� NULL �ص�.

	//first�� �����ͼ� llink�� node����, first�� node��.
	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if(h->first == NULL){//�����޽���
		printf("Error: Nothing to delete.\n");
		return 0;
	}

	//n�� ���� n�� rlink�� h->first�� 
	listNode* n = h->first;
	h->first = n->rlink;

	//n(ó�� h->first)�� �����Ѵ�.
	free(n);
	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	if(h->first == NULL){//������ �����޽���.
		printf("Error: nothing to Invert.\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n !=NULL){//n�� �Űܰ��鼭 middle�� �̿��Ͽ� trail�� n�� rlink,llink�� �ٿ��� invert ����Ʈ�� ����
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	//������ middle�� ���ĵǾ��ֱ� ������ middle�� first��.
	h->first = middle;

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	//node�� ���� key, llink, rlink�� �־��ش�.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink=node->rlink=NULL;

	if(h->first == NULL){//������ �״�� ��带 first�� �־��ش�.
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while(n!=NULL){
		if(n->key >=key){//���� ��ġ �ľ�.
			if(n == h->first){//ù ��� �������� Ȯ���Ͽ� insetFirst.
				insertFirst(h,key);
			}
			else{//�ƴ� ��� n�� node�� rlink��, n->llink�� node�� llink��, n->llink�� rlink�� node�� �־��ش�.
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n=n->rlink;
	}

	//��ã�� ��� �������� ���� 
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL){
		printf("Error: Nothing to delete\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL){
		if(n->key == key){
			if(n==h->first){//�� ���̸� deleteFirst�� �ѱ�.
				deleteFirst(h);
			}
			else if (n->rlink == NULL){//������ ���� deleteLast�� �ѱ�.
				deleteLast(h);
			}
			else{//�߰� ����̸� n�� ������ rlink�� n�� rlink, n�� �������� llink�� n�� llink�� �ִ´�.
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n=n->rlink;
	}//�������� for�����ε� ����.

	//����� �Դٴ� ���� ã�� ���ߴ� �̾߱�.
	printf("Error: Cannot find the node for key = %d\n", key);
	return 1;
}


