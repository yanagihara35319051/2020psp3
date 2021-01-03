#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int id;
    char name[19];  //  市の名前、UTF-8対応
    float members;  //  世帯人員
    int total;      //  食料合計
    int grain;      //  穀類
    int seafood;    //  魚介類
    int meat;       //  肉類
    int milk;       //  乳卵類
    int vegetable;  //  野菜類
    int fruit;      //  果物
    int seasoning;  //  調味料
    int snack;      //  菓子類
    int cocking;    //  調理料理
    int drink;      //  飲料
    int liquor;     //  酒類
    int eatout;     //  外食
} City;

#define DEBUG
#define MAX_CITY    47


void PrintCity(City city)
{
    printf("%d, %s, %.2f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", 
        city.id, city.name, city.members, city.total, 
        city.grain, city.seafood, city.meat, city.milk, city.vegetable, city.fruit,
        city.seasoning, city.snack, city.cocking, city.drink, city.liquor, city.eatout);
}

void PrintArray(City city[], int size)
{
    int i;

    for (i=0; i<size; i++) {
        PrintCity(city[i]);
    }
}

int LoadData(City arrayCity[])
{
    char buf[256];
    FILE* fp;

    fp = fopen("consumption.csv","r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        return -1;
    }

    int cn = 0; // 市の数
    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%d,%[^,],%f,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
            &(arrayCity[cn].id), arrayCity[cn].name, &(arrayCity[cn].members), &(arrayCity[cn].total), 
            &(arrayCity[cn].grain),  &(arrayCity[cn].seafood),  &(arrayCity[cn].meat), &(arrayCity[cn].milk), 
            &(arrayCity[cn].vegetable),  &(arrayCity[cn].fruit),  &(arrayCity[cn].seasoning),  &(arrayCity[cn].snack),
            &(arrayCity[cn].cocking),  &(arrayCity[cn].drink),  &(arrayCity[cn].liquor),  &(arrayCity[cn].eatout));
#ifdef DEBUG
        PrintCity(arrayCity[cn]);
#endif
        cn++;
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        return -1;
    }

    return cn;
}


void BubbleSort(City arrayCity[], int size)
{
    //  ここを実装する
    int cnt,pos;
    int i;
    City tmp;

    while(cnt != 0){
        cnt = 0;
        for(pos=0;pos<size - 1;pos++){
           if(arrayCity[pos].total > arrayCity[pos+1].total){
               tmp = arrayCity[pos];
               arrayCity[pos] = arrayCity[pos+1];
               arrayCity[pos+1] = tmp;
               cnt++;
           }
        }
    }
    return;
}


void QuickSort(City arrayCity[], int left, int right)
{
    //  ここを実装する
    
    int pivot;
    int i,j;
    City tmp;
    pivot = arrayCity[left].seafood;
    i = left;
    j = right;

    if(left == right){
        return;
    }
    
    else{
        while(i <= j){
            if(pivot < arrayCity[i].seafood){
                while(i <= j){
                    if(pivot > arrayCity[j].seafood){
                        tmp = arrayCity[j];
                        arrayCity[j] = arrayCity[i];
                        arrayCity[i] = tmp;
                        break; 
                    }
                    j--;
                }
            }
            i++;
        }

        if(i > right && j == right){
            tmp = arrayCity[right];
            arrayCity[right] = arrayCity[left];
            arrayCity[left] = tmp;
            QuickSort(arrayCity,left,right-1);
            QuickSort(arrayCity,right,right);
        
        }
        else if(j <= left){
            QuickSort(arrayCity,left,left);
            QuickSort(arrayCity,left+1,right);
        }
        else{
            tmp=arrayCity[left];
            arrayCity[left] = arrayCity[j];
            arrayCity[j] = tmp;
            QuickSort(arrayCity,left,j-1);
            QuickSort(arrayCity,j+1,right);
        }
    }
}

void ParticalHeap(City arrayCity[],int size,int index){
    int left_node,right_node,last_node,new_node;
    City tmp;

    left_node = 2*index + 1;
    right_node = 2*index + 2;
    last_node = size/2-1;

    if(right_node >= size){
        right_node = left_node;
    }


    if((arrayCity[index].meat < arrayCity[left_node].meat && arrayCity[index].meat < arrayCity[right_node].meat) || index > last_node){
        return;
    }
    else{
        if(arrayCity[left_node].meat <= arrayCity[right_node].meat){
            new_node = left_node;
            tmp = arrayCity[left_node];
            arrayCity[left_node] = arrayCity[index];
            arrayCity[index] = tmp;
        }
        else{
            new_node = right_node;
            tmp = arrayCity[right_node];
            arrayCity[right_node] = arrayCity[index];
            arrayCity[index] = tmp;
        }
        ParticalHeap(arrayCity,size,new_node);
    }
}
void BuildHeap(City arrayCity[],int size){
    int last_node,i;

    last_node = size/2-1;

    for(i = last_node;i >= 0;i--){
        ParticalHeap(arrayCity,size,i);
    }

    return;
}
void HeapSort(City arrayCity[], int size)
{
    //  チャレンジ問題(1)
    int i;
    City tmp;
    BuildHeap(arrayCity,size);

    for(i = size ; i > 1;i--){
        tmp = arrayCity[i-1];
        arrayCity[i-1] = arrayCity[0];
        arrayCity[0] = tmp;
        BuildHeap(arrayCity,i-1);
    }

    return;
    //  ここを実装する

}


void MergeSort(City arrayCity[], int left, int right)
{
    //  チャレンジ問題2
    int mid,i,j,k;

    if(left < right){

      mid = left+(right-left)/2;
      MergeSort(arrayCity,left,mid);
      MergeSort(arrayCity,mid+1,right);



      City left_buff[mid-left+1],right_buff[right-mid];

      for(i=0;i<mid-left+1;i++){
        left_buff[i] = arrayCity[left+i];
      }
      
      for(i=0;i<right-mid;i++){
        right_buff[i] = arrayCity[mid+1+i];
      }

      i = 0;
      j = 0;
      k = left;

      while(k <= right){
         if(i<(mid - left+1) && j < (right - mid)){
            if(left_buff[i].liquor <= right_buff[j].liquor){
              arrayCity[k] = left_buff[i];
              i++; 
              k++;
            }
            else{
              arrayCity[k] = right_buff[j];
              j++;  
              k++;
            }
         }
         else{
            if(i >= mid - left+1){
              arrayCity[k] = right_buff[j];
              j++;
              k++;
            }
            else if(j >= right - mid){
              arrayCity[k] = left_buff[i];
              i++;
              k++;
            }
         }
        }

      return;
    } 

    else{
        return;
    }   



    //  ここを実装する

}

int main(void)
{
 
    //  事前準備。データの読み込み、配列の作成
    City* arrayCity;
    int cn;
    arrayCity = (City*)malloc(sizeof(City) * MAX_CITY);
    cn = LoadData(arrayCity);
    if (cn == -1) {
        exit(EXIT_FAILURE);
    }

    //  食料品合計で並び替え
    printf("===== Sorted by total =====\n");
    BubbleSort(arrayCity, MAX_CITY);
    PrintArray(arrayCity, MAX_CITY);

    //  魚介類で並び替え   
    printf("===== Sorted by seafood =====\n");
    QuickSort(arrayCity, 0, MAX_CITY - 1);
    PrintArray(arrayCity, MAX_CITY);
    printf("\n");

    printf("===== Sorted by liquor =====\n");
    MergeSort(arrayCity, 0, MAX_CITY - 1);
    PrintArray(arrayCity, MAX_CITY);
    printf("\n");
    
    printf("===== Sorted by meat =====\n");
    HeapSort(arrayCity, MAX_CITY);
    PrintArray(arrayCity, MAX_CITY);


    //  後処理
    free(arrayCity);

    return 0;
}