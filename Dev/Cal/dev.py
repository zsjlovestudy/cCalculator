import math
import re
import time
import socket


# 创建TCP服务器
def start_server():
    # 创建TCP套接字
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # 绑定服务器地址和端口
    server_address = ('0.0.0.0', 65433)  # 监听所有接口的65433端口
    server_socket.bind(server_address)
    # 开始监听
    server_socket.listen(1)
    print("科学计算 - 科学计算服务器已启动，等待连接...")

    return server_socket


def main():
    server_socket = start_server()

    while True:
        # 等待客户端连接
        client_socket, client_address = server_socket.accept()
        print(f"已连接: {client_address}")

        try:
            # 接收数据
            data = b''
            while True:
                chunk = client_socket.recv(1024)
                if not chunk:
                    break
                data += chunk
                # 检查是否收到结束标记（自定义协议）
                if b'<END>' in data:
                    data = data.replace(b'<END>', b'')
                    break

            formula = data.decode().strip()
            print(f"接收到的公式: {formula}")

            if formula:
                # 处理反三角函数
                formula = formula.replace('asin', 'math.asin') \
                    .replace('acos', 'math.acos') \
                    .replace('atan', 'math.atan')

                # 处理正三角函数（角度转弧度）
                trig_functions = ['sin', 'cos', 'tan']
                for func in trig_functions:
                    pattern = re.compile(rf'(?<!math.a){func}$(.*?)$')
                    formula = pattern.sub(lambda m: f'math.{func}(math.radians({m.group(1)}))', formula)

                # 处理对数
                formula = re.sub(r'log$(.*?)$', r'math.log10(\1)', formula)
                formula = re.sub(r'ln$(.*?)$', r'math.log(\1)', formula)

                # 处理常数
                formula = formula.replace('pi', 'math.pi') \
                    .replace('e', 'math.e')

                # 处理开根号和幂运算
                formula = formula.replace('sqrt', 'math.sqrt') \
                    .replace('^', '**')

                # 处理阶乘
                formula = re.sub(r'(\d+|$[^)]+$)!', lambda x: f'math.factorial({x.group(1)})', formula)

                print(f"转换后的公式: {formula}")

                try:
                    # 执行计算
                    result = eval(formula)
                    print(f"计算结果: {result}")
                    response = str(result)
                except Exception as e:
                    error_msg = f"计算错误: {str(e)}"
                    print(error_msg)
                    response = error_msg

                # 发送响应并添加结束标记
                client_socket.sendall(response.encode() + b'<END>')
                print("已发送计算结果")

        except Exception as e:
            print(f"通信错误: {str(e)}")

        finally:
            # 关闭连接
            client_socket.close()
            print(f"连接已关闭: {client_address}")


if __name__ == "__main__":
    main()