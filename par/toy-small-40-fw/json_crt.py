#!/usr/bin/python
import os
import json
prefix = "toy"
param_fw = {
  "MODELING PARAMETERS" : "comment",
  "PREFIX" : "%s" % prefix,
  "LOG_FILE" : "log/fw.log",

  "Note that y denotes the vertical direction !" : "comment",

  "Domain Decomposition" : "comment",
        "NPROCX" : "1",
        "NPROCY" : "1",
        "NPROCZ" : "1",

  "3-D Grid" : "comment",
        "NX" : "40",
        "NY" : "46",
        "NZ" : "40",
        "DX" : "3.2",
        "DY" : "3.2",
        "DZ" : "3.2",

  "FD order" : "comment",
        "FDORDER" : "4",
        "FDCOEFF" : "2",

  "Time Stepping" : "comment",
        "TIME" : "0.06",
        "DT" : "1.0e-04",

  "Source" : "comment",
        "SOURCE_SHAPE" : "1",
        "SOURCE_TYPE" : "1",
        "SRCREC" : "1",
        "SOURCE_FILE" : "input/sources.dat",
        "RUN_MULTIPLE_SHOTS" : "1",

  "Model" : "comment",
        "READMOD" : "1",
        "MFILE" : "model/%s.small" % prefix,

  "Q-approximation" : "comment",
        "L" : "0",

  "Free Surface" : "comment",
        "FREE_SURF" : "0",
        

  "Absorbing Boundary" : "comment",
        "ABS_TYPE" : "2",
        "FW" : "10",
		"DAMPING" : "8.0",
		"NPOWER" : "10.0",
		"BOUNDARY" : "1",

  "Snapshots" : "comment",
        "SNAP" : "1",
		"TSNAP1" : "0.02",
		"TSNAP2" : "0.02",
		"TSNAPINC" : "0.01",
		"SNAP_FORMAT" : "3",
		"SNAP_FILE" : "./snap/%s" % prefix,
		"SNAP_PLANE" : "1",

  "Receiver" : "comment",
        "SEISMO" : "1",
        "SAVESU" : "1",
        "READREC" : "2",

  "Receiver array" : "comment",
        "REC_ARRAY" : "1",
        "REC_ARRAY_DEPTH" : "24.0",
        "REC_ARRAY_DIST" : "30.0",
        "DRX" : "1",
        "DRZ" : "1",

  "Seismograms" : "comment",
        "NDT" : "1",
        "SEIS_FORMAT" : "1",
        "SEIS_FILE" : "./su_obs/obs_%s" % prefix,


  "Method" : "comment",
        "METHOD" : "0",
        
        "MOD_OUT_FILE" : "./model/%s" % prefix
}

param_inv = {
  "LOG_FILE" : "log/inv.log",
  "Seismograms" : "comment",
        "SEIS_FILE" : "./su/cal",
        "SAVESU" : "0",

  "Model" : "comment",
		"READMOD" : "1",
		"MFILE" : "model/%s.small.ori" % prefix,

  "Method" : "comment",
        "METHOD" : "1",

  "INVERSION PARAMETERS" : "comment",

  "In- and Output Files" : "comment",
        "GRADMO" : "0",
        "GRAD_FILE" : "./grad/grad",
        "MOD_OUT_FILE" : "./model/%s" % prefix,
        "SEIS_OBS_FILE" : "./su_obs/obs",
        "EXTOBS" : "0",
        "INV_FILE" : "input/workflow.dat",

  "General" : "comment",
        "ITMIN, ITMAX" : "1 , 60",
        "FILT" : "1",
        "NFMAX" : "5",
        "TAST" : "50",
        "VP0, VS0, RHO0" : "6200.0, 3600.0, 2800.0",
        "WEIGHT_VP,WEIGHT_VS,WEIGHT_RHO" : "1.0, 1.0, 0.0",

  "Steplength estimation" : "comment",
        "NSHOTS_STEP" : "2",
        "TESTSTEP" : "0.02",

  "Gradient preconditioning" : "comment",
        "DAMPTYPE" : "2",

  "Hessian" : "comment",
        "HESS" : "0",
   
  "L-BFGS" : "comment",
        "LBFGS" : "0"
}

with open('fw.json', 'w') as json_file:
  json_file.write(json.dumps(param_fw, indent = 1))
param_fw.update(param_inv)  
with open('inv.json', 'w') as json_file:
  json_file.write(json.dumps(param_fw, indent = 1))
