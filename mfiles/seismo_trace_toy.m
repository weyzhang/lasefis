%plots starting, observed and inverted seismograms for one source and
%receiver and x-, y- and z-component
%Input: binary format
clear all; clc;


tracenum=50;

file_inp1='../par/su/cal_toy_vx_it1.su.shot4'; % initial data
file_inp4='../par/su_obs/obs_toy_vx_it1.su.shot4'; %observed data
file_inp7='../par/su/cal_toy_vx_it60.su.shot4'; % inverted data

file_inp2='../par/su/cal_toy_vy_it1.su.shot4';
file_inp5='../par/su_obs/obs_toy_vy_it1.su.shot4';
file_inp8='../par/su/cal_toy_vy_it60.su.shot4';

file_inp3='../par/su/cal_toy_vz_it1.su.shot4';
file_inp6='../par/su_obs/obs_toy_vz_it1.su.shot4';
file_inp9='../par/su/cal_toy_vz_it60.su.shot4';


tr1 = su2matlab(file_inp1);
tr2 = su2matlab(file_inp2);
tr3 = su2matlab(file_inp3);
tr4 = su2matlab(file_inp4);
tr5 = su2matlab(file_inp5);
tr6 = su2matlab(file_inp6);
tr7 = su2matlab(file_inp7);
tr8 = su2matlab(file_inp8);
tr9 = su2matlab(file_inp9);



nt = tr1.ns; % number of time samples
dt = tr1.dt; % sample interval in micro-seconds
ns = tr1.ns; % number of samples per trace


fig=55;
%--------------------------------------------------------------------------



trace1=tr1(1).trace;
trace2=tr2(1).trace;
trace3=tr3(1).trace;
trace4=tr4(1).trace;
trace5=tr5(1).trace;
trace6=tr6(1).trace;
trace7=tr7(1).trace;
trace8=tr8(1).trace;
trace9=tr9(1).trace;



t=(dt:dt:ns*dt)./10^6; % time in seconds

figure(fig)
subplot(1,2,1) 

plot(t,trace1/max(trace6)+4.8,'b-','LineWidth',1.5);
hold on
plot(t,trace4/max(trace6)+4.8,'k-','LineWidth',1.5);
hold on
plot(t,(trace2/max(trace6))+2.4,'b-','LineWidth',1.5);
hold on
plot(t,(trace5/max(trace6))+2.4,'k-','LineWidth',1.5);
hold on
plot(t,trace3/max(trace6),'b-','LineWidth',1.5);
hold on
plot(t,trace6/max(trace6),'k-','LineWidth',1.5);

xlabel('time in s');
xlim([0.015 0.05]);
ylabel('normalized amplitude');
ylim([-2 7]);
set(gca,'ytick',[])

set(get(gca,'Ylabel'),'FontSize',12);
set(get(gca,'Ylabel'),'FontWeight','normal');
set(get(gca,'Xlabel'),'FontSize',12);
set(get(gca,'Xlabel'),'FontWeight','normal');
set(gca,'FontSize',12);
set(gca,'FontWeight','normal');
set(gca,'Linewidth',1.0);

legend('starting','observed','Location','NorthWest');

txt1 = 'x-component';
text(0.04,5.2,txt1);
txt2 = 'y-component';
text(0.04,2.7,txt2);
txt3 = 'z-component';
text(0.04,0.3,txt3);


subplot(1,2,2) 
plot(t,trace4/max(trace6)+4.8,'k-','LineWidth',1.5);
hold on
plot(t,trace7/max(trace6)+4.8,'r-','LineWidth',1.5);
hold on
plot(t,(trace5/max(trace6))+2.4,'k-','LineWidth',1.5);
hold on
plot(t,(trace8/max(trace6))+2.4,'r-','LineWidth',1.5);
hold on
plot(t,trace6/max(trace6),'k-','LineWidth',1.5);
hold on
plot(t,trace9/max(trace6),'r-','LineWidth',1.5);

xlabel('time in s');
xlim([0.015 0.05]);
ylabel('normalized amplitude');
ylim([-2 7]);
set(get(gca,'Ylabel'),'FontSize',12);
set(get(gca,'Ylabel'),'FontWeight','normal');
set(get(gca,'Xlabel'),'FontSize',12);
set(get(gca,'Xlabel'),'FontWeight','normal');
set(gca,'FontSize',12);
set(gca,'FontWeight','normal');
set(gca,'Linewidth',1.0);
set(gca,'ytick',[]);
hleg1 = legend('observed','inverted','Location', 'NorthWest');

txt1 = 'x-component';
text(0.04,5.2,txt1);
txt2 = 'y-component';
text(0.04,2.7,txt2);
txt3 = 'z-component';
text(0.04,0.3,txt3);








% find rec, source position:
% SU=su2matlab('/data14/sdunkl/toy/results1/su/cal_toynew_vy_it43.su.shot3')
% recx=SU(tracenum).gx
% recy=SU(tracenum).gx
% soux=SU(tracenum).sx
% souy=SU(tracenum).sy
