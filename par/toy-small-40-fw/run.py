#!/usr/bin/python
import os
import sys
import shutil
import json
rm_dirs = ['grad', 'hess', 'su', 'su_obs']
mk_dirs = ['model', 'log']
FW_JSON = 'fw.json'
INV_JSON = 'inv.json'
files = [FW_JSON, INV_JSON, 'bsub.out']

def init():
  for f in rm_dirs:
    if os.path.exists(f):
      shutil.rmtree(f)
      os.mkdir(f)
    else:
      os.mkdir(f)
  for f in mk_dirs:
    if not os.path.exists(f):
      os.mkdir(f)

def clean():
  for f in rm_dirs:
    if os.path.exists(f):
      shutil.rmtree(f)
  for f in files:
    if os.path.exists(f):
      os.system("rm -f %s" % f)

def read_json(json_file):
  with open(json_file) as f:
    data = json.load(f)
    data['JSON_FILE'] = json_file
    return data

def compile(path, para):# {{{
  cmd = "scons -C %s %s -j8" % (path, para)
  print cmd
  os.system(cmd)
# }}}  

def bsub_x86(queue, np, job, prog):# {{{
  cmd = "/usr/sw-mpp/bin/bsub -I -q %s -n %d -o bsub.out -J %s %s" % (queue, np, job, prog)
  return cmd
# }}}
def bsub_sw(queue, np, job, prog):# {{{
  cmd="/usr/sw-mpp/bin/bsub -I -b -m 1 -p -q %s -host_stack 1024 -share_size 5000 -n %d -cgsp 64 -o bsub.out -J %s %s" % (queue, np, job, prog)
  return cmd
# }}}
def run(submit_cmd, param):# {{{
  cmd = submit_cmd.rstrip() + '''\
    %s | tee %s
    ''' % (param['JSON_FILE'], param['LOG_FILE'])
  print cmd
  os.system(cmd)
# }}}

if '-c' in sys.argv:
  clean()
  exit()

exe="../../bin/ifos3d"
if 'fw' in sys.argv:
  init()
  compile('../../libcseife/', '')
  compile('../../', '')
  param = read_json(FW_JSON)

  run(bsub_x86(queue="q_x86_expr", np=int(param['NPROCX'])*int(param['NPROCY'])*int(param['NPROCZ']), job='toy', prog=exe), param)

  #shutil.copy('model/%s.vs_it0' % param['PREFIX'], 'model/%s.vs.true' % param['PREFIX'])
  #shutil.copy('model/%s.vp_it0' % param['PREFIX'], 'model/%s.vp.true' % param['PREFIX'])
  #shutil.copy('model/%s.rho_it0' % param['PREFIX'], 'model/%s.rho.true' % param['PREFIX'])

elif 'inv' in sys.argv:
  compile('../../libcseife', '')
  compile('../../', '')
  param = read_json(INV_JSON)

  run(bsub_x86(queue="q_x86_expr", np=int(param['NPROCX'])*int(param['NPROCY'])*int(param['NPROCZ']), job='toy', prog=exe), param)
else:
  print 'Usage: ./run.py fw or ./run.py inv'
