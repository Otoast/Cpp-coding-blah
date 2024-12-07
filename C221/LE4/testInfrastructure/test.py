import subprocess
import os

def run_cpp_file():
    # Compile the C++ code
    cpp_filename = 'bst_test.cpp'
    compile_process = subprocess.run(["g++", "-std=c++17", cpp_filename, "-o", "temp_executable"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

    # Check for compilation errors
    if compile_process.returncode != 0:
        print("Compilation error:")
        print(compile_process.stderr)
        return

    # Run the compiled executable
    try:
        run_process = subprocess.run(["./temp_executable"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=20)
        if (run_process.stderr):
            print("Error:")
            print(run_process.stderr) 
        print(run_process.stdout)
    except subprocess.TimeoutExpired:
        print("The executable timed out after 20 seconds.")
    
    valgrind_cmd = ["valgrind", "--leak-check=full", "./temp_executable"]

    try:
        process = subprocess.Popen(valgrind_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate(20)
        
        if "ERROR SUMMARY: 0 errors" not in stderr.decode():
            print("Valgrind detected memory leaks")
            print(stderr.decode())
        else:
            print("No memory leaks detected")
    except subprocess.CalledProcessError as e:
        print("Valgrind error")
    except subprocess.TimeoutExpired:
        print("The executable timed out after 20 seconds.")

   
    try:
        os.remove("./temp_executable")
    except FileNotFoundError:
        print("Compilation error")

run_cpp_file()
