input = (input("Enter desired file size (in MB): "))

output = open("output.txt", "w")

line = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Etiam lorem ipsum, auctor sit amet ipsum eget, laoreet consectetur velit. Aliquam \nsit amet tristique nibh. Donec malesuada mauris orci, facilisis fringilla nulla molestie ac. Integer ultricies feugiat nunc vitae blandit. Proin \nfacilisis bibendum erat, nec blandit dui auctor at. Proin dui purus, volutpat pulvinar ultrices id, semper at odio. Nulla congue auctor urna \nsit amet gravida. Integer porta nisi vitae ultricies congue. Nunc pharetra tempus sem non commodo. Fusce vitae egestas lacus. Cras \npretium vel metus sit amet euismod. Sed sem elit, egestas sed elementum at, scelerisque nec ex.\n"
lineCount = int(input) * 1000000 / len(line)

for i in range(0, int(lineCount)):
    output.write(line)
    