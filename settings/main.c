//
//  main.c
//  hello-world
//
//  Created by jeizas on 2016/12/5.
//  Copyright © 2016年 jeizas. All rights reserved.
//

#include<stdio.h>
#include<unistd.h>

long CopyFile(const char* file_1, const char * file_2);

int main(){
    char *conf = "./sd/config";
    char * imgDefult = "./test.jpg";
    char * imgSd = "./sd/test2.jpg";
    FILE *fp;
    char buf[50];
    if((fp=fopen(conf, "a"))==NULL){
        getcwd(buf, sizeof(buf));
        printf("\nCannot open file strike any key exit! %s\n" , buf);
        return 0;
    }
    char str[50] = "\nalltuu-wifi=123456\npassword=123456\n";
    printf("wirte msg:");
    for(int i=0; i<50; i++) {
        fputc(str[i], fp);
        printf("%c", str[i]);
    }
    
    fclose(fp);
    printf("to:&%s\n", conf);
    
    printf("Copy File: %s\n To File: %s\n", imgDefult, imgSd);
    puts("Copying......");
    
    CopyFile(imgDefult, imgSd);
    return 0;
}

long CopyFile(const char* file_1, const char * file_2) {
    FILE *pfRead = fopen(file_1, "rb");// pfRead用作复制源.
    FILE *pfWrite = fopen(file_2, "wb");// pfWrite对应复制出来的新文件.
    if (NULL == pfRead || NULL == pfWrite)
    {
        fclose(pfRead);
        fclose(pfWrite);
        return -1;
    }
    long bytesCount = 0;//统计复制的字节数. long最大可以表示不超过2GB的文件
    
    /* 因为C没有byte类型，所以这里用char替代
     * 貌似对大多数机器来说，char都是 单字节
     */
    int arrLen = 1024;   //这个是缓存数组的元素大小
    char bufArr[arrLen]; //这个是 "缓存", 缓存的字节数是 elementSize * arrLen.
    int copiedLen;      //这个变量用来记录fread函数每一次真正读取的元素数
    int elementSize = sizeof(bufArr[0]);
    do {
        copiedLen = 0;
        
        copiedLen = fread(bufArr, elementSize, arrLen, pfRead);
        fwrite(bufArr, elementSize, copiedLen, pfWrite);
        
        bytesCount += copiedLen * elementSize;
        
    } while(copiedLen == arrLen);
    
    //关闭流.
    fclose(pfRead);
    fclose(pfWrite);
    
    return bytesCount;
}
