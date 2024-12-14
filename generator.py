input = (input("Enter desired file size (in MB): "))

output = open("output.txt", "w")

line = "Lorem ipsum dolor sit amet\n"
lineCount = int(input) * 1000000 / len(line)

for i in range(0, int(lineCount)):
    output.write(line)