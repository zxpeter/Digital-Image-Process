%% guassi
image=imread('E:\Jolie.bmp');
[width,height,z]=size(image);
if(z>1)
    image=rgb2gray(image);
end
figure(1);
subplot(2,2,1);
imshow(image);
title('ԭͼ');
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
title('�Ӹ�˹������');
avg_image = avg_filter(result1,5);
subplot(2,2,3);
imshow(avg_image);
title('��ֵ�˲���');
mid_image = mid_filter(result1,5);
subplot(2,2,4);
imshow(mid_image);
title('��ֵ�˲���');

avg_psnr = psnr(result1,avg_image);
avg_ssim = ssim_index(result1, avg_image, [0.01 0.03], ones(3), 255);
mid_psnr = psnr(result1,mid_image);
mid_ssim = ssim_index(result1, mid_image, [0.01 0.03], ones(3), 255);
%% ���뽷��������
image=imread('E:\Jolie.bmp');
[width,height,z]=size(image);
if(z>1)
    image=rgb2gray(image);
end
result2=image;
figure(2);
subplot(2,2,1);
imshow(image);
title('ԭͼ');
k1=0.05;
k2=0.3;
a1=rand(width,height)<k1;
a2=rand(width,height)<k2;
result2(a1&a2)=0;
result2(a1& ~a2)=255;
subplot(2,2,2);
imshow(result2);
title('�ӽ��κ�');
avg_image = avg_filter(result2,5);
subplot(2,2,3);
imshow(avg_image);
title('��ֵ�˲���');
mid_image = mid_filter(result2,5);
subplot(2,2,4);
imshow(mid_image);
title('��ֵ�˲���');
avg_psnr2 = psnr(result1,avg_image);
avg_ssim2 = ssim_index(result1, avg_image, [0.01 0.03], ones(3), 255);
mid_psnr2 = psnr(result1,mid_image);
mid_ssim2 = ssim_index(result1, mid_image, [0.01 0.03], ones(3), 255);
%% С���任
figure;
subplot(2,2,1); imshow(result1);
subplot(2,2,2); imshow(result2);
 %��С������sym4��x����2��С���ֽ�  
[c,s]=wavedec2(result2,2,'sym4');  
%��ȡС���ֽ��е�һ��ĵ�Ƶͼ�񣬼�ʵ���˵�ͨ�˲�ȥ��  
a1=wrcoef2('a',c,s,'sym4');  % a1Ϊ double �����ݣ�
%����ȥ����ͼ��  


subplot(2,2,3); imshow(uint8(a1)); % ע�� imshow()��image()��ʾͼ��������imshow()������ʾ double �����ݣ��������ת�� uint8(a1)��
title('��һ��ȥ��ͼ��');           % ����image() ��ʾͼ�������ꣻ
%��ȡС���ֽ��еڶ���ĵ�Ƶͼ�񣬼�ʵ���˵�ͨ�˲�ȥ��  
%�൱�ڰѵ�һ��ĵ�Ƶͼ�񾭹���һ�εĵ�Ƶ�˲�����  
a2=wrcoef2('a',c,s,'sym4',2);  
%����ȥ����ͼ��  
subplot(2,2,4); imshow(uint8(a2)); %image(a2);
title('�ڶ���ȥ��ͼ��');  

%% sobel
image=imread('E:\Jolie.bmp');
% image=imread('Lena.jpg');
image = rgb2gray(image);
subplot(1,3,1);
imshow(uint8(image));
uSobel = sobel_u(image);
subplot(1,3,2);
imshow(uint8(uSobel));
title('��Ե����');  %������Ե�����ͼ��
% Matlab�Դ�������Ե���
% KΪ��ȡ�õ��Ĺؼ�֡�ĻҶ�ͼ
BW3 = edge(image,'sobel', 0.09);
subplot(1,3,3);
imshow(BW3,[]);
title('Matlab�Դ�������Ե���');
