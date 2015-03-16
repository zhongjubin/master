function axes_ctl()
%%  Pleale do not modify This part
edit('selfprocess.m');  %if you do not edit two file you can comment them
edit('axes_ctl.m');
global ha;
%% you can modify this part to control  yours figure and axes
try
    if(~isempty(ha.selfh))%if you have multiple figures you can close them at this part
        close(ha.selfh);
    end
catch
end
ha.selfh=figure('name','Self Figure');
figure(ha.selfh); %if you want to make your own plot mode you can chang the code 
% ha.ah1 =subplot(3,1,1);
% ha.ah2 =subplot(3,1,2);
% ha.ah3 =subplot(3,1,3);
ha.ah1 = axes;
selfprocess()
%% Important note if you change  the code above 
%% Please do same change in""""selfprocess.m """"according to your changes