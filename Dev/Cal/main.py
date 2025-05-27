import math
import re
import time

while True:
    # 读取公式文件
    with open('formula.txt', 'r') as f:
        formula = f.read().strip()

    if formula:
        # 处理反三角函数
        formula = formula.replace('asin', 'math.asin') \
                         .replace('acos', 'math.acos') \
                         .replace('atan', 'math.atan')

        # 处理正三角函数（角度转弧度），避免匹配反三角函数
        trig_functions = ['sin', 'cos', 'tan']
        for func in trig_functions:
            pattern = re.compile(rf'(?<!math.a){func}\((.*?)\)')
            formula = pattern.sub(lambda m: f'math.{func}(math.radians({m.group(1)}))', formula)

        # 处理对数，使用正则表达式确保参数格式正确
        formula = re.sub(r'log\((.*?)\)', r'math.log10(\1)', formula)
        formula = re.sub(r'ln\((.*?)\)', r'math.log(\1)', formula)

        # 处理常数
        formula = formula.replace('pi', 'math.pi') \
                         .replace('e', 'math.e')

        # 处理开根号和幂运算
        formula = formula.replace('sqrt', 'math.sqrt') \
                         .replace('^', '**')

        # 处理阶乘（支持数字和括号内表达式）
        formula = re.sub(r'(\d+|\([^)]+\))!', lambda x: f'math.factorial({x.group(1)})', formula)

        # 调试输出，打印转换后的公式
        print(f"转换后的公式: {formula}")

        try:
            result = eval(formula)
            print(f"计算结果: {result}")
        except Exception as e:
            result = f"计算错误: {str(e)}"
            print(result)

        # 写入结果文件
        with open('result.txt', 'w') as f:
            f.write(str(result))

        # 清空公式文件
        with open('formula.txt', 'w') as f:
            f.write('')
    else:
        # 如果文件内容为空，等待一段时间后再次检查
        time.sleep(1)