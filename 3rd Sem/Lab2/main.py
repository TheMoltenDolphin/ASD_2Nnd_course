import sys

OPERATORS_P1 = {'+', '-'}
OPERATORS_P2 = {'*', '/'}
OPERATORS = OPERATORS_P1 | OPERATORS_P2

DIGITS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']

class RecursiveEvaluator:
    
    def __init__(self, expression_string: str):
        if not expression_string or expression_string[-1] != '=':
            raise SyntaxError("Выражение должно заканчиваться на '='")
        
        self.expression = expression_string[:-1]
        self.index = 0
        
        if not self.expression:
             raise SyntaxError("Пустое выражение")

    def parse(self) -> float:
        result = self.parse_1()
        
        if self.index != len(self.expression):
            raise SyntaxError("Неожиданные символы в конце выражения")
            
        return result

    def parse_1(self) -> float:
        current_value = self.parse_2()

        while self.index < len(self.expression):
            operator = self.expression[self.index]

            if operator not in OPERATORS_P1:
                break 
            
            self.index += 1
            
            next_value = self.parse_2()
            
            if operator == '+':
                current_value += next_value
            else:
                current_value -= next_value
                
        return current_value

    def parse_2(self) -> float:

        current_value = self.parse_3()
        
        while self.index < len(self.expression):
            operator = self.expression[self.index]

            if operator not in OPERATORS_P2:
                break
                
            self.index += 1 
            
            next_value = self.parse_3()

            if operator == '*':
                current_value *= next_value
            else:
                if next_value == 0:
                    raise SyntaxError("Деление на ноль")
                current_value /= next_value
                
        return current_value

    def parse_3(self) -> float:

        char = self.expression[self.index]

        if char in DIGITS:
            num_str = ""
            while self.index < len(self.expression) and self.expression[self.index] in DIGITS:
                num_str += self.expression[self.index]
                self.index += 1
            return float(num_str)
        
        elif char == '(':
            self.index += 1 
            
            value_inside = self.parse_level_1_add_sub()
            
            if self.index >= len(self.expression) or self.expression[self.index] != ')':
                 raise SyntaxError("Скобка не закрыта или ожидалась ')'")
            
            self.index += 1 
            return value_inside
        
        else:
            raise SyntaxError(f"Неожиданный символ: {char}")


eq = "8+4*(7-2)/5+6*3-1+(9-4)*2/(5*4-5)+7*2-5="

try:
    evaluator = RecursiveEvaluator(eq)
    result = evaluator.parse()
    
    print(result)

except (SyntaxError, ValueError, IndexError) as e:
    print(f"Ошибка вычисления: {e}", file=sys.stderr)