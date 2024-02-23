import tkinter as tk
from tkinter import ttk
import pandas as pd
# import subsytem
# Sample DataFrames
data1 = {'Column1': list(range(1, 31)),
         'Column2': [f'A{i}' for i in range(1, 31)]}
df1 = pd.DataFrame(data1)

data2 = {'Column3': list(range(31, 61)),
         'Column4': [f'B{i}' for i in range(1, 31)]}
df2 = pd.DataFrame(data2)

# Create a Tkinter window
root = tk.Tk()
root.title("DataFrame GUI")

# Create the first Treeview widget for the first DataFrame
tree1 = ttk.Treeview(root, columns=list(df1.columns), show='headings')

# Configure column headings for the first DataFrame
for col in df1.columns:
    tree1.heading(col, text=col)

# Insert data into the first Treeview
for index, row in df1.iterrows():
    tree1.insert("", "end", values=list(row))

# Set the height of the rows in the first Treeview
tree1["height"] = len(df1)

# Add a vertical scrollbar for the first Treeview
vsb1 = ttk.Scrollbar(root, orient="vertical", command=tree1.yview)
tree1.configure(yscrollcommand=vsb1.set)

# Pack the first Treeview with padding and towards the center
tree1.place(relx=0.3, rely=0.5, anchor='center')
vsb1.place(relx=0.65, rely=0.5, anchor='center')

vsb1 = ttk.Scrollbar(root, orient="vertical", command=tree1.yview)
tree1.configure(yscrollcommand=vsb1.set)
vsb1.pack(side="right", fill="y")

for col in df1.columns:
    tree1.column(col, anchor='center')
# Create the second Treeview widget for the second DataFrame
tree2 = ttk.Treeview(root, columns=list(df2.columns), show='headings')

# Configure column headings for the second DataFrame
for col in df2.columns:
    tree2.heading(col, text=col)

# Insert data into the second Treeview
for index, row in df2.iterrows():
    tree2.insert("", "end", values=list(row))

# Set the height of the rows in the second Treeview
tree2["height"] = len(df2)

# Add a vertical scrollbar for the second Treeview
vsb2 = ttk.Scrollbar(root, orient="vertical", command=tree2.yview)
tree2.configure(yscrollcommand=vsb2.set)

# Pack the second Treeview with padding and towards the center
tree2.place(relx=0.7, rely=0.5, anchor='center')
vsb2.place(relx=0.95, rely=0.5, anchor='center')


vsb2 = ttk.Scrollbar(root, orient="vertical", command=tree2.yview)
tree2.configure(yscrollcommand=vsb2.set)
vsb2.pack(side="right", fill="y")

for col in df2.columns:
    tree2.column(col, anchor='center')
# Run the Tkinter event loop
root.geometry("800x600")  # Set the window size
root.mainloop()