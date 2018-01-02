function [ out ] = psnr( X,Y )
[ m,n ] = size( X );
mse = sum(( double(X(:)) - double(Y(:)) ).^2);
mse = mse/(m*n);
out = 10*log10((255*255)/mse);
end