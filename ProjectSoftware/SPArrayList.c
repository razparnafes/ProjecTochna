#include "SPArrayList.h"
#include <stdio.h>
#include <stdlib.h>

//ToDo: redeal with all errors - still in HW3 format

SPArrayList* spArrayListCreate(int maxSize){
	//check maxsize valid
	if (maxSize <= 0){
		return NULL;
	}

	//init list struct
	SPArrayList* new_list = (SPArrayList*) calloc(1, sizeof(SPArrayList));
	if (new_list == NULL){
		printf("Error: calloc has failed\n");
		return NULL;
	}

	//init element array
	int* elements = (int*) calloc(maxSize, sizeof(int));
	if (elements == NULL){
		printf("Error: calloc has failed\n");
		return NULL;
	}

	//set list fields
	new_list -> elements = elements;
	new_list -> actualSize = 0;
	new_list -> maxSize = maxSize;

	//init element array to 0's
	for(int i = 0; i < maxSize; i++){
		elements[i] = 0;
	}

	return new_list;
}


SPArrayList* spArrayListCopy(SPArrayList* src){

	//assert src
	if(src == NULL){
		return NULL;
	}

	//init copy
	SPArrayList* copy = spArrayListCreate(src->maxSize);
	if(copy == NULL){
		return NULL;
	}
	copy->actualSize = src->actualSize;

	//copy elements
	for (int i = 0; i < src->actualSize; i++){
		copy->elements[i] = src->elements[i];
	}

	return copy;
}

void spArrayListDestroy(SPArrayList* src){
	if (src != NULL){
		free(src->elements);
		free(src);
	}
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src){
	//check arg
	if (src == NULL){
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}

	//clears elements
	src->actualSize = 0;

	return SP_ARRAY_LIST_SUCCESS;
}


SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index){
	//check args
	if (src == NULL || index > src->actualSize){
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}

	//checks list length
	if (src->actualSize == src->maxSize){
		return SP_ARRAY_LIST_FULL;
	}

	//moves elements forward
	for (int i = src->actualSize; i > index; i--){
		src->elements[i] = src->elements[i-1];
	}

	//inserts elem
	src->elements[index] = elem;
	src->actualSize++;

	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem){
	return spArrayListAddAt(src, elem, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem){
	return spArrayListAddAt(src, elem, src->actualSize);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index){
	//check args
	if(src == NULL || index >= src->actualSize){
		return SP_ARRAY_LIST_INVALID_ARGUMENT;
	}

	//if list empty...
	if(src->actualSize == 0){
		return SP_ARRAY_LIST_EMPTY;
	}

	//move elems back to remove specified elem
	for (int i = index; i < src->actualSize-1; i++){
		src->elements[i] = src->elements[i+1];
	}
	src->actualSize--;

	return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src){
	return spArrayListRemoveAt(src, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src){
	return spArrayListRemoveAt(src, src->actualSize-1);
}

int spArrayListGetAt(SPArrayList* src, int index){
	return src->elements[index];
}

int spArrayListGetFirst(SPArrayList* src){
	return spArrayListGetAt(src, 0);
}

int spArrayListGetLast(SPArrayList* src){
	return spArrayListGetAt(src, src->actualSize-1);
}

int spArrayListMaxCapacity(SPArrayList* src){
	return src->maxSize;
}

int spArrayListSize(SPArrayList* src){
	return src->actualSize;
}

bool spArrayListIsFull(SPArrayList* src){
	//check arg
	if (src == NULL){
		return false;
	}

	//check full
	if (src->actualSize == src->maxSize){
		return true;
	}

	//else:
	return false;
}

bool spArrayListIsEmpty(SPArrayList* src){
	//check arg
	if (src == NULL){
		return false;
	}

	//check full
	if (src->actualSize == 0){
		return true;
	}

	//else:
	return false;
}





