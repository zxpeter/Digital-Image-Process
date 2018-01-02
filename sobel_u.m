function uSobel = sobel_u(imag)
[high,width] = size(imag);   % 获得图像的高度和宽度
% F2 = double(imag);        
U = double(imag);       
uSobel = imag;
for i = 2:high - 1   %sobel边缘检测
    for j = 2:width - 1
        Gx = (U(i+1,j-1) + 2*U(i+1,j) + U(i+1,j+1)) - (U(i-1,j-1) + 2*U(i-1,j) + U(i-1,j+1));
        Gy = (U(i-1,j+1) + 2*U(i,j+1) + U(i+1,j+1)) - (U(i-1,j-1) + 2*U(i,j-1) + U(i+1,j-1));
        uSobel(i,j) = sqrt(Gx^2 + Gy^2); 
    end
end 
% scale = 4; 
% cutoff = scale*mean2(uSobel); 
% thresh = sqrt(cutoff);
thresh = 240;
uSobel(uSobel>=thresh) = 255;
uSobel(uSobel<thresh) = 0;