# 107_1_Machine_Learning_and_Practice

開發環境DEV C ++ 4.9.9.2

使用語言C ++



/**********************************程式流程**********************************/



step 0  - 建立樣本（訓練）

  建立大量data_array []亂數座標並以同心圓切分不同TAG

第1步 - 建立預測點 

  建立大量T_array []亂數座標

第2步 - 更新一次對應表

  的foreach（T_array []）

    建立與各點距離

    的foreach（data_array中[]）{

      計算距離並寫入distance_array []

    }

    找出distance_array []內K個最小值//最近座標

    計算最近座標TAG重複最大量

第3步 - 輸出

  //為了區分樣本與預測標籤預測標籤將會追加總標籤數目

  //共有K種標籤預測為A類輸出TAG將顯示A + K.

  以TXT輸出並配合'\ t'貼入Excel儲存格

  並以Excel的內建2D圖表輸出

    

/**********************************使用參數**********************************/



#define DCNT     60000// 資料個數//樣本

#define TCNT     6000 // 資料個數//預測



#define K        9    // 判斷數量



#define DIM      2    // 資料維度(for Excel圖表功能)

#define LOW     -999  // 資料下限

#define UP       999  // 資料上限
