#!/usr/bin/env python3
"""

    Checker Template for Cafe Grader (custom_cms)
    Version 0.1 (Alpha)
    Status: W.I.P
    
"""
import sys

class JudgeHelper:
    __input_testcase = None
    __output_consetant = None
    __output_actual = None

    def __init__(self, argv):
        self.__argv = argv
        self.__read_input()
        self.__read_consetant()

        if len(self.__argv) > 3:
            self.__read_actual()
        elif len(self.__argv) < 3:
            self.report_wrong("HELPER NEED AT LEAST 3 ARGV TO RUN!")
     
    def __read_input(self):
        # Read testcase input
        with open(self.__argv[1]) as input_file:
            plain_text = input_file.readlines()
            self.__input_testcase = plain_text
            return self.__input_testcase

    def __read_consetant(self):
        # Read consetant output (Output from student code result)
        with open(self.__argv[2]) as consetant_file:
            plain_text = consetant_file.readlines()
            self.__output_consetant = plain_text
            return self.__output_consetant

    def __read_actual(self):
        # Read actual testcase
        with open(self.__argv[3]) as output_file:
            plain_text = output_file.readlines()
            self.__output_actual = plain_text
            return self.__output_actual
    
    def report_wrong(self, comment: str = ""):
        print("0.0")
        sys.stderr.write(comment)
        exit()

    def report_correct(self):
        print("1.0")
        exit()

    def report_partial(self, score: float = 0.0):
        if score > 1 or score < 0:
            self.report_wrong("YOU SHOULD ENTER SCORE AT [0, 1) ONLY!")
        print(str(score))
        exit()

    def get_input(self):
        return self.__input_testcase
    
    def get_output_consetant(self):
        return self.__output_consetant
    
    def get_output_actual(self):
        return self.__output_actual

if __name__ == "__main__":
    helper = JudgeHelper(sys.argv)
    data_input = helper.get_input()
    data_output = helper.get_output_consetant()

    # ----- Let's make any logic below this line. -----
