%�Ա����ֵ�˲�������x����Ҫ�˲���ͼ��,n��ģ���С(��n��n)  
function d=mid_filter(x,n)     
[height, width]=size(x);   %����ͼ����p��q��,��p>n,q>n  
x1=double(x);  
x2=x1;  
for i=1:height-n+1  
    for j=1:width-n+1  
        c=x1(i:i+(n-1),j:j+(n-1)); %ȡ��x1�д�(i,j)��ʼ��n��n��Ԫ��,��ģ��(n��n��)  
        e=c(1,:);      %��c����ĵ�һ��  
        for u=2:n  
            e=[e,c(u,:)];     %��c�����Ϊһ���о���      
        end  
        mm=median(e);      %mm����ֵ  
        x2(i+(n-1)/2,j+(n-1)/2)=mm;   %��ģ���Ԫ�ص���ֵ����ģ������λ�õ�Ԫ��  
    end  
end   
%δ����ֵ��Ԫ��ȡԭֵ  
d=uint8(x2);  