function Y = dft2(X)
[m n dim]=size(X);
AM=zeros(m);
AN=zeros(n);
for x=1:m
    for u=1:m  
        AM(x,u)=0.25*exp(1i*2*pi*(x-1)*(u-1)/m);  
    end  
end  
  
for y=1:n  
    for v=1:n
        AN(y,v)=0.25*exp(1i*2*pi*(v-1)*(y-1)/n);  
    end  
end  
Y=AM*X*AN';        %DFT±ä»»

%fourier matrix  
 