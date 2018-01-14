# -*- coding:utf-8 -*-

import os
import sys
origin = sys.argv[1]
new = sys.argv[2]
origin, new = '.' + origin, '.' + new
# 列出当前目录下所有的文件
files = os.listdir(".")
if origin == '.':
    for filename in files:
        portion = os.path.splitext(filename)
        newname = portion[0] + new  
        os.rename(filename,newname)
else:
    for filename in files:
        portion = os.path.splitext(filename)
        if portion[1] == origin:
            newname = portion[0] + new
            os.rename(filename,newname)
