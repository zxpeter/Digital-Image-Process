#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include <iostream>
#include <math.h>
#include <windows.h>
#include <fstream>
using namespace std;

//变量定义
BITMAPFILEHEADER strHead;
RGBQUAD strPla[256];//256色调色板
BITMAPINFOHEADER strInfo;

int w,h,bitcount;
unsigned char *pBmpBuf;
unsigned char *qBmpBuf;
bool fig_output(char* ,unsigned char*, int, int, int);

//显示位图文件头信息
void showBmpHead(BITMAPFILEHEADER pBmpHead){
    cout<<"位图文件头:"<<endl;
    //cout<<"bfType value is "<<hex<<pBmpHead.bfType<<endl;
    cout<<"文件大小:"<<pBmpHead.bfSize<<endl;
    //printf("文件大小:%d\n",pBmpHead.bfSize);
    cout<<"保留字_1:"<<pBmpHead.bfReserved1<<endl;
    cout<<"保留字_2:"<<pBmpHead.bfReserved2<<endl;
    cout<<"实际位图数据的偏移字节数:"<<pBmpHead.bfOffBits<<endl<<endl;
}

void showBmpInforHead(BITMAPINFOHEADER pBmpInforHead){
    cout<<"位图信息头:"<<endl;
    cout<<"结构体的长度:"<<pBmpInforHead.biSize<<endl;
    cout<<"位图宽:"<<pBmpInforHead.biWidth<<endl;
    cout<<"位图高:"<<pBmpInforHead.biHeight<<endl;
    cout<<"biPlanes平面数:"<<pBmpInforHead.biPlanes<<endl;
    cout<<"biBitCount采用颜色位数:"<<pBmpInforHead.biBitCount<<endl;
    cout<<"压缩方式:"<<pBmpInforHead.biCompression<<endl;
    cout<<"biSizeImage实际位图数据占用的字节数:"<<pBmpInforHead.biSizeImage<<endl;
    cout<<"X方向分辨率:"<<pBmpInforHead.biXPelsPerMeter<<endl;
    cout<<"Y方向分辨率:"<<pBmpInforHead.biYPelsPerMeter<<endl;
    cout<<"使用的颜色数:"<<pBmpInforHead.biClrUsed<<endl;
    cout<<"重要颜色数:"<<pBmpInforHead.biClrImportant<<endl;
}

tagRGBQUAD* ReadFile(char *strFile){
    FILE *fpi;
    fpi=fopen(strFile,"rb");
    if(fpi!=NULL){
        //先读取文件类型
        WORD bfType;
        fread(&bfType,1,sizeof(WORD),fpi);
        if(0x4d42!=bfType){
            cout<<"the file is not a bmp file!"<<endl;
            return NULL;
        }
        //读取bmp文件的文件头和信息头
       /* fread(&strHead,sizeof(BITMAPFILEHEADER),1,fpi);
        showBmpHead(strHead);//显示文件头
        fread(&strInfo,sizeof(BITMAPINFOHEADER),1,fpi);
        showBmpInforHead(strInfo);//显示文件信息头*/
        fseek(fpi, sizeof(BITMAPFILEHEADER),0);//跳过位图文件头结构BITMAPFILEHEADER
        BITMAPINFOHEADER strInfo;
        fread(&strInfo, sizeof(BITMAPINFOHEADER), 1,fpi);
        //读取调色板
        /*
        for(int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++){
            //存储的时候，一般去掉保留字rgbReserved
            fread((char *)&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpi);
            fread((char *)&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpi);
            fread((char *)&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpi);
            cout<<"strPla[nCounti].rgbBlue"<<strPla[nCounti].rgbBlue<<endl;
            cout<<"strPla[nCounti].rgbGreen"<<strPla[nCounti].rgbGreen<<endl;
            cout<<"strPla[nCounti].rgbRed"<<strPla[nCounti].rgbRed<<endl;
        }
        */
         cout<<"读出图片的像素数据:::::"<<endl;
        /*
        //读出图片的像素数据
        memset(imagedata,0,sizeof(IMAGEDATA) * 256 * 256);
        //fseek(fpi,54,SEEK_SET);
        fread(imagedata,sizeof(struct tagIMAGEDATA) * strInfo.biWidth,strInfo.biHeight,fpi);
        */
        w = strInfo.biWidth;
        h = strInfo.biWidth;
        bitcount = strInfo.biBitCount;
        int lineByte=(w * bitcount/8 + 3)/4 * 4;
        cout<<"biWidth: "<<strInfo.biWidth<<endl;
        cout<<"biHeight: "<<strInfo.biHeight<<endl;
        pBmpBuf=new unsigned char[lineByte * h];//申请位图数据所需要的空间，读位图数据进内存
        qBmpBuf=new unsigned char[lineByte * h];
        fread(pBmpBuf,1,lineByte * h,fpi);
        fclose(fpi);
    }
    else{
        cout<<"file open error!"<<endl;
        return NULL;
    }
}

//RGB
void fig_RGB(unsigned char *p )
{
	int sum,i;
	sum = w * h;
	int t;
	for(i = 0;i < 3 * sum;i++)
	{
		//qBmpBuf[i] = p[i+2];	//B
		qBmpBuf[i] = 0;
		i++;
		//qBmpBuf[i] = p[i];    //G
		qBmpBuf[i] = 0;    //G
		i++;
		qBmpBuf[i] = p[i-2];    //R
		//qBmpBuf[i] = 0;    //R

	}
    fig_output("RGB.BMP",qBmpBuf , w, h, bitcount);
}

//RGB转YIQ
void fig_YIQ(unsigned char *p )
{
	int sum,i;
	sum = w * h ;
	int t;
	for(i = 0;i < 3 * sum;i++)
	{
		//qBmpBuf[i] = 0.299 * p[i+2] + 0.587 * p[i+1] + 0.114 * p[i];	//Y
		//qBmpBuf[i] = 0.596 * p[i+1] - 0.274 * p[i] - 0.322 * p[i-1];    //I
		qBmpBuf[i] = 0.211 * p[i] - 0.523 * p[i-1] + 0.312 * p[i-2];    //Q
		t = qBmpBuf[i];
		i++;
		//qBmpBuf[i] = 0.596 * p[i+1] - 0.274 * p[i] - 0.322 * p[i-1];    //I
		qBmpBuf[i] = t;
		i++;
		//qBmpBuf[i] = 0.211 * p[i] - 0.523 * p[i-1] + 0.312 * p[i-2];    //Q
		qBmpBuf[i] = t;
	}
    fig_output("YIQ.BMP",qBmpBuf , w, h, bitcount);
}

//RGB转HSI
void fig_HSI(unsigned char *p)
{
	int sum,i;
	sum = w * h ;
	int t;
	for(i = 0;i < 3 * sum;i++)
	{
		//qBmpBuf[i] = (p[i+2] + p[i+1] + p[i])/3 ;		//H
		//qBmpBuf[i] = 1 - 3.0 * min(p[i+1], min(p[i], p[i-1]))/(p[i+1] + p[i] + p[i-1]);
        double k = acos((p[i] * 2 - p[i-1] - p[i-2])/(2 * sqrt((p[i] - p[i-1]) * (p[i] - p[i-1]) + (p[i] - p[i-2]) * (p[i-1] - p[i-1])))) * 255/6.28;
		if(p[i-2]>p[i-1])
			k = 255 - k;
		qBmpBuf[i] = k;   //I
        t = qBmpBuf[i];
		i++;
		//qBmpBuf[i] = 1 - 3.0 * min(p[i+1], min(p[i], p[i-1]))/(p[i+1] + p[i] + p[i-1]);   //S
        qBmpBuf[i] = t;
		i++;
		//double k = acos((p[i] * 2 - p[i-1] - p[i-2])/(2 * sqrt((p[i] - p[i-1]) * (p[i] - p[i-1]) + (p[i] - p[i-2]) * (p[i-1] - p[i-1])))) * 255/6.28;
		//if(p[i-2]>p[i-1])
			//k = 255 - k;
		//qBmpBuf[i] = k;   //I
        qBmpBuf[i] = t;
	}
    fig_output("HSI.BMP",qBmpBuf,w,h ,bitcount);

}

//RGB转XYZ
void fig_XYZ(unsigned char *p)
{
	int sum,i;
	sum = w * h ;
	int t;
	for(i = 0;i < 3 * sum;i++)
	{
		//qBmpBuf[i] = 0.490 * p[i+2] + 0.310 * p[i+1] + 0.200 * p[i];		//X
		//qBmpBuf[i] = 0.177 * p[i+1] + 0.813 * p[i] + 0.011 * p[i-1];   //Y
		qBmpBuf[i] = 0.000 * p[i] + 0.010 * p[i-1] + 0.990 * p[i-2];    //Z
        t = qBmpBuf[i];
		i++;
	    //qBmpBuf[i] = 0.177 * p[i+1] + 0.813 * p[i] + 0.011 * p[i-1];   //Y
        qBmpBuf[i] = t;
		i++;
		//qBmpBuf[i] = 0.000 * p[i] + 0.010 * p[i-1] + 0.990 * p[i-2];    //Z
        qBmpBuf[i] = t;
	}
    fig_output("XYZ.BMP",qBmpBuf , w, h, bitcount);
}

//显示图像
bool fig_output(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount)
{//如果位图数据指针为0，则没有数据传入，函数返回
	if(!imgBuf)
	 return 0;
	int colorTablesize=0;
	int lineByte=(width * biBitCount/8 + 3)/4 * 4;
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0)
	 return 0;
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型
	fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;//bfSize是图像文件4个组成部分之和
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits=54+colorTablesize;//bfOffBits是图像文件前3个部分所需空间之和
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
	BITMAPINFOHEADER head;
	head.biBitCount=biBitCount;
	head.biClrImportant=0;
	head.biClrUsed=0;
	head.biCompression=0;
	head.biHeight=height;
	head.biPlanes=1;
	head.biSize=40;
	head.biSizeImage=lineByte*height;
	head.biWidth=width;
	head.biXPelsPerMeter=0;
	head.biYPelsPerMeter=0;
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);//写位图信息头进内存
	fwrite(imgBuf, h*lineByte, 1, fp);//写位图数据进文件
	fclose(fp);
	return 1;
 }
int main(){
    char strFile[30];//bmp文件名
    cout<<"请输入所要读取的文件名:"<<endl;
    cin>>strFile;
    ReadFile(strFile);
    //readBmp("time.bmp");
    ofstream outfile("pixel.txt",ios::in|ios::trunc);
    int lineByte=(w * bitcount/8 + 3)/4 * 4;
    cout<<"biWidth: "<<w<<endl;
    cout<<"biHeight: "<<h<<endl;
    cout<<"lineByte: "<<lineByte<<endl;
    fig_XYZ(pBmpBuf);//分别调用RGB，YIQ，HSI，XYZ函数
	int m = 0;
    for(int i = 0; i < h; i++) //输出第一行数据
    {
        for(int j = 0; j < w; j++)
        {
            for(int k=0;k<3;k++)//每像素RGB三个分量分别置0才变成黑色
			{
				m=*(pBmpBuf + i * lineByte + j * 3 + k);
				outfile<<m<<" ";
			}
        }
    }
	delete []pBmpBuf;
	delete []qBmpBuf;
}
