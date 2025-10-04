import webbrowser
import time
import os

def open_testcase_links(start_id, count):
    print(f"Opening links for testcases {start_id} through {start_id + count - 1}")
    
    for i in range(count):
        testcase_id = start_id + i
        
        # URLs for input and solution files
        input_url = f"https://cedt-grader.nattee.net/testcases/{testcase_id}/download_input"
        solution_url = f"https://cedt-grader.nattee.net/testcases/{testcase_id}/download_sol"
        
        # Open URLs in browser
        print(f"Opening testcase {testcase_id}...")
        webbrowser.open(input_url)
        time.sleep(1)  # Add a small delay between opening links
        webbrowser.open(solution_url)
        time.sleep(1)  # Add a small delay between testcases
        
        print(f"Opened testcase {testcase_id}: input and solution")
        
if __name__ == "__main__":
    # Starting testcase ID and count
    start_id = 17355
    count = 20  # This will download 17355 through 17374
    
    # Create directories for downloaded files
    os.makedirs("input", exist_ok=True)
    os.makedirs("solution", exist_ok=True)
    
    # Open the links
    open_testcase_links(start_id, count)
    
    print("\nAll links opened. Check your browser for the downloads.")
    print("Note: You may need to manually save the files from your browser.")
    print("Suggested file organization:")
    print(" - Save input files to the 'input' directory")
    print(" - Save solution files to the 'solution' directory")