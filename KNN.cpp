#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
// ------------------------------------
#define DCNT     60000// 資料個數//樣本
#define TCNT     6000 // 資料個數//預測
#define K        9    // 判斷數量
#define DIM      2    // 資料維度
#define LOW     -999  // 資料下限
#define UP       999  // 資料上限

using namespace std;

struct DATA_LIST{
    int data[DIM]  ;  // 原始資料
    int table      ;  // 資料所屬叢聚
};

DATA_LIST data_array[DCNT];//樣本資料 
DATA_LIST T_array[TCNT];   //預測資料 

// 計算二點距離
int distance(int *x, int *y, int dim)
{
    int sum=0;
    for(int i=0; i<dim; i++){
        sum = sum+(x[i]-y[i])*(x[i]-y[i]) ;
    }
    return sum;
}

// 更新table
int update_table(DATA_LIST *sample, DATA_LIST objective)
{
    int distance_array[DCNT];//各點距離 
    int k_array[K];//找出最近 標籤
    int F_array[K];//找出重複程度 
    
    for(int i=0;i<DCNT;i++){
        distance_array[i] = distance(sample[i].data,objective.data, DIM);
    }
    
    for(int k=0;k<K;k++){
        int min = distance_array[0];//最小值
        int min_ptr = 0;//最小值位置 
        k_array[k]=sample[min_ptr].table;//紀錄TAG
        F_array[k]=0;//歸零
        
        for(int i=1;i<DCNT;i++){
            if(min>distance_array[i]){
                min       =distance_array[i];
                min_ptr   = i ;
            }
        }
        k_array[k]=sample[min_ptr].table;
        distance_array[min_ptr]=2147483647;
    }
    
    int max = -1;//最大值
    int max_ptr = 0;//最大值位置 
    for(int k=0;k<K;k++){
        for(int j=0;j<K;j++){
            if(k_array[k]==k_array[j]){
                 F_array[k]++;
                 if(F_array[k]>max){
                     max=F_array[k];
                     max_ptr=k;
                 }
            } 
        }
    }
    
    return k_array[max_ptr];
}   
    
    
int main(void)
{ 
    srand((unsigned)time(NULL));    
    // step 0.0 - 建立樣本
    for(int i=0;i<DCNT;i++){
        int sum = 0;
        for(int j=0;j<DIM;j++){
            data_array[i].data[j] = LOW + rand()%(UP-LOW+1);
            sum=sum+data_array[i].data[j]*data_array[i].data[j];
        }
        data_array[i].table=-1;
        if(sum<250*250){
            data_array[i].table=0;
        }
        else if(sum<500*500){
            data_array[i].table=1;
        }
        else if(sum<750*750){
            data_array[i].table=2;
        }
        else {
            data_array[i].table=3;
        }
    }
    // step 1 - 建立預測點 
    for(int i=0;i<TCNT;i++){
        for(int j=0;j<DIM;j++){
            T_array[i].data[j] = LOW + rand()%(UP-LOW+1);
        }
    }
    // step 2 - 更新一次對應表
    for(int i=0;i<TCNT;i++){
        T_array[i].table=4+update_table(data_array,T_array[i]);
    }    
    // 輸出資料 
    
    // 寫入
    printf("\n\n寫入紀錄\n");
    char filename[]="KNN_out.txt";
    fstream fp;
    fp.open(filename, ios::out);//開啟檔案
    
    // 輸出資料 
    fp<<"sample Items";for(int i=0;i<DIM;i++){fp<<"\tX"<<i;}fp<<"\t\tout\t";
        for(int k=0;k<K;k++){
            fp<<"\tlist"<<k;
            for(int j=0;j<DIM;j++){
                fp<<"\t";
            }
        }
    for(int i=0;i<DCNT;i++){
        fp<<"\n"<<i;
        for(int j=0;j<DIM;j++){
            fp<<"\t"<<data_array[i].data[j];
        }
        fp<<"\t==>\t"<<data_array[i].table<<"\t";
        
        
        for(int k=0;k<K;k++){
                    fp<<"\t";
            for(int j=0;j<DIM;j++){
                if(k==data_array[i].table){
                    fp<<"\t"<<data_array[i].data[j];
                }
                else{
                    fp<<"\t";
                }
            }
        }
    }
    
    fp<<"\n\n\n";
    fp<<"objective Items";
    for(int i=0;i<TCNT;i++){
        fp<<"\n"<<i;
        for(int j=0;j<DIM;j++){
            fp<<"\t"<<T_array[i].data[j];
        }
        fp<<"\t==>\t"<<T_array[i].table<<"\t";
        
        
        for(int k=0;k<K;k++){
                    fp<<"\t";
            for(int j=0;j<DIM;j++){
                if(k==T_array[i].table){
                    fp<<"\t"<<T_array[i].data[j];
                }
                else{
                    fp<<"\t";
                }
            }
        }
    }
    
    fp.close();//關閉檔案
    
    system("PAUSE");
    return 0;
}
