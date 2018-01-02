%% guassi
image=imread('E:\Jolie.bmp');
[width,height,z]=size(image);
if(z>1)
    image=rgb2gray(image);
end
figure(1);
subplot(2,2,1);
imshow(image);
title('原图');
av=0;
std=0.1;
u1=rand(width,height);
u2=rand(width,height);
x=std*sqrt(-2*log(u1)).*cos(2*pi*u2)+av;
% x = 0.08 * u1;
% result1(:,:,1)=double(image(:,:,1))/255+x;
% result1(:,:,2)=double(image(:,:,2))/255;
% result1(:,:,3)=double(image(:,:,3))/255;
result1=double(image)/255+x;
result1=uint8(255*result1);
% result1=uint8(double(image)+x);
subplot(2,2,2);
imshow(result1);
title('加高斯噪声后');
avg_image = avg_filter(result1,5);
subplot(2,2,3);
imshow(avg_image);
title('均值滤波后');
mid_image = mid_filter(result1,5);
subplot(2,2,4);
imshow(mid_image);
title('中值滤波后');

avg_psnr = psnr(result1,avg_image);
avg_ssim = ssim_index(result1, avg_image, [0.01 0.03], ones(3), 255);
mid_psnr = psnr(result1,mid_image);
mid_ssim = ssim_index(result1, mid_image, [0.01 0.03], ones(3), 255);
%% 加入椒盐噪声：
image=imread('E:\Jolie.bmp');
[width,height,z]=size(image);
if(z>1)
    image=rgb2gray(image);
end
result2=image;
figure(2);
subplot(2,2,1);
imshow(image);
title('原图');
k1=0.05;
k2=0.3;
a1=rand(width,height)<k1;
a2=rand(width,height)<k2;
result2(a1&a2)=0;
result2(a1& ~a2)=255;
subplot(2,2,2);
imshow(result2);
title('加椒盐后');
avg_image = avg_filter(result2,5);
subplot(2,2,3);
imshow(avg_image);
title('均值滤波后');
mid_image = mid_filter(result2,5);
subplot(2,2,4);
imshow(mid_image);
title('中值滤波后');
avg_psnr2 = psnr(result1,avg_image);
avg_ssim2 = ssim_index(result1, avg_image, [0.01 0.03], ones(3), 255);
mid_psnr2 = psnr(result1,mid_image);
mid_ssim2 = ssim_index(result1, mid_image, [0.01 0.03], ones(3), 255);
%% 小波变换
figure;
subplot(2,2,1); imshow(result1);
subplot(2,2,2); imshow(result2);
 %用小波函数sym4对x进行2层小波分解  
[c,s]=wavedec2(result2,2,'sym4');  
%提取小波分解中第一层的低频图像，即实现了低通滤波去噪  
a1=wrcoef2('a',c,s,'sym4');  % a1为 double 型数据；
%画出去噪后的图像  


subplot(2,2,3); imshow(uint8(a1)); % 注意 imshow()和image()显示图像有区别，imshow()不能显示 double 型数据，必须进行转换 uint8(a1)；
title('第一次去噪图像');           % 并且image() 显示图像有坐标；
%提取小波分解中第二层的低频图像，即实现了低通滤波去噪  
%相当于把第一层的低频图像经过再一次的低频滤波处理  
a2=wrcoef2('a',c,s,'sym4',2);  
%画出去噪后的图像  
subplot(2,2,4); imshow(uint8(a2)); %image(a2);
title('第二次去噪图像');  

%% sobel
image=imread('E:\Jolie.bmp');
% image=imread('Lena.jpg');
image = rgb2gray(image);
subplot(1,3,1);
imshow(uint8(image));
uSobel = sobel_u(image);
subplot(1,3,2);
imshow(uint8(uSobel));
title('边缘检测后');  %画出边缘检测后的图像
% Matlab自带函数边缘检测
% K为获取得到的关键帧的灰度图
BW3 = edge(image,'sobel', 0.09);
subplot(1,3,3);
imshow(BW3,[]);
title('Matlab自带函数边缘检测');
