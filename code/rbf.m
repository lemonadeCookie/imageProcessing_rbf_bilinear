rate = 0.8;
I = imread('d.jpg');
I = rgb2gray(I);
I = double(I);
[m,n] = size(I);
mask = rand(m,n);
mask(find(mask>rate))=1;
mask(find(mask<rate))=0;
for i=1:m
     for j=1:n
        if(mask(i,j)== 1)
           I(i,j) = 255;
        end
     end
end

fid=fopen('RBFmid_d_0.2.txt','w');
[m ,n]=size(I);
fprintf('%g\n',m);
fprintf('%g\n',n);
 for i=1:1:m
    for j=1:1:n
       if j==n
         fprintf(fid,'%g\n',I(i,j));
      else
        fprintf(fid,'%g\t',I(i,j));
       end
    end
end
fclose(fid);

for i= 1:m
 for j= 1:n
     if mask(i,j)==1
        count = 0;
        x = (24); y = (24); b = (24);
        A = [24,24];
        for k=i-4:1:i+4
         for h=j-4:1:j+4
          if k >= 1 && k <= m && h >= 1 && h <= n
             if mask(k,h)==0
                 count = count + 1;
                 x(count) = k;
                 y(count) = h;
                 b(count) = I(k,h);
             end
          end  
         end
        end
        if (count>1)    
         for k=1:1:count
            for h=1:1:count
             r = (x(k)-x(h))*(x(k)-x(h)) + (y(k)-y(h))*(y(k)-y(h)); 
             A(k,h) = sqrt(1+0.3*r);
            end
         end
         b = b';
         w = A \ b;
         I(i,j)=0;
         for k = 1:1:count
           r = (i-x(k))*(i-x(k))+(j-y(k))*(j-y(k));  
           I(i,j) = I(i,j)+w(k)*sqrt(1+0.3*r);
         end  
        end
        
     end
 end
end
I = uint8(I);
result = I;
imshow(result);

fid2=fopen('RBFout_d_0.2.txt','w');
[m ,n]=size(result);
fprintf('%g\n',m);
fprintf('%g\n',n);
 for i=1:1:m
    for j=1:1:n
       if j==n
         fprintf(fid2,'%g\n',result(i,j));
      else
        fprintf(fid2,'%g\t',result(i,j));
       end
    end
end
fclose(fid2);
