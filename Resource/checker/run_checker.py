#!/usr/bin/env python3
"""

    Checker Template for Cafe Grader (custom_cms)
    Version 0.1 (Alpha)
    Status: W.I.P
    
"""
import os
import sys
import logging

logging.basicConfig(
        level=logging.DEBUG,
        format="%(levelname)s: %(message)s"
)

class Grader:
    CHECKER_FILE = None
    CURRENT_DIR = None

    def __init__(self, checker: str):
        self.CHECKER_FILE = checker
        if not self._verifyDirectory():
            exit(0)
        

    def _checkTestcase(self):
        dataset = list()
        for file in os.listdir(self.CURRENT_DIR):
            if file.__contains__(".sol") or file == ".gitkeep":
                continue
            testcase_in = file
            testcase_out = file[0:len(file)-3] + ".sol"
            dataset.append([testcase_in, testcase_out])
        return dataset


    def _verifyDirectory(self):
        cwd = os.getcwd()
        if os.path.exists(cwd+"/testcase"):
            self.CURRENT_DIR = cwd+"/testcase"
            return True
        
        os.makedirs(cwd+"/testcase")
        return False
    
    def Run(self):
        files = self._checkTestcase()
        if len(files) <= 0:
            logging.error("Not have a file to dry-run checker!")
        
        for f in files:
            logging.info("Trying to run: %s", self.CHECKER_FILE)
            logging.info("===================",)
            os.system(f"chmod +x ./{self.CHECKER_FILE}")
            os.system(f"./{self.CHECKER_FILE} {self.CURRENT_DIR}/{f[0]} {self.CURRENT_DIR}/{f[1]}")
            logging.info("===================",)


if __name__ == "__main__":
    CHECKER = input("Checker file name (.py): ")
    Judge = Grader(CHECKER)
    Judge.Run()
