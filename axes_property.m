function varargout = axes_property(varargin)
% AXES_PROPERTY M-file for axes_property.fig
%      AXES_PROPERTY, by itself, creates a new AXES_PROPERTY or raises the existing
%      singleton*.
%
%      H = AXES_PROPERTY returns the handle to a new AXES_PROPERTY or the handle to
%      the existing singleton*.
%
%      AXES_PROPERTY('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in AXES_PROPERTY.M with the given input arguments.
%
%      AXES_PROPERTY('Property','Value',...) creates a new AXES_PROPERTY or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before axes_property_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to axes_property_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help axes_property

% Last Modified by GUIDE v2.5 21-Oct-2010 17:01:40

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @axes_property_OpeningFcn, ...
                   'gui_OutputFcn',  @axes_property_OutputFcn, ...
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
% End initialization code - DO NOT EDIT


% --- Executes just before axes_property is made visible.
function axes_property_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to axes_property (see VARARGIN)

% Choose default command line output for axes_property
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes axes_property wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = axes_property_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in data_length.
function data_length_Callback(hObject, eventdata, handles)
% hObject    handle to data_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
val =get(hObject,'Value');
ha.data_length=(val*1000);
% Hints: contents = get(hObject,'String') returns data_length contents as cell array
%        contents{get(hObject,'Value')} returns selected item from data_length


% --- Executes during object creation, after setting all properties.
function data_length_CreateFcn(hObject, eventdata, handles)
% hObject    handle to data_length (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
set(hObject,'Value',ha.data_length/1000);
% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
contents = get(hObject,'String');
str=contents{get(hObject,'Value')};
ha.line_style = str(2:find(str==')')-1);
plot(ha.handle,ha.pdata,[ha.line_style,ha.line_marker,ha.line_color],'linewidth',ha.line_width);
% Hints: contents = get(hObject,'String') returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2


% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
line_style_table={'-',':','-.','--',' '};
for i=1:length(line_style_table)
    if strcmp(ha.line_style,line_style_table{i})
        break;
    end
end
set(hObject,'Value',i);
% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu3.
function popupmenu3_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
contents = get(hObject,'String');
str=contents{get(hObject,'Value')};
ha.line_marker = str(2:find(str==')')-1);
plot(ha.handle,ha.pdata,[ha.line_style,ha.line_marker,ha.line_color],'linewidth',ha.line_width);
% Hints: contents = get(hObject,'String') returns popupmenu3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu3


% --- Executes during object creation, after setting all properties.
function popupmenu3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
line_marker_table={' ','.','x','+','*','s','d','v','^','<','>','p','h'};
for i=1:length(line_marker_table)
    if strcmp(ha.line_marker,line_marker_table{i})
        break;
    end
end
set(hObject,'Value',i);

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu4.
function popupmenu4_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
contents = get(hObject,'String');
str=contents{get(hObject,'Value')};
ha.line_color = str(2:find(str==')')-1);
plot(ha.handle,ha.pdata,[ha.line_style,ha.line_marker,ha.line_color],'linewidth',ha.line_width);
% Hints: contents = get(hObject,'String') returns popupmenu4 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu4


% --- Executes during object creation, after setting all properties.
function popupmenu4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
line_color_table={'b','g','r','c','m','y','b','w'};
for i=1:length(line_color_table)
    if strcmp(ha.line_color,line_color_table{i})
        break;
    end
end
set(hObject,'Value',i);
% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in xlim.
function xlim_Callback(hObject, eventdata, handles)
% hObject    handle to xlim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
index = get(hObject,'value');
if index ==2
    set(handles.x_man,'Visible','on');
else
    set(handles.x_man,'Visible','off');
    ha.xlim='auto';
end
xlim(ha.handle,ha.xlim);
% Hints: contents = get(hObject,'String') returns xlim contents as cell array
%        contents{get(hObject,'Value')} returns selected item from xlim


% --- Executes during object creation, after setting all properties.
function xlim_CreateFcn(hObject, eventdata, handles)
% hObject    handle to xlim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
if strcmp(ha.xlim,'auto')
    i=1;
else
    i=2;
    str = get(hObject,'String');
    str{2}=[num2str(ha.xlim(1)),',',num2str(ha.xlim(2))];
    set (hObject ,'String',str);
end
set(hObject,'Value',i);
% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function x_man_Callback(hObject, eventdata, handles)
% hObject    handle to x_man (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
str = get(hObject,'String');
str2 = get(handles.xlim,'String');
try
   x =  strread(str,'','delimiter',',');
    if  length(x)==2
        str2{2}=str;
        ha.xlim=x;
    else
        set (handles.xlim,'value',1);
        str2{2}='mannul';
        ha.xlim='auto';
    end
catch
     set (handles.xlim,'value',1);
      str2{2}='mannul';
      ha.xlim='auto';
end
xlim(ha.handle,ha.xlim);
set(hObject,'String','');
set(hObject,'Visible','off');
set (handles.xlim,'String',str2);
% Hints: get(hObject,'String') returns contents of x_man as text
%        str2double(get(hObject,'String')) returns contents of x_man as a double


% --- Executes during object creation, after setting all properties.
function x_man_CreateFcn(hObject, eventdata, handles)
% hObject    handle to x_man (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function y_man_Callback(hObject, eventdata, handles)
% hObject    handle to y_man (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
str = get(hObject,'String');
str2 = get(handles.ylim,'String');
try
   y =  strread(str,'','delimiter',',');
   if  length(y)==2
        str2{2}=str;
        ha.ylim=y;
    else
        set (handles.xlim,'value',1);
        str2{2}='mannul';
        ha.ylim='auto';
    end
catch
     set (handles.ylim,'value',1);
      str2{2}='mannul';
      ha.ylim='auto';
end
ylim(ha.handle,ha.ylim);
set(hObject,'String','');
set(hObject,'Visible','off');
set (handles.ylim,'String',str2);

% Hints: get(hObject,'String') returns contents of y_man as text
%        str2double(get(hObject,'String')) returns contents of y_man as a double


% --- Executes during object creation, after setting all properties.
function y_man_CreateFcn(hObject, eventdata, handles)
% hObject    handle to y_man (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in ylim.
function ylim_Callback(hObject, eventdata, handles)
% hObject    handle to ylim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
index = get(hObject,'value');
if index ==2
    set(handles.y_man,'Visible','on');
else
    set(handles.y_man,'Visible','off');
    ha.ylim='auto';
end
ylim(ha.handle,ha.ylim);
% Hints: contents = get(hObject,'String') returns ylim contents as cell array
%        contents{get(hObject,'Value')} returns selected item from ylim


% --- Executes during object creation, after setting all properties.
function ylim_CreateFcn(hObject, eventdata, handles)
% hObject    handle to ylim (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
if strcmp(ha.xlim,'auto')
    i=1;
else
    i=2;
    str = get(hObject,'String');
    str{2}=[num2str(ha.xlim(1)),',',num2str(ha.xlim(2))];
    set (hObject ,'String',str);
end
set(hObject,'Value',i);
% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
try
    val=strread(get(hObject,'String'));
    ha.line_width = val;
    plot(ha.handle,ha.pdata,[ha.line_style,ha.line_marker,ha.line_color],'linewidth',ha.line_width);
catch
    set(hObject,'String',num2str(ha.line_width));
end
% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
set(hObject,'String',num2str(ha.line_width));
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
ha.xlabel = get(hObject,'String');
xlabel(ha.handle,ha.xlabel)
% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
set(hObject,'String',ha.xlabel);
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global ha;
ha.ylabel = get(hObject,'String');
ylabel(ha.handle,ha.ylabel)
% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double


% --- Executes during object creation, after setting all properties.
function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha;
set(hObject,'String',ha.ylabel);
% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu8.
function popupmenu8_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popupmenu8 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu8


% --- Executes during object creation, after setting all properties.
function popupmenu8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



% --- Executes on button press in radiobutton2.
function radiobutton2_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    global ha;
    set(handles.radiobutton2,'Value',1);
    set(handles.radiobutton3,'Value',0);
    ha.sgn=1;
    data_process();
% Hint: get(hObject,'Value') returns toggle state of radiobutton2


% --- Executes on button press in radiobutton3.
function radiobutton3_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    global ha;
    set(handles.radiobutton3,'Value',1);
    set(handles.radiobutton2,'Value',0);
    ha.sgn=0;
     data_process();
% Hint: get(hObject,'Value') returns toggle state of radiobutton3


% --- Executes during object creation, after setting all properties.
function radiobutton2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to radiobutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha
set(hObject,'Value',ha.sgn);


% --- Executes during object creation, after setting all properties.
function radiobutton3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to radiobutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
global ha
set(hObject,'Value',~ha.sgn);

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
    xlabel(ha.handle,ha.xlabel);
    ylabel(ha.handle,ha.ylabel);
end

