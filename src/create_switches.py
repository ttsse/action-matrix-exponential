import re

file = open('theta.cpp',mode = 'r')
thetafile = file.read()
file.close()
filewrite = open('theta.cpp', mode = 'w')

i = 0

thetafilenew = '#include"expmv.h"\n#include<vector>\n\nstd::vector<double> expmv::get_theta(int m)\n{\nswitch(m)\n{\n    case \'half\':\n    {\n        std::vector<double> theta{'

precisions = ['single', 'double']

for j in range(len(thetafile)):
    if (re.match('[^\S\r\n]',thetafile[j])):
        thetafilenew += ', '
    elif (re.match('\n',thetafile[j])):
        thetafilenew += '};\n        return theta;\n        break;\n    \n}    case \'' + precisions[i] + '\':\n    {\n        std::vector<double> theta{'
        i += 1
    else:
        thetafilenew += thetafile[j]

thetafilenew += '};\n        return theta;\n        break;\n    }\n}\n};'

filewrite.write(thetafilenew)
filewrite.close()

#\n        break;\n    case *:\n        return 