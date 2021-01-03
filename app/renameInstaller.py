###################################################
#
#                   RenameInstaller.py
#
# 
#
# Created: Dec 2020
# by: Marcelo Varanda
#
# Copyrights: Varanda Labs Inc.
#
# RenameInstaller adds release version to the installer file
# Note: supposed to be called from project app dir
#
###################################################


import sys,os

INSTALLER_VERSION_FILENAME = "version.h"
INSTALLER_VERSION_TOKEN = "AuTyperVersion"
installer_files = ["AuTyperInstaller.exe"]

releaseDir = ".\\installers"

def rename(ver_file, token, files):
  ver = None
  fh = open(ver_file)
  if fh == None:
    print("Could not find version file")
    sys.exit(1)
  while True:
    # Read next line
    line = fh.readline()
    # If line is blank, then you struck the EOF
    if not line :
      break;
    if line.find(token) >= 0:
      line = line.replace('\"', '')
      s = line.split()
      ver = s[2].split('.')
      break;
  fh.close()
  if ver == None:
    print("Could not find version number")
    sys.exit(1)
    
  #tail = ".%.3d.%.3d.%.3d." % (int(ver[0]), int(ver[1]), int(ver[2]))
  tail = ".%d.%d.%d." % (int(ver[0]), int(ver[1]), int(ver[2]))
  for name in files:
    ns = name.split('.') # Note: assume file name with a single .
    new_name = releaseDir + "\\" + ns[0] + tail + ns[1]
    old_name = releaseDir + "\\" +name
    print("renaming %s to %s" % (old_name, new_name))
    os.rename(old_name, new_name)
    
if __name__ == "__main__":
  rename(INSTALLER_VERSION_FILENAME, INSTALLER_VERSION_TOKEN, installer_files)

  print("rename done")