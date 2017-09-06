#!/usr/bin/python
import os
import sys
#help
if len(sys.argv) < 3 or (len(sys.argv) == 3 and (sys.argv[2][0] != 'n' or sys.argv[2][2] != '=')) or (len(sys.argv) == 4 and (sys.argv[2][0] != 'n' or sys.argv[2][2] != '=')):
  print 'Usage: ./draw.py in_file n1=%d [n2=%d]'
  print 'Example: ./draw.py toy.vp_it60 n1=68 n2=32'
  exit()

#arguments
prefix='toy'
rsf_file=prefix+'.rsf'
vpl_file=prefix+'.vpl'
title="VP"
label1="Depth"
label2="Distance"
unit1="m"
unit2="m"
n1=184  #y
n2=160  #x
n3=160  #z
in_file=sys.argv[1]

#create rsf file 
crt_com='sfmath n1=%d n2=%d n3=%d output=0 > %s' % (n1, n2, n3, rsf_file)
sub_com='sed -i "s/in=.*/in=%s/g" %s' % (in_file, rsf_file)
os.popen(crt_com)
os.popen(sub_com)

#get average bias
avg_com="sfattr want=mean < %s | awk '{print $3}'" % (rsf_file)
mean=float(os.popen(avg_com).read().strip())

#sfwindow and sfgrey
index1=int(sys.argv[2][1])
first1=int(sys.argv[2][3:])
pen=''
if len(sys.argv) == 3:
  win_com='sfwindow f%d=%d n%d=1 < %s' % (index1, first1, index1, rsf_file)
  plot_com='sfgrey color=j title=%s label1=%s label2=%s unit1=%s unit2=%s bias=%d scalebar=y barreverse=y > %s' % (title, label1, label2, unit1, unit2, mean, vpl_file)
  pen_com='sfpen %s' % (vpl_file)
  t_com = '%s | %s' % (win_com, plot_com)
  os.popen(t_com)
elif len(sys.argv) == 4:
  index2=int(sys.argv[3][1])
  first2=int(sys.argv[3][3:])
  win_com='sfwindow f%d=%d n%d=1 f%d=%d n%d=1 < %s' % (index1, first1, index1, index2, first2, index2, rsf_file)
  plot_com='sfgraph title="%s" dash=0 plotfat=5  grid=y yreverse=n > %s' % (title, vpl_file)
  pen_com='sfpen %s' % (vpl_file)
  t_com = '%s | %s' % (win_com, plot_com)
  os.popen(t_com)

#sfpen
os.popen(pen_com)
