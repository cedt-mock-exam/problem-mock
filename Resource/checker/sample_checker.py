#!/usr/bin/env python3
"""

    Checker Template for Cafe Grader (custom_cms)
    Version 0.1 (Alpha)
    Status: W.I.P
    
    (CHECKER: bonus_amazing_tiling)
    
"""
import sys

class JudgeHelper:
    __input_testcase = None
    __output_consetant = None
    __output_actual = None

    def __init__(self, argv):
        self.__argv = argv
        if len(self.__argv) > 3:
            self.__read_actual()
        elif len(self.__argv) < 3:
            self.report_wrong("HELPER NEED AT LEAST 3 ARGV TO RUN!")          
        self.__read_input()
        self.__read_consetant()
     
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
    try:
        data_input = helper.get_input()
        data_output = helper.get_output_consetant()
        # ----- Let's make any logic below this line. -----
        A, B = -1, -1
        if len(data_input) > 1 and len(data_input) <= 0:
            helper.report_wrong()
        A = int(data_input[0])

        if len(data_output) > 1:
            helper.report_wrong()
        elif len(data_output) > 0:
            B = int(data_output[0])
        else:
            B = 0

        if A >= 11:
            a, b, c = 1, 2, 5
            for _ in range(4, A + 1):
                a, b, c = b, c, 2 * c + a
        
            if c == B:
                helper.report_wrong("Ha! you are smart but too smart for this problem")
            elif B == 0:
                helper.report_correct()
            else:
                helper.report_partial(0.01)
        if A == 10 and B == 1255:
            helper.report_correct()
        if A == 9 and B == 569:
            helper.report_correct()
        if A == 8 and B == 258:
            helper.report_correct()
        if A == 7 and B == 117:
            helper.report_correct()
        if A == 6 and B == 53:
            helper.report_correct()
        if A == 5 and B == 24:
            helper.report_correct()
        if A == 4 and B == 11:
            helper.report_correct()
        if A == 3 and B == 5:
            helper.report_correct()
        if A == 2 and B == 2:
            helper.report_correct()
        if A == 1 and B == 1:
            helper.report_correct()

        helper.report_wrong()            
    except Exception as e:
        helper.report_wrong(f"") # In production please report with empty string!