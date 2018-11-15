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
#define DCNT     60000// ��ƭӼ�//�˥�
#define TCNT     6000 // ��ƭӼ�//�w��
#define K        9    // �P�_�ƶq
#define DIM      2    // ��ƺ���
#define LOW     -999  // ��ƤU��
#define UP       999  // ��ƤW��

using namespace std;

struct DATA_LIST{
    int data[DIM]  ;  // ��l���
    int table      ;  // ��Ʃ����O�E
};

DATA_LIST data_array[DCNT];//�˥���� 
DATA_LIST T_array[TCNT];   //�w����� 

// �p��G�I�Z��
int distance(int *x, int *y, int dim)
{
    int sum=0;
    for(int i=0; i<dim; i++){
        sum = sum+(x[i]-y[i])*(x[i]-y[i]) ;
    }
    return sum;
}

// ��stable
int update_table(DATA_LIST *sample, DATA_LIST objective)
{
    int distance_array[DCNT];//�U�I�Z�� 
    int k_array[K];//��X�̪� ����
    int F_array[K];//��X���Ƶ{�� 
    
    for(int i=0;i<DCNT;i++){
        distance_array[i] = distance(sample[i].data,objective.data, DIM);
    }
    
    for(int k=0;k<K;k++){
        int min = distance_array[0];//�̤p��
        int min_ptr = 0;//�̤p�Ȧ�m 
        k_array[k]=sample[min_ptr].table;//����TAG
        F_array[k]=0;//�k�s
        
        for(int i=1;i<DCNT;i++){
            if(min>distance_array[i]){
                min       =distance_array[i];
                min_ptr   = i ;
            }
        }
        k_array[k]=sample[min_ptr].table;
        distance_array[min_ptr]=2147483647;
    }
    
    int max = -1;//�̤j��
    int max_ptr = 0;//�̤j�Ȧ�m 
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
    // step 0.0 - �إ߼˥�
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
    // step 1 - �إ߹w���I 
    for(int i=0;i<TCNT;i++){
        for(int j=0;j<DIM;j++){
            T_array[i].data[j] = LOW + rand()%(UP-LOW+1);
        }
    }
    // step 2 - ��s�@��������
    for(int i=0;i<TCNT;i++){
        T_array[i].table=4+update_table(data_array,T_array[i]);
    }    
    // ��X��� 
    
    // �g�J
    printf("\n\n�g�J����\n");
    char filename[]="KNN_out.txt";
    fstream fp;
    fp.open(filename, ios::out);//�}���ɮ�
    
    // ��X��� 
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
    
    fp.close();//�����ɮ�
    
    system("PAUSE");
    return 0;
}
