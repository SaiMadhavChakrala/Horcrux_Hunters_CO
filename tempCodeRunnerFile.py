import tkinter as tk
from tkinter import ttk, scrolledtext, filedialog
import subprocess

class MyApp:
    def __init__(self, root):
        self.root = root
        self.root.title("My Cool GUI App")
        self.root.geometry("1200x600")  # Enlarged window size

        # Style configuration
        style = ttk.Style()
        style.configure("TButton", padding=10, font=('Helvetica', 12))

        # Scrolled Text Editor
        self.text_editor = scrolledtext.ScrolledText(self.root, wrap=tk.WORD, width=80, height=15, font=('Arial', 12))
        self.text_editor.place(x=10, y=10)

        # Save Button
        save_button = ttk.Button(self.root, text="Save to Testfile[1].txt", command=self.save_to_file)
        save_button.place(x=20, y=310)

        # Run C++ Button
        run_cpp_button = ttk.Button(self.root, text="Run C++", command=self.run_cpp)
        run_cpp_button.place(x=500, y=310)

        # Text Preview
        self.text_preview = scrolledtext.ScrolledText(self.root, wrap=tk.WORD, width=80, height=10, font=('Arial', 12))
        self.text_preview.place(x=10, y=380)

        # Table
        self.data_table = ttk.Treeview(self.root, columns=('Column1', 'Column2'), show='headings', height=32)
        self.data_table.heading('Column1', text='Column1')
        self.data_table.heading('Column2', text='Column2')

        # Adding sample data, you can replace it with your actual data
        for i in range(32):
            self.data_table.insert("", tk.END, values=(f"Row{i+1} Col1", f"Row{i+1} Col2"))

        # Enlarge the table size and move it to the right
        self.data_table.place(x=750, y=10)

    def save_to_file(self):
        content = self.text_editor.get("1.0", tk.END)
        with open("Testfile[1].txt", 'w') as file:
            file.write(content)

    def run_cpp(self):
        # Save content to Testfile[1].txt before running main.cpp
        self.save_to_file()

        # Assuming main.cpp is in the same directory as this script
        try:
            subprocess.run(["g++", "main.cpp", "-o", "main"], check=True)
            process = subprocess.run(["./main"], capture_output=True, text=True, check=True)
            self.text_preview.delete('1.0', tk.END)
            self.text_preview.insert(tk.END, process.stdout)
        except subprocess.CalledProcessError as e:
            self.text_preview.delete('1.0', tk.END)
            self.text_preview.insert(tk.END, e.stderr)

if __name__ == "__main__":
    root = tk.Tk()
    app = MyApp(root)
    root.mainloop()
