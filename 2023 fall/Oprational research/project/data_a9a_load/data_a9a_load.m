%% matlab读取a9a数据代码

 clear all;

file_name='a9a.txt';
is_sparse=1;
feat=123;%1355191;
%%
filepath=['./',file_name];
fid=fopen(filepath,'r');
b2=inf;

if is_sparse==1
    Xtrain=sparse(feat,0);
else
    Xtrain=zeros(feat,0);
end
Ylabel=[];
data{1}=Xtrain;
data{2}=Ylabel;
Data{1}=data;
for k=1:1e10   
    str=fgetl(fid);
    if mod(k,100)==0
        k;
    end
    
    if str==(-1)
        break;
    end
    n=length(str);
    if n<=3
        Xtrain(:,end+1)=0;
        if n<2
            Ylabel(end+1,1)=str2num(str);
        else
            Ylabel(end+1,1)=str2num(str([1,2]));
        end
        continue;
    end
    J=[];Value=[];
 Ylabel(end+1,1)=str2num(str([1,2]));%(str([1,4]));%(str(1:4));
    for j=1:n
        id=0;
        if j==n
            Value(end+1)= str2num(str(b2+1:n));
            break;
        end
        if str(j)==' '
            b1=j;
            id=1;
        end
        if str(j)==':'
            b2=j;
            id=2;
        end
        if id==1&&b1>=b2;
            Value(end+1)=str2num(str(b2+1:b1-1));
        end
        if id==2
            J(end+1)=str2num(str(b1+1:b2-1));
        end
    end
    Xtrain(J,end+1)=Value;
    if mod(k,1001)==0
        if is_sparse==1
            data{1}=sparse(Xtrain);
        else
            data{1}=Xtrain;
        end
        data{2}=Ylabel
        Data{end+1}=data;
        if is_sparse==1
            Xtrain=sparse(feat,0);
        else
            Xtrain=zeros(feat,0);
        end
        Ylabel=[];
        continue;
    end
end
data{1}=Xtrain;
data{2}=Ylabel;
Data{end+1}=data;
fclose(fid);
Xtrain=[];
Ylabel=[];
Data=Data(2:end);
len_D=length(Data);
for d=1:len_D
    Xtrain=[Xtrain,Data{1}{1}];
    Ylabel=[Ylabel;Data{1}{2}];
    if d<len_D
        Data=Data(2:end);
    end
end
data{1}=Xtrain;
data{2}=Ylabel;
save([file_name,'.mat'],'data');
 
