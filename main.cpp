#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include <iostream>
#include <math.h>
#include <windows.h>
#include <fstream>
using namespace std;

//��������
BITMAPFILEHEADER strHead;
RGBQUAD strPla[256];//256ɫ��ɫ��
BITMAPINFOHEADER strInfo;

int w,h,bitcount;
unsigned char *pBmpBuf;
unsigned char *qBmpBuf;
bool fig_output(char* ,unsigned char*, int, int, int);

//��ʾλͼ�ļ�ͷ��Ϣ
void showBmpHead(BITMAPFILEHEADER pBmpHead){
    cout<<"λͼ�ļ�ͷ:"<<endl;
    //cout<<"bfType value is "<<hex<<pBmpHead.bfType<<endl;
    cout<<"�ļ���С:"<<pBmpHead.bfSize<<endl;
    //printf("�ļ���С:%d\n",pBmpHead.bfSize);
    cout<<"������_1:"<<pBmpHead.bfReserved1<<endl;
    cout<<"������_2:"<<pBmpHead.bfReserved2<<endl;
    cout<<"ʵ��λͼ���ݵ�ƫ���ֽ���:"<<pBmpHead.bfOffBits<<endl<<endl;
}

void showBmpInforHead(BITMAPINFOHEADER pBmpInforHead){
    cout<<"λͼ��Ϣͷ:"<<endl;
    cout<<"�ṹ��ĳ���:"<<pBmpInforHead.biSize<<endl;
    cout<<"λͼ��:"<<pBmpInforHead.biWidth<<endl;
    cout<<"λͼ��:"<<pBmpInforHead.biHeight<<endl;
    cout<<"biPlanesƽ����:"<<pBmpInforHead.biPlanes<<endl;
    cout<<"biBitCount������ɫλ��:"<<pBmpInforHead.biBitCount<<endl;
    cout<<"ѹ����ʽ:"<<pBmpInforHead.biCompression<<endl;
    cout<<"biSizeImageʵ��λͼ����ռ�õ��ֽ���:"<<pBmpInforHead.biSizeImage<<endl;
    cout<<"X����ֱ���:"<<pBmpInforHead.biXPelsPerMeter<<endl;
    cout<<"Y����ֱ���:"<<pBmpInforHead.biYPelsPerMeter<<endl;
    cout<<"ʹ�õ���ɫ��:"<<pBmpInforHead.biClrUsed<<endl;
    cout<<"��Ҫ��ɫ��:"<<pBmpInforHead.biClrImportant<<endl;
}

tagRGBQUAD* ReadFile(char *strFile){
    FILE *fpi;
    fpi=fopen(strFile,"rb");
    if(fpi!=NULL){
        //�ȶ�ȡ�ļ�����
        WORD bfType;
        fread(&bfType,1,sizeof(WORD),fpi);
        if(0x4d42!=bfType){
            cout<<"the file is not a bmp file!"<<endl;
            return NULL;
        }
        //��ȡbmp�ļ����ļ�ͷ����Ϣͷ
       /* fread(&strHead,sizeof(BITMAPFILEHEADER),1,fpi);
        showBmpHead(strHead);//��ʾ�ļ�ͷ
        fread(&strInfo,sizeof(BITMAPINFOHEADER),1,fpi);
        showBmpInforHead(strInfo);//��ʾ�ļ���Ϣͷ*/
        fseek(fpi, sizeof(BITMAPFILEHEADER),0);//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
        BITMAPINFOHEADER strInfo;
        fread(&strInfo, sizeof(BITMAPINFOHEADER), 1,fpi);
        //��ȡ��ɫ��
        /*
        for(int nCounti=0;nCounti<strInfo.biClrUsed;nCounti++){
            //�洢��ʱ��һ��ȥ��������rgbReserved
            fread((char *)&strPla[nCounti].rgbBlue,1,sizeof(BYTE),fpi);
            fread((char *)&strPla[nCounti].rgbGreen,1,sizeof(BYTE),fpi);
            fread((char *)&strPla[nCounti].rgbRed,1,sizeof(BYTE),fpi);
            cout<<"strPla[nCounti].rgbBlue"<<strPla[nCounti].rgbBlue<<endl;
            cout<<"strPla[nCounti].rgbGreen"<<strPla[nCounti].rgbGreen<<endl;
            cout<<"strPla[nCounti].rgbRed"<<strPla[nCounti].rgbRed<<endl;
        }
        */
         cout<<"����ͼƬ����������:::::"<<endl;
        /*
        //����ͼƬ����������
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
        pBmpBuf=new unsigned char[lineByte * h];//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
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

//RGBתYIQ
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

//RGBתHSI
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

//RGBתXYZ
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

//��ʾͼ��
bool fig_output(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount)
{//���λͼ����ָ��Ϊ0����û�����ݴ��룬��������
	if(!imgBuf)
	 return 0;
	int colorTablesize=0;
	int lineByte=(width * biBitCount/8 + 3)/4 * 4;
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0)
	 return 0;
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp����
	fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;//bfSize��ͼ���ļ�4����ɲ���֮��
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits=54+colorTablesize;//bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��
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
	fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);//дλͼ��Ϣͷ���ڴ�
	fwrite(imgBuf, h*lineByte, 1, fp);//дλͼ���ݽ��ļ�
	fclose(fp);
	return 1;
 }
int main(){
    char strFile[30];//bmp�ļ���
    cout<<"��������Ҫ��ȡ���ļ���:"<<endl;
    cin>>strFile;
    ReadFile(strFile);
    //readBmp("time.bmp");
    ofstream outfile("pixel.txt",ios::in|ios::trunc);
    int lineByte=(w * bitcount/8 + 3)/4 * 4;
    cout<<"biWidth: "<<w<<endl;
    cout<<"biHeight: "<<h<<endl;
    cout<<"lineByte: "<<lineByte<<endl;
    fig_XYZ(pBmpBuf);//�ֱ����RGB��YIQ��HSI��XYZ����
	int m = 0;
    for(int i = 0; i < h; i++) //�����һ������
    {
        for(int j = 0; j < w; j++)
        {
            for(int k=0;k<3;k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
			{
				m=*(pBmpBuf + i * lineByte + j * 3 + k);
				outfile<<m<<" ";
			}
        }
    }
	delete []pBmpBuf;
	delete []qBmpBuf;
}
