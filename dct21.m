% function Y = dct21(X)
function X2 = dct21(X)
[m n dim]=size(X);
AM=zeros(m);
AN=zeros(n);
for i=0:m-1
    for j=0:m-1
        if i==0
            a=sqrt(1/m);
        else
            a=sqrt(2/m);
        end            
        AM(i+1,j+1)=a*cos(pi*(j+0.5)*i/m);
    end
end
for i=0:n-1
    for j=0:n-1
        if i==0
            a=sqrt(1/n);
        else
            a=sqrt(2/n);
        end            
        AN(i+1,j+1)=a*cos(pi*(j+0.5)*i/n);
    end
end

Y=AM*X*AN';        %DCT±ä»»
mask1=[1 0 0 0 0 0 0 0 
             0 0 0 0 0 0 0 0 
             0 0 0 0 0 0 0 0 
             0 0 0 0 0 0 0 0 
             0 0 0 0 0 0 0 0 
             0 0 0 0 0 0 0 0 
             0 0 0 0 0 0 0 0 
             0 0 0 0 0 0 0 0];
% mask1=[0 0 0 0 0 0 0 0 
%              0 0 0 0 0 0 1 1 
%              0 0 0 0 0 1 1 1 
%              0 0 0 0 1 1 1 1 
%              0 0 0 0 1 1 1 1 
%              0 0 1 1 1 1 1 1 
%              0 1 1 1 1 1 1 1 
%              1 1 1 1 1 1 1 1];
% AM = AM .* mask1;
% AN = AN .* mask1;
Y = Y .* mask1;
X2=AM'*Y*AN;        %DCT·´±ä»»


