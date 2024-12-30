fileSize = input("Enter desired file size (in MB): ")
shortLines = True if input("Generate short lines? (Y/N): ") == "Y" else False

output = open("output.txt", "w")

line = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam lorem ipsum, auctor sit amet ipsum eget, laoreet consectetur velit. Aliquam \nsit amet tristique nibh. Donec malesuada mauris orci, facilisis fringilla nulla molestie ac. Integer ultricies feugiat nunc vitae blandit. Proin facilisis bibendum erat, nec blandit dui auctor at. Proin dui purus, volutpat pulvinar ultrices id, semper at odio. Nulla congue auctor urna \nsit amet gravida. Integer porta nisi vitae ultricies congue. Nunc pharetra tempus sem non commodo. Fusce vitae egestas lacus. Cras pretium vel metus sit amet euismod. Sed sem elit, egestas sed elementum at, scelerisque nec ex.\n" if not shortLines else "Lorem ipsum dolor sit amet.\n"
lineCount = int(fileSize) * 1000000 / len(line)

for i in range(0, int(lineCount)):
    output.write(line)
    