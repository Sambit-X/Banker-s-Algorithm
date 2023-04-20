import subprocess
import tkinter as tk

# Define the function to be executed when the button is clicked
def run_program():
    # Get the input from the Entry widgets
    input1_str = input1_entry.get()
    input2_str = input2_entry.get()
    input3_str = input3_entry.get("1.0", tk.END)
    input4_str = input4_entry.get("1.0", tk.END)
    
    # Convert input strings to lists
    input1_list = [int(x) for x in input1_str.split()]
    input2_list = [int(x) for x in input2_str.split()]
    input3_list = [[int(x) for x in line.split()] for line in input3_str.split('\n')]
    input4_list = [[int(x) for x in line.split()] for line in input4_str.split('\n')]

    # Call the C program and pass input to it
    input_bytes = '\n'.join([' '.join(map(str, input1_list)), ' '.join(map(str, input2_list)), 
                             '\n'.join([' '.join(map(str, row)) for row in input3_list]), 
                             '\n'.join([' '.join(map(str, row)) for row in input4_list])]).encode()
    result = subprocess.run(["./my_c_executable"], input=input_bytes, stdout=subprocess.PIPE)

    # Decode the output and update the Label widget
    output_str = result.stdout.decode().strip()
    output_label.config(text=output_str)


# Create the main window
root = tk.Tk()
root.geometry("500x500")
root.title("Banker's Algorithm")

# Create the input Entry widgets and labels
input1_label = tk.Label(root, text="Process List (5 values):")
input1_label.pack()
input1_entry = tk.Entry(root)
input1_entry.pack()

input2_label = tk.Label(root, text="Available Resources (3 values)")
input2_label.pack()
input2_entry = tk.Entry(root)
input2_entry.pack()

input3_label = tk.Label(root, text="Maximum Matrix (5x3 values):")
input3_label.pack()
input3_entry = tk.Text(root, height=5, width=30)
input3_entry.pack()

input4_label = tk.Label(root, text="Allocation Matrix (5x3 values):")
input4_label.pack()
input4_entry = tk.Text(root, height=5, width=30)
input4_entry.pack()

# Create the button to execute the C program
run_button = tk.Button(root, text="RUN", command=run_program)
run_button.pack()

# Create the output Label widget
output_label = tk.Label(root, text="")
output_label.pack()

# Start the main event loop
root.mainloop()
