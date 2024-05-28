# 打开data.txt文件进行读取
with open('data3.txt', 'r') as file:
    # 逐行读取文件
    lines = file.readlines()

# 创建一个新的列表来存储需要写入的行
new_lines = []

# 遍历原始文件的每一行
for line in lines:
    # 检查行的最后一个字符是否为'1'
    if line.strip().endswith('1'):
        # 如果是，复制该行3次
        new_lines.extend([line] * 9)
    else:
        # 如果不是，只添加原始行
        new_lines.append(line)

# 将结果输出到标准输出，您可以将它们重定向到另一个文件


# 如果你想将结果写入到另一个文件，可以取消注释下面的代码
with open('output.txt', 'w') as file:
     for new_line in new_lines:
         file.write(new_line)
print("dasda")