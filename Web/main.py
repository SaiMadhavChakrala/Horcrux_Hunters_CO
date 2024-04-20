from flask import Flask, render_template, request, redirect, url_for
import subprocess
import pandas as pd
app = Flask(__name__)
print(app)
print("HI")

alias = ["zero","ra","sp","gp","tp","t0","t1","t2","s0","s1","a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","t3","t4","t5","t6","t7","t8"]

out =[]
for i in range(32):
    out.append({'Register':"x"+str(i),'Alias':alias[i],'Core_1':0,'Core_2':0})

Core_one =""
Core_two =""

with open('Testfile[1].txt', 'r') as file:
    # Read the entire contents of the file into a string
    Core_one = file.read() 
with open('Testfile[2].txt', 'r') as file:
    # Read the entire contents of the file into a string
    Core_two = file.read() 

Core_one ="HI"
blockSize = 16
numBlocks = 32
assoc = 32
nSets = 1
missLatency = 1
policy = "option1"
dataforwarding="option1"
data1 = {'A': range(100), 'B': range(100)}
df = pd.DataFrame(data1)
df2 = pd.DataFrame(data1)
left=["1"]
right=["1"]
middle=[]
middle2=[]
middle3=[]
c1=""
c2=""
np=""

@app.route("/", methods=['GET', 'POST'])
def page1():
    if request.method == 'POST':
        with open('Testfile[1].txt', 'r') as file:
            # Read the entire contents of the file into a string
            Core_one = file.read() 
        with open('Testfile[2].txt', 'r') as file:
            # Read the entire contents of the file into a string
            Core_two = file.read() 
        # Core_one ="HI"    
        blockSize = 16
        numBlocks = 32
        assoc = 32
        nSets = 1
        missLatency = 1
        policy = "option1"
        dataforwarding="option1"
        Core_one = Core_one.replace('\r\n', '\n')
        Core_one = Core_one.strip()
        data1 = {'A': range(100), 'B': range(100)}
        df = pd.DataFrame(data1)
        df2 = pd.DataFrame(data1)
        return render_template('index.html',Core_one = Core_one,Core_two = Core_two,blockSize=blockSize,numBlocks=numBlocks,assoc=assoc,nSets=nSets,missLatency=missLatency,policy=policy,dataforwarding=dataforwarding,df=df,out=out,df2=df2,middle=middle,middle2=middle2,middle3=middle3,c1=c1,c2=c2,np=np)
    else:
        with open('Testfile[1].txt', 'r') as file:
            # Read the entire contents of the file into a string
            Core_one = file.read() 
        with open('Testfile[2].txt', 'r') as file:
            # Read the entire contents of the file into a string
            Core_two = file.read() 

        Core_one = Core_one.replace('\r\n', '\n')
        Core_one = Core_one.lstrip()
        blockSize = 16
        numBlocks = 32
        assoc = 32
        nSets = 1
        missLatency = 1
        policy = "option1"
        dataforwarding="option1"
        data1 = {'Ins/Clock': range(1), 'Unnamed': range(1)}
        df = pd.DataFrame(data1)
        df2 = pd.DataFrame(data1)
        return render_template('index.html',Core_one = Core_one,Core_two = Core_two,blockSize=blockSize,numBlocks=numBlocks,assoc=assoc,nSets=nSets,missLatency=missLatency,policy=policy,dataforwarding=dataforwarding,df=df,out=out,df2=df2,middle=middle,middle2=middle2,middle3=middle3,c1=c1,c2=c2,np=np)
    


@app.route('/index', methods=['POST','PUT'])
def update_data():

    Core_one = request.form['input1']
    Core_two = request.form['input2']
    blockSize = request.form['bs']
    numBlocks = request.form['nb']
    assoc = request.form['as']
    nSets = request.form['ns']
    missLatency = request.form['ml']
    dataforwarding =  request.form.get('dataforwarding')
    print(dataforwarding)
    policy=request.form.get('policy')
    input2 = request.form['input2']
    input = request.form['input1']
    
    with open("Testfile[1].txt", "w") as f:
        input = input.replace('\r\n', '\n')
        input = input.lstrip()
        f.write(input)
        print(input)


    with open("Testfile[2].txt", "w") as f:
        input2 = input2.replace('\r\n', '\n')
        input2 = input2.lstrip()
        f.write(input2)
        print(input2)

    with open("cache_df.txt","w") as f:
        f.write(blockSize + "\n")
        f.write(numBlocks + "\n")
        f.write(assoc + "\n")
        f.write(nSets + "\n")
        f.write(missLatency + "\n")

        if dataforwarding == "option1":
            f.write("0" + "\n")
        else:
            f.write("1" + "\n")
            
        if policy == "option1":
            f.write("0" + "\n")
        else:
            f.write("1" + "\n")

        # f.write(policy + "\n")
        
    subprocess.run(["g++", "main.cpp", "-o", "compiled_cpp_file"])
    subprocess.run(["./compiled_cpp_file"])
    df=pd.read_csv('./out1.csv')
    df2=pd.read_csv('./out2.csv')

    Core_one=input
    filename = "output.txt"
    lines = read_file_to_list(filename)
    filename2 = "data.txt"
    lines2 = read_file_to_list(filename2)
    lines3 = read_file_to_list("out.txt")
    lines4 = lines3[38:42]
    left=[]
    right=[]
    print("HII")
    for x in lines4:
        left.append(x[:21])
        print(x[:21])
        right.append(x[22:])
    
    middle=[]
    for x in range(len(left)):
        middle.append({'left':left[x],'right':right[x]})


    lines4 = lines3[45:49]
    left=[]
    right=[]
    print("HII")
    for x in lines4:
        left.append(x[:21])
        print(x[:21])
        right.append(x[22:])
    
    middle2=[]
    for x in range(len(left)):
        middle2.append({'left':left[x],'right':right[x]})


    lines4 = lines3[52:55]
    left=[]
    right=[]
    print("HII")
    for x in lines4:
        left.append(x[:21])
        print(x[:21])
        right.append(x[22:])
    
    middle3=[]
    for x in range(len(left)):
        middle3.append({'left':left[x],'right':right[x]})

    c1 = "Core 1"
    c2 = "Core 2"
    np = "Net Program"
    out =[]
    for i in range(32):
        out.append({'Register':"x"+str(i),'Alias':alias[i],'Core_1':lines[i],'Core_2':lines2[i]})

    return render_template('index.html',Core_one = Core_one,Core_two = Core_two,blockSize=blockSize,numBlocks=numBlocks,assoc=assoc,nSets=nSets,missLatency=missLatency,policy=policy,dataforwarding=dataforwarding,df=df,out=out,df2=df2,middle=middle,middle2=middle2,middle3=middle3,c1=c1,c2=c2,np=np)
        

def read_file_to_list(filename):
  """Reads all lines from a text file into a list.

  Args:
      filename: The path to the text file.

  Returns:
      A list of strings, where each element is a line from the file.
  """

  with open(filename, 'r') as f:
    lines = f.readlines()

  # Remove trailing newline characters from each line
  lines = [line.rstrip() for line in lines]
  return lines


if __name__ == '__main__':
    app.run()