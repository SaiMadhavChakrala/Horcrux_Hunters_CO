import tkinter as tk
from tkinter import ttk
import pandas as pd
import subprocess
class DataFrameGUI(tk.Tk):
    def __init__(self, dataframe):
        super().__init__()

        self.title("DataFrame GUI")
        self.tree = ttk.Treeview(self, columns=list(dataframe.columns), show="headings")
        for column in dataframe.columns:
            self.tree.heading(column, text=column)
            self.tree.column(column, width=120, anchor=tk.CENTER) 

        for i, row in dataframe.iterrows():
            self.tree.insert("", "end", values=tuple(row))

        vsb = ttk.Scrollbar(self, orient="vertical", command=self.tree.yview)
        self.tree.configure(yscrollcommand=vsb.set)
        vsb.pack(side="right", fill="y")
        self.tree.pack(pady=20, padx=20)


        screen_height = self.winfo_screenheight()
        self.geometry(f"800x{int(screen_height * 0.8)}") 

if __name__ == "__main__":
    myindex = ["Register Name", "Register Value"]
    mycolumns = list(range(32))

    subprocess.run(["g++", "main.cpp", "-o", "main"])
    subprocess.run(["./main"])
    with open("./output.txt", "r") as file:
        content = file.read()
        print("Output from C++ program:", content)


    mydata = [["x" + str(i) for i in range(32)],content.split()]
    
    df = pd.DataFrame(data=mydata, index=myindex, columns=mycolumns)
    df = df.transpose()

    root = tk.Tk()
    root.title("DataFrame GUI")

    tree = ttk.Treeview(root, columns=list(df.columns), show='headings')

    for col in df.columns:
        tree.heading(col, text=col)

    for index, row in df.iterrows():
        tree.insert("", "end", values=list(row))

    tree["height"] = len(df)

    vsb = ttk.Scrollbar(root, orient="vertical", command=tree.yview)
    tree.configure(yscrollcommand=vsb.set)
    vsb.pack(side="right", fill="y")

    for col in df.columns:
        tree.column(col, anchor='center')

    tree.pack()
    root.mainloop()