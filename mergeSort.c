#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct Array {
  int* array;
  unsigned long long int arraySize;
} Array;

void printArray(Array* myArray) {
  for (unsigned long long int i = 0; i < myArray->arraySize; i++) printf("%d", myArray->array[i]);
  puts("");
}

void freeArray(Array* myArray) {
  free(myArray->array);
  free(myArray);
}

void checkSort(Array* myArray) {
  for (unsigned long long int i = 1; i < myArray->arraySize; i++) {
    if (myArray->array[i] < myArray->array[i - 1]) {
      printf("Nao ordenado, erro indice %llu\n", i);
      return;
    }
  }
  puts("File sorted");
}

Array* readFile(char* fileName) {
  unsigned long long int arraySize;
  FILE* myFile = fopen(fileName, "r");
  fscanf(myFile, "#Linha#\n%llu#\n", &arraySize);
  Array* myArray = (Array*)malloc(sizeof(Array));
  myArray->arraySize = arraySize;
  myArray->array = (int*)malloc(sizeof(int) * arraySize);
  for (unsigned long long int i = 0; i < arraySize; i++) fscanf(myFile, "%d\n", &(myArray->array[i]));
  return myArray;
}

Array* copyArray(Array* myArray) {
  Array* newArray = (Array*)malloc(sizeof(Array));
  newArray->arraySize = myArray->arraySize;
  newArray->array = (int*)malloc(sizeof(int) * newArray->arraySize);
  memcpy(newArray->array, myArray->array, newArray->arraySize * sizeof(int));
  return newArray;
}

void merge(int* arr, int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;

  int* left = (int*)malloc(sizeof(int) * n1);
  int* right = (int*)malloc(sizeof(int) * n2);

  for (int i = 0; i < n1; i++) left[i] = arr[l + i];
  for (int i = 0; i < n2; i++) right[i] = arr[m + i + 1];

  int i = l, j = 0, k = 0;
  while (j < n1 && k < n2) {
    if (left[j] <= right[k]) {
      arr[i++] = left[j++];
    }
    else {
      arr[i++] = right[k++];
    }
  }

  while (j < n1) arr[i++] = left[j++];
  while (k < n2) arr[i++] = right[k++];

  free(left);
  free(right);
}

void mergeSort(int* arr, int l, int r) {
  if (l >= r) return;
  int m = (l + r) / 2;
  mergeSort(arr, l, m);
  mergeSort(arr, m + 1, r);
  merge(arr, l, m, r);
}



typedef struct threadArgs {
  int* arr;
  int l, m, r;
} ThreadArgs;


void* mergeParallel(void* myArgs) {
  myArgs;
  return NULL;
}

void mergeSortParallel(int* arr, int l, int r) {
  if (l >= r) return;

}




int main(int argc, char const* argv[]) {
  Array* myArray = readFile("entryFile.txt");
  mergeSort(myArray->array, 0, myArray->arraySize - 1);
  checkSort(myArray);
  // printArray(myArray);

  freeArray(myArray);
  return 0;
}
