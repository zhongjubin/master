function start_com()
clear;clc;close all hidden; 
global ha
ha.data_length = 1000;
ha.data= [];
ha.line_style = '-';
ha.line_marker = ' ';
ha.line_color = 'b';
ha.line_width =1.0;
ha.xlim = 'auto';
ha.ylim = 'auto';
ha.sgn=1;
ha.byte_num=2;
ha.pdata = [];
ha.xlabel = 'value';
ha.ylabel = 'num';
ha.plot_flag =1;
ha.hex_disp =1;
ha.hex_send =0;
ha.auto_send =0;
ha.auto_time =1000;
ha.stop_disp =0;
ha.self_cur = 0;
ha.save_flag = 0;
ha.save_name = 'rec.dat';
ha.fid=[];
ha.com=3;
serial_communication;