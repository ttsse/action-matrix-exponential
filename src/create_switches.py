import re

file = open('thetatemp.cpp',mode = 'r')
thetafile = file.read()
file.close()
filewrite = open('thetatemp.cpp', mode = 'w')

i = 2

functionname = 'theta_half_prec'

thetafilenew = 'double '+functionname+'(int m)\n{\nswitch(m)\n{\n    case 1:\n        return ';

for j in range(len(thetafile)):
    if (re.match('\s',thetafile[j])):
        thetafilenew += ';\n        break;\n    case '+str(i)+':\n        return '
        i += 1
    else:
        thetafilenew += thetafile[j]

thetafilenew += ';\n        break;\n}\n}'

filewrite.write(thetafilenew)
filewrite.close()

#\n        break;\n    case *:\n        return 