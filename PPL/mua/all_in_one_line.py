f = open('Main.java','r')
data = f.read()
lines = data.split('\n')
lines = [l for l in lines if not l.strip().startswith('//')]
s = ''
for line in lines:
    s += line.strip() + ' '
g = open('out.java', 'w')
print(s,file=g)
