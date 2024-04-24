#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstring>

int* newArray(int*, int);// 生成随机数组
void showArray(int*, int);// 打印数组
void swap(int*, int*);// 交换
void recordShortTime(void (*)(int*, int), int*, int);// 计算时间
void recordLongTime(void (*)(int*, int), int*, int);// 计算时间
void checkArray(int*, int);// 检查排序
void bubbleSort(int*, int);// 冒泡排序
void selectSort(int*, int);// 选择排序
void insertSort(int*, int);// 插入排序
void shellSort(int*, int);// 希尔排序
void shellInsert(int*, int, int);  
void quickSort(int*, int);// 快速排序
void quickSort(int*, int, int);
void mergeSort(int*, int);// 归并排序
void mergeSort(int*, int, int);
void merge(int*, int, int, int);
void heapSort(int*, int);// 堆排序
void buildHeap(int*, int, int);
void countSort(int*, int);// 计数排序
void radixSort(int*, int);// 基数排序

int main()
{
    srand(1);
    int *array;
    int size = 100000;
    array = newArray(array, size);
    printf("bubbleSort:\n");
    recordLongTime(bubbleSort, array, size);
    printf("selectSort:\n");
    recordLongTime(selectSort, array, size);
    printf("insertSort:\n");
    recordLongTime(insertSort, array, size);
    printf("shellSort:\n");
    recordLongTime(shellSort, array, size);
    printf("quickSort:\n");
    recordLongTime(quickSort, array, size);
    printf("mergeSort:\n");
    recordLongTime(mergeSort, array, size);
    printf("heapSort:\n");
    recordLongTime(heapSort, array, size);
    printf("countSort:\n");
    recordLongTime(countSort, array, size);
    printf("radixSort:\n");
    recordLongTime(radixSort, array, size);
}

// 生成大小为 size 的随机数组
int* newArray(int* array, int size) {
    array = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size;
    }
    //showArray(array, size);
    return array;
}

// 交换元素
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 打印数组
void showArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\t", array[i]);
    }
    printf("\n");
}

// 记录每个排序算法运行时间, 适用于大数据
void recordLongTime(void (*func)(int* funcArray, int funcSize), int* array, int size) {
    clock_t begin = clock();
    func(array, size);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("lasting %f seconds.\n", time_spent);
}

// 记录每个排序算法运行时间, 适用于小数据
void recordShortTime(void (*func)(int* funcArray, int funcSize), int* array, int size) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    func(array, size);
    clock_gettime(CLOCK_REALTIME, &end);
    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("lasting %f seconds.\n", time_spent);
}

// 检查排序是否正确
void checkArray(int* array, int size) {
    int flag = 1;
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            flag = 0;
            break;
        }
    }
    if (flag)
        printf("Sort successfully!!\n");
    else
        printf("Sort failed!!\n");
}

// 冒泡排序
void bubbleSort(int * array, int size) {
    int temp;
    int* sortArray = (int*)malloc(size * sizeof(int));
    memcpy(sortArray, array, size * sizeof(int));
    
    for (int i = 0; i < size -1; i++) {
        for (int j = 0; j < size -i - 1; j++) {
            if (sortArray[j] > sortArray[j + 1]) {
                swap(&sortArray[j], &sortArray[j + 1]);
            }
        }
    }
    
    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

// 选择排序
void selectSort(int* array, int size) {
    int min;
    int* sortArray = (int*)malloc(size * sizeof(int));
    memcpy(sortArray, array, size * sizeof(int));
    
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i; j < size; j++){
            if (sortArray[j] < sortArray[min])
                min = j;            
        }
        if (min != i){
            swap(&sortArray[i], &sortArray[min]);
        }
    }
    
    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

// 插入排序
void insertSort(int* array, int size) {
    int temp;
    int* sortArray = (int*)malloc(size * sizeof(int));
    memcpy(sortArray, array, size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        for (int j = i; j > 0; j--) {
            if (sortArray[j] < sortArray[j - 1])
                swap(&sortArray[j], &sortArray[j - 1]);
        }
    
    }
    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

// 希尔排序
void shellSort(int* array, int size) {
    int* sortArray = (int*)malloc(size * sizeof(int));
    memcpy(sortArray, array, size * sizeof(int));
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            shellInsert(sortArray, i - gap, i);
        }
    }
    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

// 希尔排序的插入排序
void shellInsert(int* array, int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int min = array[i];
        int j = i - 1;
        while (i >= start && array[j] > min) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = min;
    }
}

// 快速排序
void quickSort(int* array, int size) {
    int* sortArray = (int*)malloc(size * sizeof(int));
    memcpy(sortArray, array, size * sizeof(int));
    int low = 0;
    int high = size - 1;
    quickSort(sortArray, low, high);
    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

// 快速排序的具体递归实现
void quickSort(int* array, int low, int high) {
    int i = low;
    int j = high;
    int temp = array[i];
    
    if (i >= j)
        return;
    
    while (i != j) {
        while (i != j) {
            while (i < j && array[j] >= temp)
                j--;
            while (i < j && array[i] <= temp)
                i++;
            if (i < j)
                swap(&array[i], &array[j]);
        }
    }
    swap(&array[i], &array[low]);
    
    quickSort(array, i + 1, high);
    quickSort(array, low, i - 1);
}

// 归并排序
void mergeSort(int* array, int size) {
    int* sortArray = (int*)malloc(size * sizeof(int));
    memcpy(sortArray, array, size * sizeof(int));
    int left = 0;
    int right = size - 1;
    mergeSort(sortArray, left, right);
    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

// 分
void mergeSort(int* array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

// 治
void merge(int* array, int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;
    int* leftArray = (int*)malloc(len1 * sizeof(int));
    int* rightArray = (int*)malloc(len2 * sizeof(int));
    // for (int i = 0; i < len1; i++)
    //     leftArray[i] = array[left + i];
    // for (int j = 0; j < len2; j++)
    //     rightArray[j] = array[mid + 1 + j];
    memcpy(leftArray, array + left, len1 * sizeof(int));
    memcpy(rightArray, array + mid + 1, len2 * sizeof(int));
    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while (i < len1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < len2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
    free(leftArray);
    free(rightArray);
}

// 堆排序
void heapSort(int* array, int size) {
    int* sortArray = (int*)malloc(size * sizeof(int));
    memcpy(sortArray, array, size * sizeof(int));

    for (int i = size / 2 - 1; i >= 0; i--) 
        buildHeap(sortArray, size, i);
    
    for (int i = size - 1; i > 0; i--) {
        swap(&sortArray[0], &sortArray[i]);
        buildHeap(sortArray, i, 0);
    }
    
    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

void buildHeap(int* array, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && array[left] > array[largest])
        largest = left;
    if (right < size && array[right] > array[largest])
        largest = right;
    if (largest != i) {
        swap(&array[i], &array[largest]);
        buildHeap(array, size, largest);
    }
}

// 计数排序
void countSort(int* array, int size) {
    int* sortArray = (int*)malloc(size * sizeof(int));
    int max = *array, min = *array;
    
    for (int i = 1; i < size; i++) {
        if (array[i] > max)
            max = array[i];
        else if (array[i] < min)
            min = array[i];
    }

    int range = max - min + 1;
    int* count = (int*)calloc(range, sizeof(int));
    for (int i = 0; i < size; i++) {
        count[array[i]-min]++;
    }

    int k = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            sortArray[k++] = i + min;
            count[i]--;
        }
    }

    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

// 基数排序的计数排序
void countSort(int* array, int size, int exp) {
    int* newArray = (int*)malloc(size * sizeof(int));
    int* count = (int*)calloc(10, sizeof(int));

    for (int i = 0; i < size; i++) 
        count[array[i] / exp % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--) {
        newArray[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }
    memcpy(array, newArray, size * sizeof(int));
    
    free(count);
    free(newArray);
}

// 基数排序
void radixSort(int* array, int size) {
    int* sortArray = (int*)malloc(size * sizeof(int));
    memcpy(sortArray, array, size * sizeof(int));

    int max = *sortArray;
    for (int i = 0; i < size; i++) {
        if (sortArray[i] > max) {
            max = sortArray[i];
        }
    }
    for (int exp = 1; max / exp > 0; exp *= 10) 
        countSort(sortArray, size, exp);
    
    //showArray(sortArray, size);
    checkArray(sortArray, size);
    free(sortArray);
}

