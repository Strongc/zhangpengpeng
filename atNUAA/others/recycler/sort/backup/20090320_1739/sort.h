/*****************************************************
Zhang Pengpeng (rocflyhi@gmail.com)
  
 from 
Colleage of Information Science and Technology 
Nanjing University of Aeronautics and Astronautics
 
Comment: 
This program comes form my algorithm homework which is modified for linux and GCC.
*****************************************************/


/***********************global variable************************/

int Arr[5000];	/*date array*/
int A[5000];		/*a copy of array to protect original date*/
int numArr;		/*the number of the array*/
double countComp;	/*times of comparison of each sort_Method*/
double compPerSort[5][5000];/*recond numArr*/
double countAver[5];	/*average times of comparison*/


/***********************preparation************************/
void getArr();	/*produce random array*/
void copyArr();	/*copy date to protect original date*/
void statistics(int sortMode);	/*get average sortMode is the sort method*/
void output();	/*print the result*/


/***********************archieve of each sort_algorithm************************/

/**SELECTIONSORT*********sortMode=0**/
void selectionSort(int compCount);
/**INSERTIONSORT*********sortMode=1**/
void insertionSort(int compCount);
/**BOTTOMUPSORT*********sortMode=2**/
void merge(int p,int q,int r);
void bottomupSort(int compCount);
/**MERGESORT*********sortMode=3**/
void mergeSort(int compCount);
void mergesortrec(int low,int high);
/**QUICKSORT**************sortMode=4**/
int split(int low,int high);
void quickSortrec(int low,int high);
void quickSort(int compCount);

/**sort organizing function **********/
int sort();
