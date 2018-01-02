clear;
close all;
clc;

img=imread('time.bmp');
%img=mat2gray(img);  %��������ӳ�䵽[0,1];
[m n dim]=size(img);
% imshow(img);
%%ͼ���RGB
img2=double(img);
R=img2(:,:,1);
G=img2(:,:,2);
B=img2(:,:,3);

%%RGB2YCbCr
Y=zeros(m,n);    %����
Cb=zeros(m,n);   %�ʶ�
Cr=zeros(m,n);   %Ũ��
matrix=[0.299 0.587 0.114;
        -0.1687 -0.3313 0.5;
        0.5 -0.4187 -0.0813];
for i=1:m
   for j=1:n 
        tmp=matrix*[R(i,j) G(i,j) B(i,j)]';
        Y(i,j)=tmp(1);
        Cb(i,j)=tmp(2)+128;
        Cr(i,j)=tmp(3)+128;
   end
end

%%YCbCr2RGB
matrix=inv(matrix);
for i=1:m
   for j=1:n 
        tmp=matrix*[Y(i,j) Cb(i,j)-128 Cr(i,j)-128]';
        R(i,j)=tmp(1);
        G(i,j)=tmp(2);
        B(i,j)=tmp(3);
   end
end

%%��������任��û��Ļ�����ôͼ���ǲ����
% img(:,:,1)=R;
% img(:,:,2)=G;
% img(:,:,3)=B;
img3(:,:,1)=Y;  %ֻ��Y�����Ķ�ά����
% img3(:,:,2)=Y;
% img3(:,:,3)=Y;

% img3(:,:,2)=Cb;
% img3(:,:,3)=Cr;
tic
height= m; %�����  
width = n; %�����  
region_size = 8;  %�����ߴ�С  
numRow = round(height/region_size);%ͼ���ڴ�ֱ�����ֳܷɶ��ٸ���СΪregion_size  
numCol = round(width/region_size);%ͼ����ˮƽ�����ֳܷɶ��ٸ���СΪregion_size  
I=imresize(img3,[numRow*region_size,numCol*region_size]);%���������µ�ͼ���Է�ֹtemp�±�Խ��  
temp = I;
t1 = (0:numRow-1)*region_size + 1; t2 = (1:numRow)*region_size;  
t3 = (0:numCol-1)*region_size + 1; t4 = (1:numCol)*region_size;  
figure;   
k = 0;  
for i = 1 : numRow  
    for j = 1 : numCol  
        I(t1(i):t2(i), t3(j):t4(j), :) = dct21(I(t1(i):t2(i), t3(j):t4(j), :)); 
%         I(t1(i):t2(i), t3(j):t4(j), :) = dft2(I(t1(i):t2(i), t3(j):t4(j), :));    
    end  
end  
toc
psnr(temp,I)
imshow(uint8(I));
title('�ֶ��ֿ�DCT');
% Y = dct21(img3);
Y2=blkproc(img3,[8 8],'dct2');
X1=blkproc(Y2,[8 8],'idct2');
 
figure;
subplot(1,4,1);
imshow(img);
subplot(1,4,2);
imshow(uint8(img3));
title('Y����ͼ');
% subplot(1,4,3);
% imshow(uint8(Y));
% title('�Լ�ʵ�ֵ�δ�ֿ�DCT�任ͼ');
subplot(1,4,4);
imshow(uint8(Y2));
title('ϵͳ�ֿ�DCT�任ͼ');