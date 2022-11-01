#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define informationSize 50
#define cut ","

struct Node {
	char flight[informationSize];
	char destination[informationSize];
	char take_off[informationSize];
	char landing[informationSize];
	Node* next;
};

struct Node2 {
	char destination[informationSize];
	Node2* next;
};

void add(Node* list, char* flight, char* destination, char* take_off, char* landing) {
	Node* lookFor = list;
	Node* ptr = lookFor;
	Node* newNode = (Node*)malloc(sizeof(Node));
	lookFor = list->next;
	while (lookFor && strcmp(lookFor->take_off, take_off) < 0) {	//�Ƨ�
		ptr = lookFor;
		lookFor = lookFor->next;
	}
	strcpy(newNode->flight, flight);
	strcpy(newNode->destination, destination);
	strcpy(newNode->take_off, take_off);
	strcpy(newNode->landing, landing);
	newNode->next = lookFor;
	ptr->next = newNode;
}

void addAirLine(Node2* list, char* destination) {
	Node2* tail = list;
	Node2* ptr = NULL;
	Node2* newNode = (Node2*)malloc(sizeof(Node));
	strcpy(newNode->destination, destination);
	newNode->next = NULL;
	int count = 0;
	while (tail->next) {
		if (strcmp(tail->next->destination, destination) == 0)count++;
		tail = tail->next;
	}
	if (count == 0)tail->next = newNode;//�p�G�S���X�{�L�h�s�W���`�I
}

int countNode(Node2* list) {
	Node2* tail = list;
	int count = 0;
	while (tail->next) {
		tail = tail->next;
		count++;//�p��`�I
	}
	return count;
}

void printNode(Node* list) {
	while (list->next) {
		printf_s("%10s\t%10s\t%10s\t%10s\n", list->next->flight, list->next->destination, list->next->take_off, list->next->landing);//��X���e
		list = list->next;
	}
}

void printAirLine(Node2* list) {
	while (list->next) {
		printf_s("%10s\n", list->next->destination);//��X���e
		list = list->next;
	}
}

void freeNode(Node* list) {
	for (Node* toDel; list;) {
		toDel = list;
		list = list->next;
		free(toDel);
	}
}

void freeNode2(Node2* list) {
	for (Node2* toDel; list;) {
		toDel = list;
		list = list->next;
		free(toDel);//�k�ٰO����
	}
}

void userSearch(Node* list) {
	char city_name[50];
	printf("\n�п�J�����W:");
	scanf_s("%s", city_name, 50);
	Node* found = list->next;
	while (found) {
		if (strcmp(found->destination, city_name) == 0)printf_s("%10s\t%10s\t%10s", found->flight, found->take_off, found->landing);
		found = found->next;
	}
}

void main(int argc, char** argv) {

	FILE* file = fopen(argv[1], "r");
	char* data_ori = (char*)malloc(sizeof(char) * informationSize);
	char* ptr = NULL;

	char* flight = (char*)malloc(sizeof(char) * informationSize);
	char* destination = (char*)malloc(sizeof(char) * informationSize);
	char* take_off = (char*)malloc(sizeof(char) * informationSize);
	char* landing = (char*)malloc(sizeof(char) * informationSize);

	Node* list = (Node*)malloc(sizeof(Node));
	list->next = NULL;

	Node2* newList = (Node2*)malloc(sizeof(Node2));
	newList->next = NULL;

	/*�r����Ψä��O�x�s�B�[�J�`�I*/
	while (fgets(data_ori, informationSize, file) != NULL) {
		ptr = strtok(data_ori, cut);
		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				strcpy(flight, ptr);
				break;
			case 1:
				strcpy(destination, ptr);
				break;
			case 2:
				strcpy(take_off, ptr);
				break;
			case 3:
				strcpy(landing, ptr);
				break;
			}
			ptr = strtok(NULL, cut);
		}
		add(list, flight, destination, take_off, landing);//�s�W�ñƧǸ`�I
		addAirLine(newList, destination);//�s�W�����Ƹ`�I
	}

	printNode(list);//��X�Ҧ���Z
	printf_s("\n\n\n");
	printAirLine(newList);//��X�����Ư�Z
	printf_s("\n%d\n", countNode(newList));//��X��u�ƶq

	userSearch(list);

	/*�k�ٰO����Ŷ�*/
	fclose(file);
	free(flight);
	free(destination);
	free(take_off);
	free(landing);
	freeNode(list);
	freeNode2(newList);
}