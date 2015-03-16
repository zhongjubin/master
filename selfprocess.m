function selfprocess()
global ha
ha.sgn=1;%ha.sgn is the sign of the number 1: signed,and 0: unsigned;
%% transit to (Bytes X uint8) to num
ha.pdata=zeros(1,floor(length(ha.data)/ha.byte_num));
l=1;
for i=1:ha.byte_num:length(ha.data)-ha.byte_num+1
    for j=1:ha.byte_num
        ha.pdata(l)=ha.pdata(l)*256+ha.data(i+j-1);
    end
    if ha.sgn
        if ha.pdata(l)>2^(8*ha.byte_num-1)-1
            ha.pdata(l)=ha.pdata(l)-2^(8*ha.byte_num);
        end
    end
    l=l+1;
end
%% plot them in its axeses.
plot(ha.ah1,[1:length(ha.pdata(1:3:end))],ha.pdata(1:3:end),'b-',1:length(ha.pdata(2:3:end)),ha.pdata(2:3:end),'r-',...
    1:length(ha.pdata(3:3:end)),ha.pdata(3:3:end),'g-');
% plot(ha.ah2,ha.pdata(2:3:end),'b-');
% plot(ha.ah3,ha.pdata(3:3:end),'b-');
