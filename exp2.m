clear;
close all;
clc;

img=imread('time.bmp');
%img=mat2gray(img);  %任意区间映射到[0,1];
[m n dim]=size(img);
% imshow(img);
%%图像的RGB
img2=double(img);
R=img2(:,:,1);
G=img2(:,:,2);
B=img2(:,:,3);

%%RGB2YCbCr
Y=zeros(m,n);    %亮度
Cb=zeros(m,n);   %彩度
Cr=zeros(m,n);   %浓度
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

%%如果正反变换都没错的话，那么图像是不变的
% img(:,:,1)=R;
% img(:,:,2)=G;
% img(:,:,3)=B;
img3(:,:,1)=Y;  %只有Y分量的二维矩阵
% img3(:,:,2)=Y;
% img3(:,:,3)=Y;

% img3(:,:,2)=Cb;
% img3(:,:,3)=Cr;
tic
height= m; %求出行  
width = n; %求出列  
region_size = 8;  %区域宽高大小  
numRow = round(height/region_size);%图像在垂直方向能分成多少个大小为region_size  
numCol = round(width/region_size);%图像在水平方向能分成多少个大小为region_size  
I=imresize(img3,[numRow*region_size,numCol*region_size]);%重新生成新的图像，以防止temp下标越界  
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
title('手动分块DCT');
% Y = dct21(img3);
Y2=blkproc(img3,[8 8],'dct2');
X1=blkproc(Y2,[8 8],'idct2');
 
figure;
subplot(1,4,1);
imshow(img);
subplot(1,4,2);
imshow(uint8(img3));
title('Y分量图');
% subplot(1,4,3);
% imshow(uint8(Y));
% title('自己实现的未分块DCT变换图');
subplot(1,4,4);
imshow(uint8(Y2));
title('系统分块DCT变换图');