import tkinter as tk
from tkinter import ttk, scrolledtext, filedialog
import subprocess

class MyApp:
    def __init__(self, root):
        self.root = root
        self.root.title("My Cool GUI App")
        self.root.geometry("1200x850")  # Enlarged window size

        # Style configuration
        style = ttk.Style()
        style.configure("TButton", padding=10, font=('Helvetica', 12))

        # Scrolled Text Editor for Testfile[1].txt
        self.text_editor_1 = scrolledtext.ScrolledText(self.root, wrap=tk.WORD, width=80, height=20, font=('Arial', 12))
        self.text_editor_1.place(x=10, y=10)

        # Scrolled Text Editor for Testfile[2].txt
        self.text_editor_2 = scrolledtext.ScrolledText(self.root, wrap=tk.WORD, width=80, height=20, font=('Arial', 12))
        self.text_editor_2.place(x=10, y=470)

        # Save Button for Testfile[1].txt
        save_button_1 = ttk.Button(self.root, text="Save to Testfile[1].txt", command=self.save_to_file_1)
        save_button_1.place(x=20, y=400)

        # Save Button for Testfile[2].txt
        save_button_2 = ttk.Button(self.root, text="Save to Testfile[2].txt", command=self.save_to_file_2)
        save_button_2.place(x=250, y=400)

        # Run C++ Button
        run_cpp_button = ttk.Button(self.root, text="Run C++", command=self.run_cpp)
        run_cpp_button.place(x=520, y=400)

        # Table
        self.data_table = ttk.Treeview(self.root, columns=('Column1', 'Column2'), show='headings', height=32)
        self.data_table.heading('Column1', text='Column1')
        self.data_table.heading('Column2', text='Column2')

        # Adding sample data, you can replace it with your actual data
        for i in range(32):
            self.data_table.insert("", tk.END, values=(f"Row{i+1} Col1", f""))

        # Enlarge the table size and move it to the right
        self.data_table.place(x=750, y=100)

        # Load content from Testfile[1].txt into the first text editor
        self.load_content_into_text_editor_1()

        # Load content from Testfile[2].txt into the second text editor
        self.load_content_into_text_editor_2()

        # Periodically check for updates in output.txt
        self.root.after(1000, self.check_for_updates)

    def check_for_updates(self):
        try:
            with open("output.txt", 'r') as file_output, open("data.txt", 'r') as file_data:
                lines_output = file_output.readlines()
                lines_data = file_data.readlines()

                for i, (line_output, line_data) in enumerate(zip(lines_output, lines_data)):
                    line_output = line_output.strip()
                    line_data = line_data.strip()

                    if i < len(self.data_table.get_children()):
                        self.data_table.set(self.data_table.get_children()[i], column='Column1', value=line_data)
                        self.data_table.set(self.data_table.get_children()[i], column='Column2', value=line_output)
                    else:
                        break
        except FileNotFoundError:
            # Handle the case where the file is not found
            pass

        # Repeat the check after 1000 milliseconds (1 second)
        self.root.after(1000, self.check_for_updates)


    def load_content_into_text_editor_1(self):
        try:
            with open("Testfile[1].txt", 'r') as file:
                content = file.read()
                self.text_editor_1.insert(tk.END, content)
        except FileNotFoundError:
            # Handle the case where the file is not found
            pass

    def load_content_into_text_editor_2(self):
        try:
            with open("Testfile[2].txt", 'r') as file:
                content = file.read()
                self.text_editor_2.insert(tk.END, content)
        except FileNotFoundError:
            # Handle the case where the file is not found
            pass

    def save_to_file_1(self):
        content = self.text_editor_1.get("1.0", tk.END)
        with open("Testfile[1].txt", 'w') as file:
            file.write(content)

    def save_to_file_2(self):
        content = self.text_editor_2.get("1.0", tk.END)
        with open("Testfile[2].txt", 'w') as file:
            file.write(content)

    def run_cpp(self):
        # Save content to Testfile[1].txt and Testfile[2].txt before running main.cpp
        self.save_to_file_1()
        self.save_to_file_2()

        # Assuming main.cpp is in the same directory as this script
        try:
            subprocess.run(["g++", "main.cpp", "-o", "main"], check=True)
            process = subprocess.run(["./main"], capture_output=True, text=True, check=True)
        except subprocess.CalledProcessError as e:
            print("")

if __name__ == "__main__":
    root = tk.Tk()
    app = MyApp(root)
    root.mainloop()
