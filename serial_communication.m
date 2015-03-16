function varargout = serial_communication(varargin)
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @serial_communication_OpeningFcn, ...
    'gui_OutputFcn',  @serial_communication_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end

function serial_communication_OpeningFcn(hObject, eventdata, handles, varargin)
handles.output = hObject;
% javaFrame = get(hObject,'JavaFrame');
% javaFrame.setFigureIcon(javax.swing.ImageIcon('icon.jpg'));
global ha;
guidata(hObject, handles);

function varargout = serial_communication_OutputFcn(hObject, eventdata, handles)
varargout{1} = handles.output;

function com_Callback(hObject, eventdata, handles)

function com_CreateFcn(hObject, eventdata, handles)
global ha
set(hObject,'Value',ha.com);
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function rate_Callback(hObject, eventdata, handles)

function rate_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function jiaoyan_Callback(hObject, eventdata, handles)

function jiaoyan_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function data_bits_Callback(hObject, eventdata, handles)

function data_bits_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function stop_bits_Callback(hObject, eventdata, handles)

function stop_bits_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function start_serial_Callback(hObject, eventdata, handles)
global scom

if get(hObject,'value')
    com_n=sprintf('com%d',get(handles.com,'value'));
    rates=[300 600 1200 2400 4800 9600 19200 38400 43000 56000 57600 115200];
    baud_rate=rates(get(handles.rate,'value'));
    switch get(handles.jiaoyan,'value')
        case 1
            jiaoyan='none';
        case 2
            jiaoyan='odd';
        case 3
            jiaoyan='even';
    end
    data_bits=5+get(handles.data_bits,'value');
    stop_bits=get(handles.stop_bits,'value');
    scom=serial(com_n);
    set(scom,'BaudRate',baud_rate,'Parity',jiaoyan,'DataBits',...
        data_bits,'StopBits',stop_bits,'BytesAvailableFcnCount',100,...
        'BytesAvailableFcnMode','byte','BytesAvailableFcn',{@bytes,handles},...
        'TimerPeriod',0.1,'timerfcn',{@bytes,handles})
    try
        fopen(scom);
        set(handles.stop_disp,'Value',0);
    catch
        msgbox('串口不可获得！');
        return
    end
    str=get(scom,'Status');
    if strcmp(str,'closed')
        set(handles.start_serial,'BackgroundColor','r');
    elseif strcmp(str,'open')
        set(handles.start_serial,'BackgroundColor','g');
    end
    %     set(handles.xianshi,'string','')
    %     set(handles.activex1,'value',1)
else
    t=timerfind;
    try
        stop(t);
        delete(t);
    end
    scoms=instrfind;
    stopasync(scom);
    fclose(scoms);
    str=get(scom,'Status');
    if strcmp(str,'closed')
        set(handles.start_serial,'BackgroundColor','r');
    elseif strcmp(str,'open')
        set(handles.start_serial,'BackgroundColor','g');
    end
    delete(scoms);
    set(handles.period_send,'value',0)
    %     set(handles.activex1,'value',0)
end


function bytes(obj,~,handles)
global ha;
if ha.stop_disp
    flushinput(obj);
else
    n=get(obj,'BytesAvailable');
    if n
        a=fread(obj,n,'uchar');
        if ha.save_flag
            fwrite(ha.fid,a);
        end
        if ~ha.hex_disp
            c=char(a');
            str= [get(handles.xianshi,'string') c];
            while length(str)>ha.data_length
                str = str(ha.data_length/20:end);
            end
            set(handles.xianshi,'string',str);
            set(handles.rec,'string',num2str(str2num(get(handles.rec,'string'))+length(c)))
        else
            b=dec2hex(a,2);
            [m,n]=size(b);
            c=[];
            for i=1:m
                c=[c,b(i,:),' '];
            end
            str = [get(handles.xianshi,'string') c];
            while length(str)>(ha.data_length*3)
                str = str(ha.data_length*3/20:end);
            end
            set(handles.xianshi,'string',str);
            set(handles.rec,'string',num2str(str2num(get(handles.rec,'string'))+m));
        end
        ha.data=[ha.data;a];
        while length(ha.data)>(ha.data_length)
            ha.data=ha.data(61:end);
        end
        if(ha.self_cur)
            selfprocess;
        else
            data_process();
        end
    end
end


function qingkong_Callback(hObject, eventdata, handles)
set(handles.xianshi,'string','')
global ha;
ha.data=[];
ha.pdata = [];
h = get(ha.handle, 'children');
delete(h);


function stop_disp_Callback(hObject, eventdata, handles)
global ha;
ha.stop_disp = get(hObject,'Value');

function radiobutton1_Callback(hObject, eventdata, handles)

function radiobutton2_Callback(hObject, eventdata, handles)

function togglebutton4_Callback(hObject, eventdata, handles)

function hex_disp_Callback(hObject, eventdata, handles)
global ha;
ha.hex_disp = get(hObject,'Value');
function manual_send_Callback(hObject, eventdata, handles)
global scom
global ha;
if ~ha.hex_send
    str=get(handles.sends,'string');
    val=str;
    set(handles.trans,'string',num2str(str2num(get(handles.trans,'string'))+length((str))))
else
    a=get(handles.sends,'string');
    b= [];
    for i=1:3:length(a)-1
        b=[b;a(i:i+1)];
    end
    try
        val=hex2dec(b)';
    catch
        msgbox('wrong input data format!');
    end
    set(handles.trans,'string',num2str(str2num(get(handles.trans,'string'))+length(val)))
end
if ~isempty(val)
    try
        str=get(scom,'TransferStatus');
    catch
        return
    end
    while 1
        if ~(strcmp(str, 'write')||strcmp(str,'read&write'))
            fwrite(scom,val,'uint8','async');
            break
        end
    end
end


function pushbutton1_Callback(hObject, eventdata, handles)
set(handles.sends,'string','')

function checkbox2_Callback(hObject, eventdata, handles)


function period_send_Callback(hObject, eventdata, handles)
if get(hObject,'value')
    t1=0.001*str2num(get(handles.period1,'string'));
    t=timer('BusyMode','queue','ExecutionMode','fixedrate',...
        'Period',t1,'TimerFcn',{@manual_send_Callback,handles});
    start(t);
else
    t=timerfind;
    stop(t);
    delete(t);
    clear t
end

function period1_Callback(hObject, eventdata, handles)

function period1_CreateFcn(hObject, eventdata, handles)
global ha
set(hObject,'String',num2str(ha.auto_time));
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function pushbutton2_Callback(hObject, eventdata, handles)
set([handles.rec,handles.trans],'string','0')

function copy_data_Callback(hObject, eventdata, handles)
if get(hObject,'value')
    set(handles.xianshi,'enable','on')
else
    set(handles.xianshi,'enable','inactive')
end


% --- Executes on button press in plotdata.
function plotdata_Callback(hObject, eventdata, handles)
% hObject    handle to plotdata (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
if ~get(handles.plotdata,'value')
    ha.plot_flag = 0;
    h = get(gca, 'children');
    delete(h);
else
    set(handles.checkbox10,'value',0);
    if ~isempty(ha.selfh)
        delete(ha.selfh);
        ha.selfh=[];
    end
    ha.self_cur = 0;
    ha.plot_flag = 1;
    plot(ha.handle,ha.pdata,[ha.line_style,ha.line_marker,ha.line_color],'linewidth',ha.line_width);
end
% Hint: get(hObject,'Value') returns toggle state of plotdata




% --- Executes on selection change in bytes.
function bytes_Callback(hObject, eventdata, handles)
% hObject    handle to bytes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
ha.byte_num=get(hObject,'value');
if(ha.self_cur)
    selfprocess;
else
    data_process();
end
% Hints: contents = get(hObject,'String') returns bytes contents as cell array
%        contents{get(hObject,'Value')} returns selected item from bytes


% --- Executes during object creation, after setting all properties.
function bytes_CreateFcn(hObject, eventdata, handles)
% hObject    handle to bytes (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha
set(hObject,'Value',ha.byte_num);
% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in hold.
function hold_Callback(hObject, eventdata, handles)
% hObject    handle to hold (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha
if get(hObject,'value')
    set(handles.hold,'string','hold off')
    hold(ha.handle,'on');
    ha.data=[]
    ha.pdata=[];
else
    set(handles.hold,'string','hold on')
    hold(ha.handle,'off');
end
% Hint: get(hObject,'Value') returns toggle state of hold

% --- Executes during object deletion, before destroying properties.
function figure1_DeleteFcn(hObject, eventdata, handles)
%     global scom;
global ha;
scoms=instrfind;
delete(scoms);
 if ~isempty(ha.fid)
    fclose(ha.fid);
 end
%




% --- Executes during object creation, after setting all properties.
function start_serial_CreateFcn(hObject, eventdata, handles)
% hObject    handle to start_serial (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called




% --- Executes on button press in axes1_property.
function axes1_property_Callback(hObject, eventdata, handles)
% hObject    handle to axes1_property (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
axes_property;







% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to  (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
ha.handle = hObject;
h = get(ha.handle, 'children');
delete(h);
% Hint: place code in OpeningFcn to populate


function data_process()
global ha;
if ha.plot_flag
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
    plot(ha.handle,ha.pdata,[ha.line_style,ha.line_marker,ha.line_color],'linewidth',ha.line_width);
    xlim(ha.handle,ha.xlim);
    ylim(ha.handle,ha.ylim);
%     xlabel(ha.handle,ha.xlabel);
%     ylabel(ha.handle,ha.ylabel);
end





% --- Executes on button press in hex_send.
function hex_send_Callback(hObject, eventdata, handles)
% hObject    handle to hex_send (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
ha.hex_send = get(hObject,'Value');
% Hint: get(hObject,'Value') returns toggle state of hex_send




% --- Executes on button press in checkbox10.
function checkbox10_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha
ha.self_cur = get(hObject,'Value');
if ha.self_cur
    set(handles.plotdata,'value',0);
    h = get(ha.handle, 'children');
    delete(h);
    axes_ctl;
end
% Hint: get(hObject,'Value') returns toggle state of checkbox10




% --- Executes during object creation, after setting all properties.
function plotdata_CreateFcn(hObject, eventdata, handles)
% hObject    handle to plotdata (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
if ha.self_cur
    set(hObject,'Value',0);
    ha.plot_flag =0;
else
    set(hObject,'Value',ha.plot_flag);
end





% --- Executes during object creation, after setting all properties.
function checkbox10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to checkbox10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha
set(hObject,'Value',ha.self_cur);
if ha.self_cur
    axes_ctl;
end



% --- Executes on button press in checkbox11.
function checkbox11_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
if(get(hObject,'Value'))
    ha.save_flag = 1;
%     if exist('rec.dat','file')
%         delete('rec.dat');
%     end
    ha.fid=fopen(ha.save_name,'w+');
%     fseek(ha.fid,0,'bof');
    set(hObject,'String','saving,click to finish');
else
    if ~isempty(ha.fid)
    fclose(ha.fid);
    ha.fid=[];
    end
    ha.save_flag = 0;
    set(hObject,'String','save');
end
% Hint: get(hObject,'Value') returns toggle state of checkbox11





% --- Executes during object creation, after setting all properties.
function stop_disp_CreateFcn(hObject, eventdata, handles)
% hObject    handle to stop_disp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha
set(hObject,'Value',ha.stop_disp);



% --- Executes during object creation, after setting all properties.
function hex_disp_CreateFcn(hObject, eventdata, handles)
global ha
set(hObject,'Value',ha.hex_disp);
% hObject    handle to hex_disp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called




% --- Executes during object creation, after setting all properties.
function checkbox11_CreateFcn(hObject, eventdata, handles)
global ha
set(hObject,'Value',ha.stop_disp);
% hObject    handle to checkbox11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called




% --- Executes during object creation, after setting all properties.
function hex_send_CreateFcn(hObject, eventdata, handles)
global ha
set(hObject,'Value',ha.hex_send);
% hObject    handle to hex_send (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called




% --- Executes during object creation, after setting all properties.
function period_send_CreateFcn(hObject, eventdata, handles)
global ha
set(hObject,'Value',ha.auto_send);
% hObject    handle to period_send (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called



%% -----------------------按键按下回调函数------------------------%%

% --- Executes on button press in ManualControl.
function ManualControl_Callback(hObject, eventdata, handles)
% hObject    handle to ManualControl (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
global manual_flag
global press_key
global slidervalue
press_key = 0;
manual_flag = get(hObject,'Value');
%为防止SpeedSlider和其储存的值slidervalue的初值不确定(createfcn设置无效)，在启动人工控制前，
%再次强制设定speedslider和slidervalue的值。
set(handles.SpeedSlider,'Value',5);
slidervalue = get(handles.SpeedSlider,'Value');
slidervalue = round(slidervalue);
Tmp = ['Speed: ',num2str((slidervalue)/10)];
set(handles.SpeedText,'String',Tmp);
if(manual_flag == 0)
    set(handles.ManualControl,'BackgroundColor','r');
    set(handles.Forward,'Enable','off');
    set(handles.Backward,'Enable','off');
    set(handles.TurnLeft,'Enable','off');
    set(handles.TurnRight,'Enable','off');
    set(handles.Stop,'Enable','off');
    set(handles.Forward,'BackgroundColor','r');
    set(handles.Backward,'BackgroundColor','r');
    set(handles.TurnLeft,'BackgroundColor','r');
    set(handles.TurnRight,'BackgroundColor','r');
    set(handles.Forward,'Value',0);
    set(handles.Backward,'Value',0);
    set(handles.TurnLeft,'Value',0);
    set(handles.TurnRight,'Value',0);
    fprintf(scom,'%s\r\n','quit');
elseif(manual_flag == 1)
    set(handles.ManualControl,'BackgroundColor','g');
    set(handles.Forward,'Enable','inactive');
    set(handles.Backward,'Enable','inactive');
    set(handles.TurnLeft,'Enable','inactive');
    set(handles.TurnRight,'Enable','inactive');
    set(handles.Stop,'Enable','on');
    set(handles.Forward,'Value',0);
    set(handles.Backward,'Value',0);
    set(handles.TurnLeft,'Value',0);
    set(handles.TurnRight,'Value',0);
    fprintf(scom,'%s\r\n','manual');
end

function figure1_WindowButtonUpFcn(hObject, eventdata, handles)
global scom
global manual_flag
global press_key
manual_flag = get(handles.ManualControl,'Value');
if(manual_flag == 1 && press_key == 0)
    set(handles.Forward,'BackgroundColor','r');
    set(handles.Backward,'BackgroundColor','r');
    set(handles.TurnLeft,'BackgroundColor','r');
    set(handles.TurnRight,'BackgroundColor','r');
    set(handles.Forward,'Value',0);
    set(handles.Backward,'Value',0);
    set(handles.TurnLeft,'Value',0);
    set(handles.TurnRight,'Value',0);
    fprintf(scom,'%s\r\n','stop'); 
end


function Forward_ButtonDownFcn(hObject, eventdata, handles)
global scom
global slidervalue
global manual_flag
global press_key
manual_flag = get(handles.ManualControl,'Value');
if(manual_flag == 1 && press_key == 0)
    set(handles.Forward,'BackgroundColor','g');
    set(handles.Backward,'BackgroundColor','r');
    set(handles.TurnLeft,'BackgroundColor','r');
    set(handles.TurnRight,'BackgroundColor','r');
    set(handles.Forward,'Value',1);
    set(handles.Backward,'Value',0);
    set(handles.TurnLeft,'Value',0);
    set(handles.TurnRight,'Value',0);
    fprintf(scom,'forward+%.0f\r\n',slidervalue);
end

function Backward_ButtonDownFcn(hObject, eventdata, handles)
global scom
global slidervalue
global manual_flag
global press_key
manual_flag = get(handles.ManualControl,'Value');
if(manual_flag == 1 && press_key == 0)
    set(handles.Forward,'BackgroundColor','r');
    set(handles.Backward,'BackgroundColor','g');
    set(handles.TurnLeft,'BackgroundColor','r');
    set(handles.TurnRight,'BackgroundColor','r');
    set(handles.Forward,'Value',0);
    set(handles.Backward,'Value',1);
    set(handles.TurnLeft,'Value',0);
    set(handles.TurnRight,'Value',0);
    fprintf(scom,'backward+%.0f\r\n',slidervalue);
end

function TurnLeft_ButtonDownFcn(hObject, eventdata, handles)
global scom
global slidervalue
global manual_flag
global press_key
manual_flag = get(handles.ManualControl,'Value');
if(manual_flag == 1 && press_key == 0)
    set(handles.Forward,'BackgroundColor','r');
    set(handles.Backward,'BackgroundColor','r');
    set(handles.TurnLeft,'BackgroundColor','g');
    set(handles.TurnRight,'BackgroundColor','r');
    set(handles.Forward,'Value',0);
    set(handles.Backward,'Value',0);
    set(handles.TurnLeft,'Value',1);
    set(handles.TurnRight,'Value',0);
    fprintf(scom,'turnleft+%.0f\r\n',slidervalue);
end

function TurnRight_ButtonDownFcn(hObject, eventdata, handles)
global scom
global slidervalue
global manual_flag
global press_key
manual_flag = get(handles.ManualControl,'Value');
if(manual_flag == 1 && press_key == 0)
    set(handles.Forward,'BackgroundColor','r');
    set(handles.Backward,'BackgroundColor','r');
    set(handles.TurnLeft,'BackgroundColor','r');
    set(handles.TurnRight,'BackgroundColor','g');
    set(handles.Forward,'Value',0);
    set(handles.Backward,'Value',0);
    set(handles.TurnLeft,'Value',0);
    set(handles.TurnRight,'Value',1);
    fprintf(scom,'turnright+%.0f\r\n',slidervalue);
end

function Stop_Callback(hObject, eventdata, handles)
% hObject    handle to Stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scom
global manual_flag
global press_key
manual_flag = get(handles.ManualControl,'Value');
if(manual_flag == 1 && press_key == 0)
    set(handles.Forward,'BackgroundColor','r');
    set(handles.Backward,'BackgroundColor','r');
    set(handles.TurnLeft,'BackgroundColor','r');
    set(handles.TurnRight,'BackgroundColor','r');
    set(handles.Forward,'Value',0);
    set(handles.Backward,'Value',0);
    set(handles.TurnLeft,'Value',0);
    set(handles.TurnRight,'Value',0);
    fprintf(scom,'%s\r\n','stop');
end

% --- Executes on slider movement.
function SpeedSlider_Callback(hObject, eventdata, handles)
% hObject    handle to SpeedSlider (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider
global slidervalue
slidervalue = get(hObject,'Value');
slidervalue = round(slidervalue);
Tmp = ['Speed: ',num2str((slidervalue)/10)];
set(handles.SpeedText,'String',Tmp);
%% -----------------------按键按下回调函数------------------------ %%




%% -----------------------按键初始状态设置------------------------ %%
%如果只判断触发的控件本身的状态，那么set(),get()只需要用hObject即可，要改其他控件时采用handels.xxx。
%若用handles.xxx，则因为该控件本身还没完全准备好，而导致错误。
function ManualControl_CreateFcn(hObject, eventdata, handles)
set(hObject,'BackgroundColor','r');
set(hObject,'Value',0);
global manual_flag
manual_flag = get(hObject,'Value');

function Forward_CreateFcn(hObject, eventdata, handles)
set(hObject,'BackgroundColor','r');
set(hObject,'Enable','off');

function Backward_CreateFcn(hObject, eventdata, handles)
set(hObject,'BackgroundColor','r');
set(hObject,'Enable','off');

function TurnLeft_CreateFcn(hObject, eventdata, handles)
set(hObject,'BackgroundColor','r');
set(hObject,'Enable','off');

function TurnRight_CreateFcn(hObject, eventdata, handles)
set(hObject,'BackgroundColor','r');
set(hObject,'Enable','off');

function Stop_CreateFcn(hObject, eventdata, handles)
set(hObject,'BackgroundColor','r');
set(hObject,'Enable','off');


function SpeedSlider_CreateFcn(hObject, eventdata, handles)
% Hint: slider controls usually have a light gray background.
global slidervalue
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject,'Value',5);
slidervalue = get(hObject,'Value');
slidervalue = round(slidervalue);

% --- Executes during object creation, after setting all properties.
function SpeedText_CreateFcn(hObject, eventdata, handles)
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
%% -----------------------按键初始状态设置------------------------ %%


%% -----------------------窗口检测到按键的回调函数------------------------ %%
% --- Executes on key press with focus on figure1 or any of its controls.
function figure1_WindowKeyPressFcn(hObject, eventdata, handles)
global scom
global slidervalue
global manual_flag
global press_key
manual_flag = get(handles.ManualControl,'Value');
%应该判断是否持续按下某键(若持续按下，则只用fprintf发送一次指令)
%键盘和按键不一样，按下后会持续触发pressFcn而发送多次指令，导致按键停止后小车依然在运行.
%加入press+key==0判断后，若某键先按下，则其他按键不再响应，只能等该键松开。
if(manual_flag == 1 && press_key==0)
    switch eventdata.Character
        case 30
            press_key = 1;
            set(handles.Forward,'BackgroundColor','g');
            set(handles.Backward,'BackgroundColor','r');
            set(handles.TurnLeft,'BackgroundColor','r');
            set(handles.TurnRight,'BackgroundColor','r');
            set(handles.Forward,'Value',1);
            set(handles.Backward,'Value',0);
            set(handles.TurnLeft,'Value',0);
            set(handles.TurnRight,'Value',0);
            fprintf(scom,'forward+%.0f\r\n',slidervalue);
        case 31
            press_key = 1;
            set(handles.Forward,'BackgroundColor','r');
            set(handles.Backward,'BackgroundColor','g');
            set(handles.TurnLeft,'BackgroundColor','r');
            set(handles.TurnRight,'BackgroundColor','r');
            set(handles.Forward,'Value',0);
            set(handles.Backward,'Value',1);
            set(handles.TurnLeft,'Value',0);
            set(handles.TurnRight,'Value',0);
            fprintf(scom,'backward+%.0f\r\n',slidervalue);
        case 28
            press_key = 1;
            set(handles.Forward,'BackgroundColor','r');
            set(handles.Backward,'BackgroundColor','r');
            set(handles.TurnLeft,'BackgroundColor','g');
            set(handles.TurnRight,'BackgroundColor','r');
            set(handles.Forward,'Value',0);
            set(handles.Backward,'Value',0);
            set(handles.TurnLeft,'Value',1);
            set(handles.TurnRight,'Value',0);
            fprintf(scom,'turnleft+%.0f\r\n',slidervalue);
         case 29
             press_key = 1;
            set(handles.Forward,'BackgroundColor','r');
            set(handles.Backward,'BackgroundColor','r');
            set(handles.TurnLeft,'BackgroundColor','r');
            set(handles.TurnRight,'BackgroundColor','g');
            set(handles.Forward,'Value',0);
            set(handles.Backward,'Value',0);
            set(handles.TurnLeft,'Value',0);
            set(handles.TurnRight,'Value',1);
            fprintf(scom,'turnright+%.0f\r\n',slidervalue);
        otherwise
    end
end

% --- Executes on key release with focus on figure1 or any of its controls.
function figure1_WindowKeyReleaseFcn(hObject, eventdata, handles)
global scom
global manual_flag
global press_key
press_key = 0;
manual_flag = get(handles.ManualControl,'Value');
if(manual_flag == 1)
    set(handles.Forward,'BackgroundColor','r');
    set(handles.Backward,'BackgroundColor','r');
    set(handles.TurnLeft,'BackgroundColor','r');
    set(handles.TurnRight,'BackgroundColor','r');
    set(handles.Forward,'Value',0);
    set(handles.Backward,'Value',0);
    set(handles.TurnLeft,'Value',0);
    set(handles.TurnRight,'Value',0);
    fprintf(scom,'%s\r\n','stop'); 
end
%% -----------------------窗口检测到按键的回调函数------------------------ %%


% --- Executes on key press with focus on SpeedSlider and none of its controls.
function SpeedSlider_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to SpeedSlider (see GCBO)
% eventdata  structure with the following fields (see UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)
