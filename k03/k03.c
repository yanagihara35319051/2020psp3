#include <stdio.h>

#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    //  ここを実装する
    int start=0,pos=0;
    int text_len=0,key_len=0;
    while(text[text_len]!='\0'){
        text_len++;
    }
        while(key[key_len]!='\0'){
        key_len++;
    }

    while(start != (text_len - key_len)){
        pos=0;
        while(text[start+pos] == key[pos] && pos<= key_len){
            pos++;
        }
        if(pos==key_len){
            return &text[start];
        }
        start++;
    }

    return NULL;
}

char* BMSearch(char text[], char key[])
{
    //  ここを実装する
    int text_len=0,key_len=0;
    int index,key_index;
    int table[256];
    int i,before_index;

    while(text[text_len]!='\0'){
        text_len++;
    }
    while(key[key_len]!='\0'){
        key_len++;
    }
    for(i=0;i < 256;i++){
        table[i] = key_len;
    }
    for(i=0;i<key_len;i++){
       table[(int)key[i]] = key_len-i-1;
    }

    index = key_len-1;
    before_index = index;

    while(1){
        key_index = key_len-1;

        if(index >= text_len){
           return NULL;
        }

        while(text[index] == key[key_index]){
            index--;
            key_index--;
            if(key_index < 0){
               return &text[index+1];
            }
        }

        index = index + table[(int)text[index]];
        if(index <= before_index){
            index = before_index++;
        }
        before_index = index;
    }
}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}