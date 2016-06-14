%plots starting, observed and inverted seismograms for one source and
%receiver and x-, y- and z-component
%Input: binary format


nt=1200; dt=0.00005;
nrec=169;
tracenum=50;

file_inp1='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/cal_toy_vx_it1.bin.shot4'; %starting data
file_inp4='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/obs_toy_vx_it1.bin.shot4_lp320Hz'; %observed data
file_inp7='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/cal_toy_vx_it60.bin.shot4'; % inverted data

file_inp2='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/cal_toy_vy_it1.bin.shot4';
file_inp5='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/obs_toy_vy_it1.bin.shot4_lp320Hz';
file_inp8='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/cal_toy_vy_it60.bin.shot4';

file_inp3='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/cal_toy_vz_it1.bin.shot4';
file_inp6='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/obs_toy_vz_it1.bin.shot4_lp320Hz';
file_inp9='/data14/sdunkl/3DAWAIT/trunk_JURECA/results_toy/su/cal_toy_vz_it60.bin.shot4';

fig=55;
%--------------------------------------------------------------------------
t=dt:dt:nt*dt;

SEIS=binread(file_inp1,nt,nrec);
trace1=SEIS(:,tracenum);
SEIS=binread(file_inp2,nt,nrec);
trace2=SEIS(:,tracenum);
SEIS=binread(file_inp3,nt,nrec);
trace3=SEIS(:,tracenum);

SEIS=binread(file_inp4,nt,nrec);
trace4=SEIS(:,tracenum);
SEIS=binread(file_inp5,nt,nrec);
trace5=SEIS(:,tracenum);
SEIS=binread(file_inp6,nt,nrec);
trace6=SEIS(:,tracenum);

SEIS=binread(file_inp7,nt,nrec);
trace7=SEIS(:,tracenum);
SEIS=binread(file_inp8,nt,nrec);
trace8=SEIS(:,tracenum);
SEIS=binread(file_inp9,nt,nrec);
trace9=SEIS(:,tracenum);



figure(fig)
%plot(t,trace3/max(trace6),'b-','LineWidth',1);
hold on
plot(t,trace6/max(trace6),'k-','LineWidth',1);
hold on
plot(t,trace9/max(trace6),'r-','LineWidth',1);
hold on
%plot(t,(trace2/max(trace6))+2.4,'b-','LineWidth',1);
hold on
plot(t,(trace5/max(trace6))+2.4,'k-','LineWidth',1);
hold on
plot(t,(trace8/max(trace6))+2.4,'r-','LineWidth',1);
hold on
%plot(t,trace1/max(trace6)+4.8,'b-','LineWidth',1);
hold on
plot(t,trace4/max(trace6)+4.8,'k-','LineWidth',1);
hold on
plot(t,trace7/max(trace6)+4.8,'r-','LineWidth',1);

xlim([0.015 0.05]);
xlabel('time (s)');
ylabel('normalized amplitude');
set(get(gca,'Ylabel'),'FontSize',12);
set(get(gca,'Ylabel'),'FontWeight','normal');
set(get(gca,'Xlabel'),'FontSize',12);
set(get(gca,'Xlabel'),'FontWeight','normal');
set(gca,'FontSize',12);
set(gca,'FontWeight','normal');
set(gca,'Linewidth',1.0);




%find rec, source position:
%SU=su2matlab('/data14/sdunkl/toy/results1/su/cal_toynew_vy_it43.su.shot3')
%recx=SU(tracenum).gx
%recy=SU(tracenum).gx
%soux=SU(tracenum).sx
%souy=SU(tracenum).sy
