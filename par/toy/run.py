#!/usr/bin/python
import os
import sys
import shutil
import json
rm_dirs = ['grad', 'hess', 'su', 'su_obs']
mk_dirs = ['log', 'model']
files = ['*.json', 'bsub.out']

def init():
  for f in (rm_dirs + mk_dirs):
    if os.path.exists(f):
      shutil.rmtree(f)
      os.mkdir(f)
    else:
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

if len(sys.argv) == 2 and sys.argv[1] == '-c':
  clean()
  exit()

exe="../../bin/ifos3d"
init()
compile('../../libcseife/', '')
compile('../../', 'model_scr=hh_toy_true.c')
param = read_json('fw.json')

run(bsub_x86(queue="q_x86_share", np=int(param['NPROCX'])*int(param['NPROCY'])*int(param['NPROCZ']), job='toy', prog=exe), param)

shutil.copy('model/%s.vs_it0' % param['PREFIX'], 'model/%s.vs.true' % param['PREFIX'])
shutil.copy('model/%s.vp_it0' % param['PREFIX'], 'model/%s.vp.true' % param['PREFIX'])
shutil.copy('model/%s.rho_it0' % param['PREFIX'], 'model/%s.rho.true' % param['PREFIX'])

compile('../../libcseife', '')
compile('../../', 'model_scr=hh_toy_true.c')
param = read_json('inv.json')

run(bsub_x86(queue="q_x86_share", np=int(param['NPROCX'])*int(param['NPROCY'])*int(param['NPROCZ']), job='toy', prog=exe), param)
