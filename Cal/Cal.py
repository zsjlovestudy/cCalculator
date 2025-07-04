import math
import re
import socket
import time
from enum import Enum
from collections import deque


class TokenType(Enum):
    NUMBER = 1
    OPERATOR = 2
    FUNCTION = 3
    CONSTANT = 4
    LEFT_PAREN = 5
    RIGHT_PAREN = 6


class Operator:
    def __init__(self, symbol, precedence, num_operands, func=None):
        self.symbol = symbol
        self.precedence = precedence
        self.num_operands = num_operands
        self.func = func


class ExpressionParser:
    OPERATORS = {
        '+': Operator('+', 1, 2, lambda a, b: a + b),
        '-': Operator('-', 1, 2, lambda a, b: a - b),
        '*': Operator('*', 2, 2, lambda a, b: a * b),
        '/': Operator('/', 2, 2, lambda a, b: a / b),
        '^': Operator('^', 3, 2, lambda a, b: a ** b),
        '%': Operator('%', 2, 2, lambda a, b: a % b),
        '!': Operator('!', 4, 1, lambda a: math.factorial(int(a))
        if a >= 0 and a.is_integer()
        else float('nan')),
    }

    FUNCTIONS = {
        'sin': (1, math.sin),
        'cos': (1, math.cos),
        'tan': (1, math.tan),
        'asin': (1, math.asin),
        'acos': (1, math.acos),
        'atan': (1, math.atan),
        'sqrt': (1, math.sqrt),
        'log': (1, math.log10),
        'ln': (1, math.log),
        'mexp': (1, math.exp),  # 新增mexp函数
    }

    CONSTANTS = {
        'pi': math.pi,
        'e': math.e
    }

    def __init__(self):
        self.reset()

    def reset(self):
        self.num_stack = []
        self.op_stack = [Operator('#', 0, 0)]
        self.token_queue = deque()

    def tokenize(self, formula):
        tokens = []
        i = 0
        n = len(formula)

        while i < n:
            if formula[i].isspace():
                i += 1
                continue

            # 处理数字
            if formula[i].isdigit() or formula[i] == '.':
                j = i
                while j < n and (formula[j].isdigit() or formula[j] in '.eE'):
                    j += 1
                tokens.append((TokenType.NUMBER, formula[i:j]))
                i = j
                continue

            # 处理函数和常量
            if formula[i].isalpha():
                j = i
                while j < n and formula[j].isalpha():
                    j += 1
                word = formula[i:j]


                if word == 'mexp' and j < n and (formula[j].isdigit() or formula[j] == '.'):
                    # 读取数字部分
                    k = j
                    while k < n and (formula[k].isdigit() or formula[k] in '.eE'):
                        k += 1
                    num_str = formula[j:k]

                    # 添加mexp函数标记
                    tokens.append((TokenType.FUNCTION, 'mexp'))
                    # 添加左括号
                    tokens.append((TokenType.LEFT_PAREN, '('))
                    # 添加数字
                    tokens.append((TokenType.NUMBER, num_str))
                    # 添加右括号
                    tokens.append((TokenType.RIGHT_PAREN, ')'))
                    i = k
                    continue
                else:
                    # 正常处理函数和常量
                    if word in self.FUNCTIONS:
                        tokens.append((TokenType.FUNCTION, word))
                    elif word in self.CONSTANTS:
                        tokens.append((TokenType.CONSTANT, word))
                    else:
                        raise ValueError(f"未知标识符: {word}")
                    i = j
                    continue

            # 处理运算符（包含%）
            if formula[i] in self.OPERATORS or formula[i] == '%':
                tokens.append((TokenType.OPERATOR, formula[i]))
                i += 1
                continue

            # 处理括号
            if formula[i] == '(':
                tokens.append((TokenType.LEFT_PAREN, '('))
                i += 1
                continue

            if formula[i] == ')':
                tokens.append((TokenType.RIGHT_PAREN, ')'))
                i += 1
                continue

            raise ValueError(f"无效字符: {formula[i]}")

        return tokens


    def parse(self, formula):
        self.reset()
        tokens = self.tokenize(formula)
        last_token_type = None

        for token_type, value in tokens:
            if token_type == TokenType.NUMBER:
                self.num_stack.append(float(value))
                last_token_type = TokenType.NUMBER

            elif token_type == TokenType.CONSTANT:
                self.num_stack.append(self.CONSTANTS[value])
                last_token_type = TokenType.CONSTANT

            elif token_type == TokenType.FUNCTION:
                self.op_stack.append(Operator(value, 4, 1, self.FUNCTIONS[value][1]))
                last_token_type = TokenType.FUNCTION

            elif token_type == TokenType.LEFT_PAREN:
                self.op_stack.append(Operator('(', 0, 0))
                last_token_type = TokenType.LEFT_PAREN

            elif token_type == TokenType.RIGHT_PAREN:
                while self.op_stack and self.op_stack[-1].symbol != '(':
                    self.calculate()
                if self.op_stack and self.op_stack[-1].symbol == '(':
                    self.op_stack.pop()
                last_token_type = TokenType.RIGHT_PAREN

            elif token_type == TokenType.OPERATOR:
                if value == '-' and last_token_type in [None, TokenType.OPERATOR, TokenType.LEFT_PAREN]:
                    op = Operator('u-', 4, 1, lambda a: -a)
                else:
                    op = self.OPERATORS[value]

                while self.op_stack and op.precedence <= self.op_stack[-1].precedence:
                    self.calculate()

                self.op_stack.append(op)
                last_token_type = TokenType.OPERATOR

        while self.op_stack[-1].symbol != '#':
            self.calculate()

        return self.num_stack.pop() if self.num_stack else 0

    def calculate(self):
        if not self.op_stack:
            return

        op = self.op_stack.pop()
        operands = []

        for _ in range(op.num_operands):
            if not self.num_stack:
                raise ValueError("操作数不足")
            operands.append(self.num_stack.pop())

        if op.symbol in ['sin', 'cos', 'tan']:
            operands = [math.radians(operands[0])]

        result = op.func(*reversed(operands))

        if op.symbol in ['asin', 'acos', 'atan']:
            result = math.degrees(result)

        self.num_stack.append(result)



def start_server():
    """创建TCP服务器"""
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_address = ('0.0.0.0', 65433)
    server_socket.bind(server_address)
    server_socket.listen(1)
    print("科学计算服务器已启动，等待连接...")
    return server_socket


def safe_calculate(formula):
    """安全计算数学表达式并格式化结果"""
    try:
        formula = re.sub(r'\s+', '', formula)
        formula = formula.lower()
        parser = ExpressionParser()
        result = parser.parse(formula)

        if math.isnan(result):
            return "数学错误: 结果未定义"
        elif math.isinf(result):
            return "数学错误: 结果无穷大"

        rounded = round(result, 7)

        if abs(rounded) < 1e-15:
            return "0"

        s = format(rounded, '.15f')

        if '.' in s:
            s = s.rstrip('0').rstrip('.')
            if s == '' or s == '-':
                s = '0'

        if s == '-0':
            s = '0'

        return s

    except Exception as e:
        return f"计算错误: {str(e)}"


def main():
    server_socket = start_server()
    parser = ExpressionParser()

    while True:
        client_socket, addr = server_socket.accept()
        client_socket.settimeout(100.0)
        print(f"已连接: {addr}")

        try:
            data = b''
            end_marker = b'<END>'
            start_time = time.time()

            while True:
                try:
                    chunk = client_socket.recv(1024)
                    if not chunk:
                        break
                    data += chunk
                    print(f"接收原始数据: {chunk.decode()!r}")

                    if data.endswith(end_marker) or time.time() - start_time > 100:
                        break
                except socket.timeout:
                    break

            if data.endswith(end_marker):
                formula = data[:-len(end_marker)].decode().strip()
            else:
                formula = data.decode().strip()

            if formula:
                print(f"接收公式: {formula}")
                result = safe_calculate(formula)
                print(f"计算结果: {result}")

                response = result.encode() + end_marker
                client_socket.sendall(response)
                print(f"发送响应: {response.decode()!r}")

        except Exception as e:
            error_msg = f"服务器错误: {str(e)}".encode() + end_marker
            print(f"处理错误: {str(e)}")
            client_socket.sendall(error_msg)
            print(f"发送错误信息: {error_msg.decode()!r}")

        finally:
            client_socket.close()
            print(f"关闭连接: {addr}")


if __name__ == "__main__":
    main()