import tkinter as tk
from tkinter import ttk
import subprocess

# Run the C++ code to generate data.txt
subprocess.run(["./main"])

# Read data from the file
data = []
with open("data.txt", "r") as file:
    for line in file:
        values = list(map(int, line.split()))
        data.extend(values)

# Create and display the table GUI
def create_table(data):
    root = tk.Tk()
    root.title("Table GUI Example")

    tree = ttk.Treeview(root)

    columns = ["Column 1"]

    tree["columns"] = columns
    for col in columns:
        tree.column(col, anchor="center")
        tree.heading(col, text=col)

    for value in data:
        tree.insert("", "end", values=(value,))

    tree.pack(expand=True, fill="both")

    root.mainloop()

# Create and display the table GUI
create_table(data)
