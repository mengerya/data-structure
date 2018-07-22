//左闭右闭区间
void QuickSort_temp1(int * start,int * last){
	if (last <= start)
		return;
	int *begin = start;
	int *end = last;
	int key = *last;
	while (end > begin){
		if (*begin < key)
			begin++;
		if (*end>key)
			end--;
		swap(*begin, *end);
	}
	swap(*begin, key);
	QuickSort_temp1(start, begin-1);
	QuickSort_temp1(begin+1, last);
}

void QuickSort_temp2(int * start, int * last){
	//挖坑法
	if (last <= start)
		return;
	int *blank_space = last;
	int *begin = start;
	int *end = last;
	int key = *last;
	while (begin < end){
		if (*begin>key){
			*blank_space = *begin;
			blank_space = begin;
			end--;
		}
		if (*end < key){
			*blank_space = *end;
			blank_space = end;
			begin++;
		}
		begin++;
		end--;
	}
	*blank_space = key;
	QuickSort_temp2(start, begin);
	QuickSort_temp2(begin+1, last);
}
/*
void QuickSort_temp3(int arr[], int size){

}
*/
void Print(int arr[],int size){
	for (size_t i = 0; i < size; i++){
		cout << arr[i] << "  ";
	}
	cout << endl;
}

int main(){
	int arr[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	int size = sizeof(arr) / sizeof(arr[0]);
	Print(arr, size);
	QuickSort_temp2(arr, arr + size - 1);
	cout << "QuickSort_temp2:" << endl;
	Print(arr, size);

	return 0;
}
