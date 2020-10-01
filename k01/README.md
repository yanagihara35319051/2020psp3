# 課題1 レポート
学籍番号　氏名


## 課題
長崎県にある市町村別人口データを読み込み、IDを用いて検索し、該当する市町村名、人口を出力するプログラムを作成する。

1. 使用するデータ
長崎県の人口データは、nagasaki.csvに保存されている。
nagasaki.csvには、csv形式で以下のデータが含まれる
    - ID
    - 県名
    - 市町村名
    - 人口
    - 男性人口
    - 女性人口

    長崎県の市町村別人口データは、下記に構造体の配列に読み込まれる。

```C: 市町村別データ構造体
typedef struct {  
    int id;  
    char pref[13];  // UTF-8対応  
    char name[19];  // UTF-8対応  
    int population;  
    int m_population;  
    int f_population;  
} City;  
```



2. 必須問題：実装する関数  
本課題では、以下の関数を実装する。  
   (1) LinearSearch：IDをキーとし、リニアサーチで市町村を検索する。  
    [入力]
    - int key: 検索する市町村のID
    - City arrayCity: 検索対象の都市別人口データ(配列)
    - int size: データの数  

    [出力]  
    - return値: IDが合致した配列データのindex。IDが一致するデータがない場合は-1。

    (2) BinarySearch: IDをキーとし、バイナリサーチで市町村を検索する。  
    [入力]
    - int key: 検索する市町村のID
    - City arrayCity: 検索対象の都市別人口データ(配列)
    - int left: バイナリサーチを行う配列のindex(左端)
    - int right: バイナリサーチを行う配列のindex(右端)  

    [出力]  
    - return値: IDが合致した配列データのindex。IDが一致するデータがない場合は-1。


3. 補助関数
以下の関数はすでに実装されており、利用することができる。  
- PrintCity: 特定の市町村別人口データを出力する  
- PrintArray: 市町村別人口データをすべて出力する  
- LoadData: 市町村別人口データを読み込み、City型の配列に格納する  
- main: メイン関数。データをロードし、リニアサーチ、バイナリサーチを呼び出す  


## ソースコードの説明
69～71:配列の0番目から順に、配列に入っているIDと探しているIDと照らし合わせる。見つかった場合、配列のインデックスを返す。探しているIDがなかった場合、-1を返す

83～84:leftに0、rightにMAX_CITYを代入
87:配列の真ん中の添え字をmidに格納
88～90:配列mid番目のIDがkeyと同じ場合、midを返値として返す
91～93：keyが配列のmid1番目より小さかった場合、rightにmid-1を格納する。つまり、配列をmidよりも左側の配列に分割する。
94～97:keyが配列のmid1番目より大きかった場合、leftにmid+1を格納する。つまり、配列をmidよりも右側の配列に分割する。
101:配列にkeyがなかった場合、返値で-1を返す。



## 出力結果

```
見つかる場合
===== linear search =====
City ID?42213
42213, 長崎県, 雲仙市, 44115, 20847, 23268

===== binary search =====
City ID?42321
42321, 長崎県, 東彼杵町, 8298, 3886, 


見つからない場合
===== linear search =====
City ID?42348
city was not found

===== binary search =====
City ID?42348
city was not found
```

## 修正履歴

